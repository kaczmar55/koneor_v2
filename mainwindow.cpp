#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eor_cfg.h"
#include "comboboxitemdelegate.h"
#include "crc16.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionOtw_rz->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->actionZapisz->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->actionZako_cz->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogCloseButton));

    ui->fileSize->setText(QString::number(eorkonf_data_size) + QString("B"));

    ui->generalTempSensorTypeCmb->addItem("TH");
    ui->generalTempSensorTypeCmb->addItem("CAN");
    ui->generalTempSensorTypeCmb->addItem("Modbus");

    ui->generalFallSensorTypeCmb->addItem("IO");
    ui->generalFallSensorTypeCmb->addItem("CAN");
    ui->generalFallSensorTypeCmb->addItem("Modbus");

    ui->weatherAutomList->addItem("Automat pogodowy 1");
    ui->weatherAutomList->setCurrentRow(0);
//    ComboBoxItemDelegate* cbid = new ComboBoxItemDelegate(ui->ioModulesTable);
//    ui->ioModulesTable->setItemDelegate(cbid);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOtw_rz_triggered()
{
    QString fileNameToOpen;
    QFile file;
    QByteArray fileBuf;
    uint16_t crc16;

    fileNameToOpen = QFileDialog::getOpenFileName(this, "Otwórz plik konfiguracji", NULL, "koneor.bin");

    if(fileNameToOpen == "")
    {
    //anuluj
    }
    else
    {
        file.setFileName(fileNameToOpen);
        if(file.open(QIODevice::ReadOnly))
        {
            fileBuf = file.readAll();
            file.close();

            if(fileBuf.size() != (eorkonf_data_size + sizeof(eorkonf_hdr_t)))
            {
                QMessageBox::critical(this, "Błąd", QString("Nieprawidłowy rozmiar pliku. Dane nie zostały wczytane\n") +
                                      QString("Wczytano: ") + QString::number(fileBuf.size()) +
                                      QString(" B\nOczekiwano: ") + QString::number(eorkonf_data_size + sizeof(eorkonf_hdr_t)) +
                                      QString(" B"));
                return;
            }

            setCfgStructs(fileBuf.data());
            crc16 = LiczCrc16Buf((uint8_t*)&fileBuf.data()[sizeof(eorkonf_hdr_t)], eorkonf_data_size);
            if(eorkonf_hdr.crc16 != crc16)
            {
                QMessageBox::critical(this, "Błąd", QString("Nieprawidłowe crc pliku. Wczytane dane mogą być błędne\n") +
                                      QString("Obliczone: 0x") + QString::number(crc16, 16) +
                                      QString("\nOczekiwano: 0x") + QString::number(eorkonf_hdr.crc16, 16));
            }

            if(eorkonf_hdr.file_len != eorkonf_data_size)
            {
                QMessageBox::critical(this, "Błąd", QString("Nieprawidłowy rozmiar danych w nagłówku\n") +
                                      QString("Odczytane: ") + QString::number(eorkonf_hdr.file_len) +
                                      QString(" B\nOczekiwano: ") + QString::number(eorkonf_data_size) +
                                      QString(" B"));
            }

            if(strncmp(eorkonf_hdr.id_txt, "EOR_KON", 7) != 0)
            {
                QMessageBox::critical(this, "Błąd", "Brak w nagłówku znacznika EOR_KON. Wczytane dane mogą być nieprawidłowe\n");
            }

            ui->fileSize->setText(QString::number(eorkonf_hdr.file_len + sizeof(eorkonf_hdr_t)));
            ui->fileVer->setText(QString("%1.%2").arg(eorkonf_hdr.ver).arg(eorkonf_hdr.rev));
            setGeneralCfg();
            setIOModuleCfg();
            setJsn2Cfg();
            setMeterCfg();
            setGeneralWeatherMeasure();
        }
        else
        {
            QMessageBox::critical(this, "Błąd", "Wystąpił błąd podczas otwierania pliku do odczytu");
        }
    }
}

void MainWindow::on_actionZako_cz_triggered()
{
    close();
}

