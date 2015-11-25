#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CfgForms/cgeneralcfgform.h"
#include "CfgForms/ciomodulescfgform.h"
#include "CfgForms/cgeneralweathermeasureform.h"
#include "CfgForms/ctemperaturescfgform.h"
#include "CfgForms/cweatherautomform.h"
#include "CfgForms/ccircuitcfgform.h"
#include "CfgForms/ciocfgform.h"
#include "CfgForms/crs232cfgform.h"
#include "CfgForms/cethernetcfgform.h"
#include "CfgForms/cmodbusslavecfgform.h"
#include "CfgForms/ccancfgform.h"
#include "CfgForms/cuserscfgform.h"
#include "eor_cfg.hpp"
#include "crc16.hpp"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#define GENERAL_CFG_FORM_ID     (0)
#define IO_MODULES_FORM_ID      (1)
#define GENERAL_WEATHER_MEASURE_FORM_ID (2)
#define TEMPERATURES_FORM_ID    (3)
#define WEATHER_AUTOM_FORM_ID   (4)
#define CIRCUIT_FORM_ID         (5)
#define IO_FORM_ID              (6)
#define RS232_FORM_ID           (7)
#define ETHERNET_FORM_ID        (8)
#define MODBUS_SLAVE_FORM_ID    (9)
#define CAN_FORM_ID             (10)
#define USERS_FORM_ID           (11)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    CGeneralCfgForm *generalCfgForm;
    QTreeWidgetItem *item, *childItem;
    int i;

    ui->setupUi(this);

    open_save_path = "koneor.bin";
    doNotChange = false;

    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->actionOtw_rz->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->actionZapisz->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->actionZako_cz->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogCloseButton));

    generalCfgForm = new CGeneralCfgForm();
    QObject::connect(generalCfgForm, &CGeneralCfgForm::cirCountChange, this, &MainWindow::on_cirCountChanged);
    QObject::connect(generalCfgForm, &CGeneralCfgForm::weatherAutomCountChange, this, &MainWindow::on_weatherAutomCountChanged);
    item = addForm("Podstawowe", generalCfgForm, GENERAL_CFG_FORM_ID, 0, NULL);
    ui->menuTreeWidget->setCurrentItem(item);
    ui->stackedWidget->setCurrentIndex(0);

    addForm("Moduły", new CIoModulesCfgForm(), IO_MODULES_FORM_ID, 0, NULL);
    addForm("Podstawowe pomiary pogody", new CGeneralWeatherMeasureForm(), GENERAL_WEATHER_MEASURE_FORM_ID, 0, NULL);
    addForm("Temperatury", new CTemperaturesCfgForm(), TEMPERATURES_FORM_ID, 0, NULL);
    item = addForm("Automaty pogodowe", new CWeatherAutomForm(), WEATHER_AUTOM_FORM_ID, 0, NULL);
    weatherAutomItem = item;

    for(i = 0; i < WEATHER_AUTOM_COUNT; i++)
    {
        childItem = new QTreeWidgetItem();
        childItem->setText(0, QString("Automat nr %1").arg(i + 1));
        childItem->setData(0, Qt::UserRole, WEATHER_AUTOM_FORM_ID);
        childItem->setData(0, Qt::UserRole + 1, i);
        item->addChild(childItem);
        if(i == 0)
            childItem->setHidden(false);
        else
            childItem->setHidden(true);
    }

    item = addForm("Obwody sterowania", new CCircuitCfgForm(), CIRCUIT_FORM_ID, 0, NULL);
    circuitItem = item;
    for(i = 0; i < CIRCUIT_COUNT; i++)
    {
        childItem = new QTreeWidgetItem();
        childItem->setText(0, QString("Obwód nr %1").arg(i + 1));
        childItem->setData(0, Qt::UserRole, CIRCUIT_FORM_ID);
        childItem->setData(0, Qt::UserRole + 1, i);
        item->addChild(childItem);
        if(i == 0)
            childItem->setHidden(false);
        else
            childItem->setHidden(true);
    }

    addForm("Dodatkowe wejścia", new CIOCfgForm(), IO_FORM_ID, 0, NULL);
    item = addForm("Komunikacja", new CRs232CfgForm(), RS232_FORM_ID, 0, NULL);
    childItem = new QTreeWidgetItem();
    childItem->setText(0, "Rs232/485");
    childItem->setData(0, Qt::UserRole, RS232_FORM_ID);
    childItem->setData(0, Qt::UserRole + 1, 0);
    item->addChild(childItem);
    addForm("Ethernet", new CEthernetCfgForm(), ETHERNET_FORM_ID, 0, item);
    addForm("Modbus Slave", new CModbusSlaveCfgForm(), MODBUS_SLAVE_FORM_ID, 0, item);
    addForm("CAN", new CCanCfgForm(), CAN_FORM_ID, 0, item);
    addForm("Użytkownicy", new CUsersCfgForm(), USERS_FORM_ID, 0, NULL);