void MainWindow::on_actionZapisz_triggered()
{
    QString fileNameToSave;
    QFile file;
    QByteArray fileBuf;
    qint64 ret;
    char* cBuf;
    eorkonf_hdr_t *tmp_eorkonf_hdr;

    fileNameToSave = QFileDialog::getSaveFileName(this, "Zapisz plik konfiguracji", NULL, "koneor.bin");

    if(fileNameToSave == "")
    {
    //anuluj
    }
    else
    {
        file.setFileName(fileNameToSave);
        if(file.open(QIODevice::WriteOnly))
        {
            eorkonf_hdr.ver = 1;
            eorkonf_hdr.rev = 0;
            eorkonf_hdr.file_len = eorkonf_data_size;
            strcpy(eorkonf_hdr.id_txt, "EOR_KON");
            fileBuf.append((char*)&eorkonf_hdr, sizeof(eorkonf_hdr_t));
            //todo na koniec crc16

            if(updateGeneralCfg() == false)
            {
                QMessageBox::critical(this, "Błąd", "Błąd parametrów w części \"Podstawowe\"");
                return;
            }
            fileBuf.append((char*)&general_cfg, sizeof(general_cfg_t));
            fileBuf.append((char*)user_cfg, sizeof(user_cfg_t) * USER_COUNT);
            if(updateIOModuleCfg() == false)
            {
                QMessageBox::critical(this, "Błąd", "Błędna wartość w polu adres w modułach IO");
                return;
            }
            fileBuf.append((char*)io_module_cfg, sizeof(io_module_cfg_t) * IO_MODULE_COUNT);
            if(updateJsn2Cfg() == false)
            {
                QMessageBox::critical(this, "Błąd", "Błędna wartość w polu adres w modułach JSN-2");
                return;
            }
            fileBuf.append((char*)jsn2_module_cfg, sizeof(jsn2_module_cfg_t) * JSN2_MODULE_COUNT);
            if(updateMeterCfg() == false)
            {
                QMessageBox::critical(this, "Błąd", "Błędny numer seryjny licznika energii");
                return;
            }
            fileBuf.append((char*)meter_cfg, sizeof(meter_cfg_t) * METER_COUNT);
            if(updateGeneralWeatherMeasure() == false)
                return;
            fileBuf.append((char*)&general_weather_measure_cfg, sizeof(general_weather_measure_cfg_t));
            fileBuf.append((char*)weather_autom_cfg, sizeof(weather_autom_cfg_t) * WEATHER_AUTOM_COUNT);
            fileBuf.append((char*)&lock_autom_cfg, sizeof(lock_autom_cfg_t));
            fileBuf.append((char*)circuit_cfg, sizeof(circuit_cfg_t) * CIRCUIT_COUNT);
            fileBuf.append((char*)&group_cfg, sizeof(group_cfg_t));
            fileBuf.append((char*)&io_cfg, sizeof(io_cfg_t));
            fileBuf.append((char*)&can_cfg, sizeof(can_cfg_t));
            fileBuf.append((char*)&modbus_slave_cfg, sizeof(modbus_slave_cfg_t));
            fileBuf.append((char*)&tgfm_cfg, sizeof(tgfm_cfg_t));
            fileBuf.append((char*)rs_cfg, sizeof(rs_cfg_t) * RS_COUNT);
            fileBuf.append((char*)&eth_cfg, sizeof(eth_cfg_t));

            cBuf = fileBuf.data();
            tmp_eorkonf_hdr = (eorkonf_hdr_t*)cBuf;
            tmp_eorkonf_hdr->crc16 = LiczCrc16Buf((uint8_t*)&cBuf[sizeof(eorkonf_hdr_t)], eorkonf_data_size);

            ret = file.write(fileBuf);
            if(ret == -1)
                QMessageBox::critical(this, "Błąd", QString("Błąd podczas zapisu pliku na dysk."));
            else if(ret < (eorkonf_data_size + sizeof(eorkonf_hdr_t)))
                QMessageBox::critical(this, "Błąd", QString("Błąd podczas zapisu danych na dysku\n") +
                                      QString("Zapisano: ") + QString::number(ret) +
                                      QString(" B\nPowinno być: ") + QString::number(eorkonf_data_size + sizeof(eorkonf_hdr_t)) +
                                      QString(" B"));
            file.close();
        }
        else
        {
            QMessageBox::critical(this, "Błąd", "Wystąpił błąd podczas otwierania pliku do zapisu");
        }
    }
}

void MainWindow::setCfgStructs(char* buf)
{
    int index = 0;

    memcpy(&eorkonf_hdr, &buf[index], sizeof(eorkonf_hdr_t));
    index += sizeof(eorkonf_hdr_t);

    memcpy(&general_cfg, &buf[index], sizeof(general_cfg_t));
    index += sizeof(general_cfg_t);

    memcpy(user_cfg, &buf[index], sizeof(user_cfg_t) * USER_COUNT);
    index += sizeof(user_cfg_t) * USER_COUNT;

    memcpy(io_module_cfg, &buf[index], sizeof(io_module_cfg_t) * IO_MODULE_COUNT);
    index += sizeof(io_module_cfg_t) * IO_MODULE_COUNT;

    memcpy(jsn2_module_cfg, &buf[index], sizeof(jsn2_module_cfg_t) * JSN2_MODULE_COUNT);
    index += sizeof(jsn2_module_cfg_t) * JSN2_MODULE_COUNT;

    memcpy(meter_cfg, &buf[index], sizeof(meter_cfg_t) * METER_COUNT);
    index += sizeof(meter_cfg_t) * METER_COUNT;

    memcpy(&general_weather_measure_cfg, &buf[index], sizeof(general_weather_measure_cfg_t));
    index += sizeof(general_weather_measure_cfg_t);

    memcpy(weather_autom_cfg, &buf[index], sizeof(weather_autom_cfg_t) * WEATHER_AUTOM_COUNT);
    index += sizeof(weather_autom_cfg_t) * WEATHER_AUTOM_COUNT;

    memcpy(&lock_autom_cfg, &buf[index], sizeof(lock_autom_cfg_t));
    index += sizeof(lock_autom_cfg_t);

    memcpy(circuit_cfg, &buf[index], sizeof(circuit_cfg_t) * CIRCUIT_COUNT);
    index += sizeof(circuit_cfg_t) * CIRCUIT_COUNT;

    memcpy(&group_cfg, &buf[index], sizeof(group_cfg_t));
    index += sizeof(group_cfg_t);

    memcpy(&io_cfg, &buf[index], sizeof(io_cfg_t));
    index += sizeof(io_cfg_t);

    memcpy(&can_cfg, &buf[index], sizeof(can_cfg_t));
    index += sizeof(can_cfg_t);

    memcpy(&modbus_slave_cfg, &buf[index], sizeof(modbus_slave_cfg_t));
    index += sizeof(modbus_slave_cfg_t);

    memcpy(&tgfm_cfg, &buf[index], sizeof(tgfm_cfg_t));
    index += sizeof(tgfm_cfg_t);

    memcpy(rs_cfg, &buf[index], sizeof(rs_cfg_t) * RS_COUNT);
    index += sizeof(rs_cfg_t) * RS_COUNT;

    memcpy(&eth_cfg, &buf[index], sizeof(eth_cfg_t));
    index += sizeof(eth_cfg_t);
}

bool MainWindow::updateGeneralCfg(void)
{
    memset(&general_cfg, 0, sizeof(general_cfg_t));
    strcpy(general_cfg.name, ui->objName->text().toUtf8().data());
    strncpy(general_cfg.description, ui->objDescription->toPlainText().toUtf8().data(), 255);
    general_cfg.cir_count = ui->cirCount->value();
    general_cfg.weather_autom_count = ui->weatherAutomCount->value();
    general_cfg.ctrl_group_cnt = 6;
    general_cfg.ind_on_time = ui->indOnTime->value();
    general_cfg.phase_asymmetry_check = ui->phaseAssymetryCheck->isChecked();
    general_cfg.phase_assymetry_tolerance = ui->phaseAssymetryTolerance->value();
    general_cfg.min_phase_voltage = ui->minPhaseVoltage->value();
    general_cfg.ctrl_user_level = ui->ctrlUserLevel->value();
    general_cfg.param_edit_user_level = ui->paramEditUserLevel->value();
    general_cfg.screen_saver_enable = ui->screenSaverEnable->isChecked();
    general_cfg.screen_saver_time = ui->screenSaverTime->value();

    return true;
}