/*    qDebug() << "general_cfg_t = " << sizeof(general_cfg_t);
    qDebug() << "user_cfg_t = " << sizeof(user_cfg_t);
    qDebug() << "io_module_cfg_t = " << sizeof(io_module_cfg_t);
    qDebug() << "jsn2_module_cfg_t = " << sizeof(jsn2_module_cfg_t);
    qDebug() << "meter_cfg_t = " << sizeof(meter_cfg_t);
    qDebug() << "general_weather_measure_cfg_t = " << sizeof(general_weather_measure_cfg_t);
    qDebug() << "weather_autom_cfg_t = " << sizeof(weather_autom_cfg_t);
    qDebug() << "temperatures_cfg_t = " << sizeof(temperatures_cfg_t);
    qDebug() << "circuit_cfg_t = " << sizeof(circuit_cfg_t);
    qDebug() << "group_cfg_t = " << sizeof(group_cfg_t);
    qDebug() << "io_cfg_t = " << sizeof(io_cfg_t);
    qDebug() << "can_cfg_t = " << sizeof(can_cfg_t);
    qDebug() << "modbus_slave_cfg_t = " << sizeof(modbus_slave_cfg_t);
    qDebug() << "tgfm_cfg_t = " << sizeof(tgfm_cfg_t);
    qDebug() << "rs_cfg_t = " << sizeof(rs_cfg_t);
    qDebug() << "eth_cfg_t = " << sizeof(eth_cfg_t);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidgetItem *MainWindow::addForm(QString name, QWidget* widget, int id1, int id2, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item;

    ui->stackedWidget->addWidget(widget);

    item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setData(0, Qt::UserRole, id1);
    item->setData(0, Qt::UserRole + 1, id2);
    if(parent == NULL)
        ui->menuTreeWidget->addTopLevelItem(item);
    else
        parent->addChild(item);

    return item;
}

void MainWindow::on_menuTreeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    CMyForm *myForm;
    CIoModulesCfgForm *ioModulesCfgForm;
    int newIndex = current->data(0, Qt::UserRole).toInt();
    int prevIndex;
    bool ok = true;

    if(previous == NULL)
        prevIndex = -1;
    else
        prevIndex = previous->data(0, Qt::UserRole).toInt();

    if(doNotChange == true)
    {
        doNotChange = false;
    }
    else
    {
        switch(prevIndex)
        {
        case WEATHER_AUTOM_FORM_ID:
        case CIRCUIT_FORM_ID:
            if((prevIndex != newIndex) || (previous->data(0, Qt::UserRole + 1) != current->data(0, Qt::UserRole + 1)))
                getCfgFromForm(prevIndex, previous->data(0, Qt::UserRole + 1).toInt());
            else
                return;
            break;
        default:
            ok = getCfgFromForm(prevIndex, 0);
            break;
        }

        if(ok == true)
        {
            myForm = (CMyForm*)ui->stackedWidget->widget(newIndex);
            if(myForm != NULL)
            {
                switch(newIndex)
                {
                case GENERAL_CFG_FORM_ID:
                    myForm->setCfg(&general_cfg);
                    break;
                case IO_MODULES_FORM_ID:
                    myForm->setCfg(io_module_cfg);
                    ioModulesCfgForm = (CIoModulesCfgForm*)myForm;
                    ioModulesCfgForm->setCfgMeter(meter_cfg);
                    ioModulesCfgForm->setCfgJsn2(jsn2_module_cfg);
                    break;
                case GENERAL_WEATHER_MEASURE_FORM_ID:
                    myForm->setCfg(&general_weather_measure_cfg);
                    break;
                case TEMPERATURES_FORM_ID:
                    myForm->setCfg(&temperatures_cfg);
                    break;
                case WEATHER_AUTOM_FORM_ID:
                    myForm->setCfg(&weather_autom_cfg[current->data(0, Qt::UserRole + 1).toInt()]);
                    break;
                case CIRCUIT_FORM_ID:
                    myForm->setCfg(&circuit_cfg[current->data(0, Qt::UserRole + 1).toInt()]);
                    break;
                case IO_FORM_ID:
                    myForm->setCfg(&io_cfg);
                    break;
                case RS232_FORM_ID:
                    myForm->setCfg(rs_cfg);
                    break;
                case ETHERNET_FORM_ID:
                    myForm->setCfg(&eth_cfg);
                    break;
                case MODBUS_SLAVE_FORM_ID:
                    myForm->setCfg(&modbus_slave_cfg);
                    break;
                case CAN_FORM_ID:
                    myForm->setCfg(&can_cfg);
                    break;
                case USERS_FORM_ID:
                    myForm->setCfg(user_cfg);
                    break;
                }
            }
            ui->stackedWidget->setCurrentIndex(newIndex);
            current->setExpanded(true);
        }
/*        else
        {
            doNotChange = true;
            ui->menuTreeWidget->setCurrentItem(previous);//, 0, QItemSelectionModel::Select);
        }*/
    }
}

void MainWindow::on_actionZako_cz_triggered()
{
    close();
}

void MainWindow::on_cirCountChanged(int new_circuit_count)
{
    int i;

    if(circuitItem)
    {
        for(i = 0; i < circuitItem->childCount(); i++)
        {
            if(i < new_circuit_count)
               circuitItem->child(i)->setHidden(false);
            else
                circuitItem->child(i)->setHidden(true);
        }
    }
}

void MainWindow::on_weatherAutomCountChanged(int new_weather_autom_count)
{
    int i;

    if(weatherAutomItem)
    {
        for(i = 0; i < weatherAutomItem->childCount(); i++)
        {
            if(i < new_weather_autom_count)
               weatherAutomItem->child(i)->setHidden(false);
            else
                weatherAutomItem->child(i)->setHidden(true);
        }
    }
}

void MainWindow::on_actionOtw_rz_triggered()
{
    QString fileNameToOpen;
    QFile file;
    QByteArray fileBuf;
    uint16_t crc16;
    CGeneralCfgForm *myForm;

    QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "", "");
    msgBox->setWindowFlags(msgBox->windowFlags() | Qt::WindowStaysOnTopHint);
    msgBox->setWindowTitle("Błąd");

    fileNameToOpen = QFileDialog::getOpenFileName(this, "Otwórz plik konfiguracji", open_save_path, "*.bin");

    if(fileNameToOpen == "")
    {
    //anuluj
    }
    else
    {
        open_save_path = fileNameToOpen;
        file.setFileName(fileNameToOpen);
        if(file.open(QIODevice::ReadOnly))
        {
            fileBuf = file.readAll();
            file.close();

            if(fileBuf.size() < (eorkonf_data_size + sizeof(eorkonf_hdr_t)))
            {
                msgBox->setText(QString("Plik jest zbyt mały. Dane nie zostały wczytane\n") +
                                QString("Wczytano: ") + QString::number(fileBuf.size()) +
                                QString(" B\nOczekiwano: ") + QString::number(eorkonf_data_size + sizeof(eorkonf_hdr_t)) +
                                QString(" B"));
                msgBox->exec();
/*                QMessageBox::critical(this, "Błąd", QString("Plik jest zbyt mały. Dane nie zostały wczytane\n") +
                                      QString("Wczytano: ") + QString::number(fileBuf.size()) +
                                      QString(" B\nOczekiwano: ") + QString::number(eorkonf_data_size + sizeof(eorkonf_hdr_t)) +
                                      QString(" B"));*/
                delete msgBox;
                return;
            }
            else if(fileBuf.size() > (eorkonf_data_size + sizeof(eorkonf_hdr_t)))
            {
                msgBox->setText(QString("Plik jest za duży. Wczytane dane mogą być błędne\n") +
                                QString("Wczytano: ") + QString::number(fileBuf.size()) +
                                QString(" B\nOczekiwano: ") + QString::number(eorkonf_data_size + sizeof(eorkonf_hdr_t)) +
                                QString(" B"));
                msgBox->exec();
/*                QMessageBox::critical(this, "Błąd", QString("Plik jest za duży. Wczytane dane mogą być błędne\n") +
                                      QString("Wczytano: ") + QString::number(fileBuf.size()) +
                                      QString(" B\nOczekiwano: ") + QString::number(eorkonf_data_size + sizeof(eorkonf_hdr_t)) +
                                      QString(" B"));*/
            }

            myForm = (CGeneralCfgForm*)ui->stackedWidget->widget(GENERAL_CFG_FORM_ID);
            ui->menuTreeWidget->setCurrentItem(ui->menuTreeWidget->topLevelItem(0));

            setCfgStructs(fileBuf.data());
            crc16 = LiczCrc16Buf((uint8_t*)&fileBuf.data()[sizeof(eorkonf_hdr_t)], eorkonf_data_size);
            if(eorkonf_hdr.crc16 != crc16)
            {
                msgBox->setText(QString("Nieprawidłowe crc pliku. Wczytane dane mogą być błędne\n") +
                                QString("Obliczone: 0x") + QString::number(crc16, 16) +
                                QString("\nOczekiwano: 0x") + QString::number(eorkonf_hdr.crc16, 16));
                msgBox->exec();
/*                QMessageBox::critical(this, "Błąd", QString("Nieprawidłowe crc pliku. Wczytane dane mogą być błędne\n") +
                                      QString("Obliczone: 0x") + QString::number(crc16, 16) +
                                      QString("\nOczekiwano: 0x") + QString::number(eorkonf_hdr.crc16, 16));*/
            }

            if(eorkonf_hdr.file_len != eorkonf_data_size)
            {
                msgBox->setText(QString("Nieprawidłowy rozmiar danych w nagłówku\n") +
                                QString("Odczytane: ") + QString::number(eorkonf_hdr.file_len) +
                                QString(" B\nOczekiwano: ") + QString::number(eorkonf_data_size) +
                                QString(" B"));
                msgBox->exec();
/*                QMessageBox::critical(this, "Błąd", QString("Nieprawidłowy rozmiar danych w nagłówku\n") +
                                      QString("Odczytane: ") + QString::number(eorkonf_hdr.file_len) +
                                      QString(" B\nOczekiwano: ") + QString::number(eorkonf_data_size) +
                                      QString(" B"));*/
            }

            if(strncmp(eorkonf_hdr.id_txt, "EOR_KON", 7) != 0)
            {
                msgBox->setText("Brak w nagłówku znacznika EOR_KON. Wczytane dane mogą być nieprawidłowe\n");
                msgBox->exec();
                //QMessageBox::critical(this, "Błąd", "Brak w nagłówku znacznika EOR_KON. Wczytane dane mogą być nieprawidłowe\n");
            }

            //myForm = (CGeneralCfgForm*)ui->stackedWidget->widget(GENERAL_CFG_FORM_ID);
            myForm->setCfg(&general_cfg);
            myForm->setFileVer(eorkonf_hdr.ver, eorkonf_hdr.rev);
            myForm->setFileSize(eorkonf_hdr.file_len + sizeof(eorkonf_hdr_t));
            //ui->menuTreeWidget->setCurrentItem(ui->menuTreeWidget->topLevelItem(0));
        }
        else
        {
            msgBox->setText("Wystąpił błąd podczas otwierania pliku do odczytu");
            msgBox->exec();
            //QMessageBox::critical(this, "Błąd", "Wystąpił błąd podczas otwierania pliku do odczytu");
        }
    }

    delete msgBox;
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

    memcpy(&temperatures_cfg, &buf[index], sizeof(temperatures_cfg_t));
    index += sizeof(temperatures_cfg_t);

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