bool MainWindow::setGeneralCfg(void)
{
    ui->objName->setText(general_cfg.name);
    ui->objDescription->setPlainText(general_cfg.description);
    ui->cirCount->setValue(general_cfg.cir_count);
    ui->weatherAutomCount->setValue(general_cfg.weather_autom_count);
    ui->indOnTime->setValue(general_cfg.ind_on_time);
    if(general_cfg.phase_asymmetry_check == 0)
        ui->phaseAssymetryCheck->setChecked(false);
    else
        ui->phaseAssymetryCheck->setChecked(true);
    ui->phaseAssymetryTolerance->setValue(general_cfg.phase_assymetry_tolerance);
    ui->minPhaseVoltage->setValue(general_cfg.min_phase_voltage);
    ui->ctrlUserLevel->setValue(general_cfg.ctrl_user_level);
    ui->paramEditUserLevel->setValue(general_cfg.param_edit_user_level);
    if(general_cfg.screen_saver_enable == 0)
        ui->screenSaverEnable->setChecked(false);
    else
        ui->screenSaverEnable->setChecked(true);
    ui->screenSaverTime->setValue(general_cfg.screen_saver_time);

    return true;
}

bool MainWindow::updateIOModuleCfg(void)
{
    int count = ui->ioModulesTable->rowCount();
    int i;
    QComboBox* cmb;
    bool ok = true;

    memset(io_module_cfg, 0, sizeof(io_module_cfg_t) * IO_MODULE_COUNT);
    for(i = 0; i < count; i++)
    {
        cmb = (QComboBox*)ui->ioModulesTable->cellWidget(i, 0);
        io_module_cfg[i].type = cmb->currentData().toInt();
        io_module_cfg[i].addr = ui->ioModulesTable->item(i, 1)->text().toInt(&ok, 0);
        if(ok == false)
            break;
    }

    return ok;
}

bool MainWindow::setIOModuleCfg(void)
{
    QTableWidget *ioModuleTable = ui->ioModulesTable;
    int i, row;
    QComboBox *cb;

    ioModuleTable->clear();
    for(i = 0; i < IO_MODULE_COUNT; i++)
    {
        if(io_module_cfg[i].type != 0)
        {
            cb = new QComboBox();
            cb->addItem(QString("IO10/5"), 1);
            cb->addItem(QString("TH"), 3);
            cb->addItem(QString("I12"), 4);
            cb->addItem(QString("I20"), 5);
            cb->addItem(QString("O10"), 6);
            cb->addItem(QString("CVM"), 7);
            cb->addItem(QString("ISC3"), 10);
            cb->addItem(QString("IO4/7"), 11);
            cb->addItem(QString("O8"), 12);
            cb->addItem(QString("GMR IO"), 14);

            row = ioModuleTable->rowCount();
            ioModuleTable->insertRow(row);
            ioModuleTable->setCellWidget(row, 0, cb);
            cb->setCurrentIndex(cb->findData(io_module_cfg[i].type));
            ioModuleTable->setItem(row, 1, new QTableWidgetItem());
            ioModuleTable->item(row, 1)->setText(QString("0x%1").arg(io_module_cfg[i].addr, 0, 16));
        }
    }
    return true;
}

bool MainWindow::updateJsn2Cfg(void)
{
    int count = ui->jsn2ModulesTable->rowCount();
    int i;
    bool ok = true;

    memset(jsn2_module_cfg, 0, sizeof(jsn2_module_cfg_t) * JSN2_MODULE_COUNT);
    for(i = 0; i < count; i++)
    {
        jsn2_module_cfg[i].type = 1;
        jsn2_module_cfg[i].addr = ui->jsn2ModulesTable->item(i, 0)->text().toInt(&ok, 0);
        if(ok == false)
            break;
    }

    return ok;
}

bool MainWindow::setJsn2Cfg(void)
{
    QTableWidget *jsn2Table = ui->jsn2ModulesTable;
    int i, row;

    jsn2Table->clear();
    for(i = 0; i < JSN2_MODULE_COUNT; i++)
    {
        if(jsn2_module_cfg[i].type != 0)
        {
            row = jsn2Table->rowCount();
            jsn2Table->insertRow(row);
            jsn2Table->setItem(row, 0, new QTableWidgetItem());
            jsn2Table->item(row, 0)->setText(QString::number(jsn2_module_cfg[i].addr));
        }
    }
    return true;
}

bool MainWindow::updateMeterCfg(void)
{
    int count = ui->energyMetersTab->rowCount();
    int i;

    memset(meter_cfg, 0, sizeof(meter_cfg_t) * METER_COUNT);
    for(i = 0; i < count; i++)
    {
        meter_cfg[i].type = 1;
        strncpy(meter_cfg[i].id, ui->energyMetersTab->item(i, 0)->text().toUtf8().data(), 14);
    }

    return true;
}

bool MainWindow::setMeterCfg(void)
{
    QTableWidget *energyMetersTab = ui->energyMetersTab;
    int i, row;

    energyMetersTab->clear();
    for(i = 0; i < METER_COUNT; i++)
    {
        if(meter_cfg[i].type != 0)
        {
            row = energyMetersTab->rowCount();
            energyMetersTab->insertRow(row);
            energyMetersTab->setItem(row, 0, new QTableWidgetItem());
            energyMetersTab->item(row, 0)->setText(meter_cfg[i].id);
        }
    }
    return true;
}

bool MainWindow::updateGeneralWeatherMeasure(void)
{
    QComboBox *cb;
    bool ret = true;
    uint8_t addr = ui->generalTempSensorAddr->value();
    uint16_t reg_no = ui->generalTempSensorRegNo->value();
    uint8_t bit_no;

    general_weather_measure_cfg.temperature_sensor.type = ui->generalTempSensorTypeCmb->currentIndex();
    general_weather_measure_cfg.temperature_sensor.addr = addr;
    general_weather_measure_cfg.temperature_sensor.reg_no = reg_no;

    switch(general_weather_measure_cfg.temperature_sensor.type)
    {
    case 0:     //TH
        if(addr >= ui->ioModulesTable->rowCount())
        {
            QMessageBox::critical(this, "Błąd", "Ogólne pomiary pogody - czujnik temperatury otoczenia\nNie ma modułu IO o podanym numerze.");
            ret = false;
        }
        else
        {
            cb = (QComboBox*)ui->ioModulesTable->cellWidget(addr, 0);
            if(cb->currentIndex() != 1)
            {
                QMessageBox::critical(this, "Błąd", "Ogólne pomiary pogody - czujnik temperatury otoczenia\nModuł o podanym numerze nie jest modułem TH.");
                ret = false;
            }
        }
        break;
    case 1:     //CAN
        break;
    case 2:     //Modbus
        break;
    }

    general_weather_measure_cfg.snow_fall_sensor.type = ui->generalFallSensorTypeCmb->currentIndex();
    addr = ui->generalFallSensorAddr->value();
    reg_no = ui->generalFallSensorRegNo->value();
    bit_no = ui->generalFallSensorBitNo->value();

    switch(general_weather_measure_cfg.snow_fall_sensor.type)
    {
    case 0:     //io
        if(addr >= ui->ioModulesTable->rowCount())
        {
            QMessageBox::critical(this, "Błąd", "Ogólne pomiary pogody - czujnik opadu\nNie ma modułu IO o podanym numerze.");
            ret = false;
        }
        else
        {
            cb = (QComboBox*)ui->ioModulesTable->cellWidget(addr, 0);
            if((cb->currentIndex() != 0) &&         /* io10/5 */
                    (cb->currentIndex() != 1) &&    /* th     */
                    (cb->currentIndex() != 2) &&    /* i12    */
                    (cb->currentIndex() != 3) &&    /* i20    */
                    (cb->currentIndex() != 7) &&    /* io4/7  */
                    (cb->currentIndex() != 9))      /* gmr io */
            {
                QMessageBox::critical(this, "Błąd", "Ogólne pomiary pogody - czujnik opadu\nModuł o podanym numerze nie ma wejść cyfrowych.");
                ret = false;
            }
        }
        break;
    case 1:     //can
        break;
    case 2:     //modbus
        break;
    }
    general_weather_measure_cfg.snow_fall_sensor.addr = addr;
    general_weather_measure_cfg.snow_fall_sensor.reg_no = reg_no;
    general_weather_measure_cfg.snow_fall_sensor.bit_no = bit_no;

    return ret;
}