void MainWindow::on_actionZapisz_triggered()
{
    QString fileNameToSave;
    QFile file;
    QByteArray fileBuf;
    qint64 ret;
    char* cBuf;
    eorkonf_hdr_t *tmp_eorkonf_hdr;

    QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "", "");
    msgBox->setWindowFlags(msgBox->windowFlags() | Qt::WindowStaysOnTopHint);
    msgBox->setWindowTitle("Błąd");

    fileNameToSave = QFileDialog::getSaveFileName(this, "Zapisz plik konfiguracji", open_save_path, "*.bin");

    if(fileNameToSave == "")
    {
    //anuluj
    }
    else
    {
        open_save_path = fileNameToSave;
        file.setFileName(fileNameToSave);
        if(file.open(QIODevice::WriteOnly))
        {
            eorkonf_hdr.ver = 1;
            eorkonf_hdr.rev = 0;
            eorkonf_hdr.file_len = eorkonf_data_size;
            strcpy(eorkonf_hdr.id_txt, "EOR_KON");
            fileBuf.append((char*)&eorkonf_hdr, sizeof(eorkonf_hdr_t));
            //todo na koniec crc16

            getCfgFromForm(ui->stackedWidget->currentIndex(), ui->menuTreeWidget->currentItem()->data(0, Qt::UserRole + 1).toInt());
            fileBuf.append((char*)&general_cfg, sizeof(general_cfg_t));
            fileBuf.append((char*)user_cfg, sizeof(user_cfg_t) * USER_COUNT);
            fileBuf.append((char*)io_module_cfg, sizeof(io_module_cfg_t) * IO_MODULE_COUNT);
            fileBuf.append((char*)jsn2_module_cfg, sizeof(jsn2_module_cfg_t) * JSN2_MODULE_COUNT);
            fileBuf.append((char*)meter_cfg, sizeof(meter_cfg_t) * METER_COUNT);
            fileBuf.append((char*)&general_weather_measure_cfg, sizeof(general_weather_measure_cfg_t));
            fileBuf.append((char*)weather_autom_cfg, sizeof(weather_autom_cfg_t) * WEATHER_AUTOM_COUNT);
            fileBuf.append((char*)&temperatures_cfg, sizeof(temperatures_cfg_t));
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
            {
                msgBox->setText(QString("Błąd podczas zapisu pliku na dysk."));
                msgBox->exec();
                //QMessageBox::critical(this, "Błąd", QString("Błąd podczas zapisu pliku na dysk."));
            }
            else if(ret < (eorkonf_data_size + sizeof(eorkonf_hdr_t)))
            {
                msgBox->setText(QString("Błąd podczas zapisu danych na dysku\n") +
                                QString("Zapisano: ") + QString::number(ret) +
                                QString(" B\nPowinno być: ") + QString::number(eorkonf_data_size + sizeof(eorkonf_hdr_t)) +
                                QString(" B"));
                msgBox->exec();
/*                QMessageBox::critical(this, "Błąd", QString("Błąd podczas zapisu danych na dysku\n") +
                                      QString("Zapisano: ") + QString::number(ret) +
                                      QString(" B\nPowinno być: ") + QString::number(eorkonf_data_size + sizeof(eorkonf_hdr_t)) +
                                      QString(" B"));*/
            }
            file.close();
        }
        else
        {
            msgBox->setText("Wystąpił błąd podczas otwierania pliku do zapisu");
            msgBox->exec();
//            QMessageBox::critical(this, "Błąd", "Wystąpił błąd podczas otwierania pliku do zapisu");
        }
    }
}