bool MainWindow::setGeneralWeatherMeasure(void)
{
    ui->generalTempSensorTypeCmb->setCurrentIndex(general_weather_measure_cfg.temperature_sensor.type);
    ui->generalTempSensorAddr->setValue(general_weather_measure_cfg.temperature_sensor.addr);
    ui->generalTempSensorRegNo->setValue(general_weather_measure_cfg.temperature_sensor.reg_no);

    ui->generalFallSensorTypeCmb->setCurrentIndex(general_weather_measure_cfg.snow_fall_sensor.type);
    ui->generalFallSensorAddr->setValue(general_weather_measure_cfg.snow_fall_sensor.addr);
    ui->generalFallSensorBitNo->setValue(general_weather_measure_cfg.snow_fall_sensor.bit_no);
    ui->generalFallSensorRegNo->setValue(general_weather_measure_cfg.snow_fall_sensor.reg_no);

    return true;
}

void MainWindow::on_addIoModuleBtn_clicked()
{
    QComboBox* cb;
    QComboBox* prev_cb;
    QTableWidgetItem* item;

    int rows = ui->ioModulesTable->rowCount();
    if(rows < IO_MODULE_COUNT)
    {
        ui->ioModulesTable->insertRow(rows);

        cb = new QComboBox();
        cb->addItem(QString("IO10/5"), 1);
        cb->addItem(QString("TH"), 3);
        cb->addItem(QString("I12"), 4);
        cb->addItem(QString("I20"), 5);
        cb->addItem(QString("O10"), 6);
        cb->addItem(QString("CVM"), 7);
        cb->addItem(QString("ISC3"), 10);
        cb->addItem(QString("IO4/7"), 11);
        cb->addItem(QString("O8"), 12);
        cb->addItem(QString("GMR IO"), 14);

        ui->ioModulesTable->setCellWidget(rows, 0, cb);
        ui->ioModulesTable->setItem(rows, 1, new QTableWidgetItem());
        if(rows == 0)
        {
            item = ui->ioModulesTable->item(0, 1);
            item->setText("0x12");
        }
        else
        {
            prev_cb = (QComboBox*)ui->ioModulesTable->cellWidget(rows - 1, 0);
            cb->setCurrentIndex(prev_cb->currentIndex());
            ui->ioModulesTable->item(rows, 1)->setText(QString("0x") + QString::number(ui->ioModulesTable->item(rows - 1, 1)->text().toInt(NULL, 0) + 1, 16));
        }
    }
}

void MainWindow::on_delIoModuleBtn_clicked()
{
    int row;

    if(ui->ioModulesTable->rowCount() > 0)
    {
        row = ui->ioModulesTable->currentRow();
        ui->ioModulesTable->removeRow(row);
    }
}

void MainWindow::on_addJsn2Btn_clicked()
{
    QTableWidgetItem *prev_item;
    int rows = ui->jsn2ModulesTable->rowCount();
    if(rows < JSN2_MODULE_COUNT)
    {
        ui->jsn2ModulesTable->insertRow(rows);
        if(rows > 0)
        {
            prev_item = ui->jsn2ModulesTable->item(rows - 1, 0);
            ui->jsn2ModulesTable->setItem(rows, 0, new QTableWidgetItem());
            ui->jsn2ModulesTable->item(rows, 0)->setText(QString::number(prev_item->text().toInt(NULL, 0) + 1));
        }
    }
}

void MainWindow::on_delJsn2Btn_clicked()
{
    int row;

    if(ui->jsn2ModulesTable->rowCount() > 0)
    {
        row = ui->jsn2ModulesTable->currentRow();
        ui->jsn2ModulesTable->removeRow(row);
    }
}

void MainWindow::on_addMeterBtn_clicked()
{
    int rows = ui->energyMetersTab->rowCount();
    if(rows < METER_COUNT)
    {
        ui->energyMetersTab->insertRow(rows);
    }
}

void MainWindow::on_delMeterBtn_clicked()
{
    int row;

    if(ui->energyMetersTab->rowCount() > 0)
    {
        row = ui->energyMetersTab->currentRow();
        ui->energyMetersTab->removeRow(row);
    }
}