bool MainWindow::getCfgFromForm(int index, int id)
{
    CIoModulesCfgForm *ioModulesCfgForm;
    CMyForm *myForm = (CMyForm*)ui->stackedWidget->widget(index);
    bool ok = true;
    uint8_t i;

    if(myForm)
    {
        switch(index)
        {
        case GENERAL_CFG_FORM_ID:
            ok = myForm->getCfg(&general_cfg);
            break;
        case IO_MODULES_FORM_ID:
            ok = myForm->getCfg(io_module_cfg);
            ioModulesCfgForm = (CIoModulesCfgForm*)myForm;
            ioModulesCfgForm->getCfgMeter(meter_cfg);
            ioModulesCfgForm->getCfgJsn2(jsn2_module_cfg);
            break;
        case GENERAL_WEATHER_MEASURE_FORM_ID:
            ok = myForm->getCfg(&general_weather_measure_cfg);
            break;
        case TEMPERATURES_FORM_ID:
            ok = myForm->getCfg(&temperatures_cfg);
            break;
        case WEATHER_AUTOM_FORM_ID:
            ok = myForm->getCfg(&weather_autom_cfg[id]);
            for(i = 0; i < CIRCUIT_COUNT; i++)
                circuit_cfg[i].reference = 0;
            for(i = 0; i < general_cfg.weather_autom_count; i++)
                circuit_cfg[weather_autom_cfg[i].referenceCircuitNo - 1].reference = 1;
            break;
        case CIRCUIT_FORM_ID:
            ok = myForm->getCfg(&circuit_cfg[id]);
            break;
        case IO_FORM_ID:
            ok = myForm->getCfg(&io_cfg);
            break;
        case RS232_FORM_ID:
            ok = myForm->getCfg(rs_cfg);
            break;
        case ETHERNET_FORM_ID:
            ok = myForm->getCfg(&eth_cfg);
            break;
        case MODBUS_SLAVE_FORM_ID:
            ok = myForm->getCfg(&modbus_slave_cfg);
            break;
        case CAN_FORM_ID:
            ok = myForm->getCfg(&can_cfg);
            break;
        case USERS_FORM_ID:
            ok = myForm->getCfg(user_cfg);
            break;
        }
    }
    return ok;
}