void MainWindow::on_generalTempSensorTypeCmb_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:     //TH
        ui->generalTempSensorAddrLbl->setText("Nr modułu TH");
        ui->generalTempSensorAddr->setMinimum(1);
        ui->generalTempSensorAddr->setMaximum(IO_MODULE_COUNT);
        ui->generalTempSensorRegNoLbl->setText("Nr kanału TH");
        ui->generalTempSensorRegNo->setMinimum(1);
        ui->generalTempSensorRegNo->setMaximum(4);
        break;
    case 1:     //CAN
        ui->generalTempSensorAddrLbl->setText("Adres CAN");
        ui->generalTempSensorAddr->setMinimum(1);
        ui->generalTempSensorAddr->setMaximum(255);
        ui->generalTempSensorRegNoLbl->setText("Nr meldunku");
        ui->generalTempSensorRegNo->setMinimum(0);
        ui->generalTempSensorRegNo->setMaximum(127);
        break;
    case 2:     //Modbus
        ui->generalTempSensorAddrLbl->setText("Adres Modbus");
        ui->generalTempSensorAddr->setMinimum(1);
        ui->generalTempSensorAddr->setMaximum(255);
        ui->generalTempSensorRegNoLbl->setText("Nr rejestru");
        ui->generalTempSensorRegNo->setMinimum(0);
        ui->generalTempSensorRegNo->setMaximum(65535);
        break;
    }
}

void MainWindow::on_generalFallSensorTypeCmb_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:     //IO
        ui->generalFallSensorAddrLbl->setText("Nr modułu IO");
        ui->generalFallSensorAddr->setMinimum(1);
        ui->generalFallSensorAddr->setMaximum(IO_MODULE_COUNT);
        ui->generalFallSensorBitNoLbl->setText("Nr wejścia");
        ui->generalFallSensorBitNo->setMinimum(1);
        ui->generalFallSensorBitNo->setMaximum(20);
        ui->generalFallSensorRegNoLbl->setVisible(false);
        ui->generalFallSensorRegNo->setVisible(false);
        break;
    case 1:     //CAN
        ui->generalFallSensorAddrLbl->setText("Adres CAN");
        ui->generalFallSensorAddr->setMinimum(1);
        ui->generalFallSensorAddr->setMaximum(255);
        ui->generalFallSensorBitNoLbl->setText("Nr bitu");
        ui->generalFallSensorBitNo->setMinimum(1);
        ui->generalFallSensorBitNo->setMaximum(16);
        ui->generalFallSensorRegNoLbl->setVisible(true);
        ui->generalFallSensorRegNoLbl->setText("Nr meldunku");
        ui->generalFallSensorRegNo->setMinimum(0);
        ui->generalFallSensorRegNo->setMaximum(127);
        ui->generalFallSensorRegNo->setVisible(true);
        break;
    case 2:     //Modbus
        ui->generalFallSensorAddrLbl->setText("Adres Modbus");
        ui->generalFallSensorAddr->setMinimum(1);
        ui->generalFallSensorAddr->setMaximum(255);
        ui->generalFallSensorBitNoLbl->setText("Nr bitu");
        ui->generalFallSensorBitNo->setMinimum(1);
        ui->generalFallSensorBitNo->setMaximum(16);
        ui->generalFallSensorRegNoLbl->setVisible(true);
        ui->generalFallSensorRegNoLbl->setText("Nr rejestru");
        ui->generalFallSensorRegNo->setMinimum(0);
        ui->generalFallSensorRegNo->setMaximum(65535);
        ui->generalFallSensorRegNo->setVisible(true);
        break;
    }
}

void MainWindow::on_weatherAutomList_currentRowChanged(int currentRow)
{

}

void MainWindow::on_editWeatherAutomBtn_clicked()
{
    if(ui->editWeatherAutomBtn->text() == "Zmień ustawienia")
    {
        ui->editWeatherAutomBtn->setText("Zapisz zmiany");
        ui->weatherAutomList->setEnabled(false);
    }
    else
    {
        ui->editWeatherAutomBtn->setText("Zmień ustawienia");
        ui->weatherAutomList->setEnabled(true);
    }
}

void MainWindow::on_weatherAutomCount_valueChanged(int arg1)
{

}
