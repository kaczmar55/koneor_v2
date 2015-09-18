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
#include "CfgForms/ctgfmcfgform.h"
#include "CfgForms/cuserscfgform.h"
#include "eor_cfg.hpp"
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
#define TGFM_FORM_ID            (11)
#define USERS_FORM_ID           (12)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    CGeneralCfgForm *generalCfgForm;
    QTreeWidgetItem *item, *childItem;
    int i;

    ui->setupUi(this);

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
    addForm("TGFM", new CTgfmCfgForm(), TGFM_FORM_ID, 0, item);
    addForm("Użytkownicy", new CUsersCfgForm(), USERS_FORM_ID, 0, NULL);

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
        myForm = (CMyForm*)ui->stackedWidget->widget(prevIndex);
        if(myForm)
        {
            switch(prevIndex)
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
                break;
            case WEATHER_AUTOM_FORM_ID:
                if((prevIndex != newIndex) || (previous->data(0, Qt::UserRole + 1) != current->data(0, Qt::UserRole + 1)))
                    ok = myForm->getCfg(&weather_autom_cfg[previous->data(0, Qt::UserRole + 1).toInt()]);
                else
                    return;
                break;
            case CIRCUIT_FORM_ID:
                if((prevIndex != newIndex) || (previous->data(0, Qt::UserRole + 1) != current->data(0, Qt::UserRole + 1)))
                    ok = myForm->getCfg(&circuit_cfg[previous->data(0, Qt::UserRole + 1).toInt()]);
                else
                    return;
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
                break;
            case TGFM_FORM_ID:
                break;
            case USERS_FORM_ID:
                break;
            }
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
                    break;
                case TGFM_FORM_ID:
                    break;
                case USERS_FORM_ID:
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

    fileNameToOpen = QFileDialog::getOpenFileName(this, "Otwórz plik konfiguracji", "koneor.bin", "koneor.bin");

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

            if(fileBuf.size() < (eorkonf_data_size + sizeof(eorkonf_hdr_t)))
            {
                QMessageBox::critical(this, "Błąd", QString("Plik jest zbyt mały. Dane nie zostały wczytane\n") +
                                      QString("Wczytano: ") + QString::number(fileBuf.size()) +
                                      QString(" B\nOczekiwano: ") + QString::number(eorkonf_data_size + sizeof(eorkonf_hdr_t)) +
                                      QString(" B"));
                return;
            }
            else if(fileBuf.size() > (eorkonf_data_size + sizeof(eorkonf_hdr_t)))
            {
                QMessageBox::critical(this, "Błąd", QString("Plik jest za duży. Wczytane dane mogą być błędne\n") +
                                      QString("Wczytano: ") + QString::number(fileBuf.size()) +
                                      QString(" B\nOczekiwano: ") + QString::number(eorkonf_data_size + sizeof(eorkonf_hdr_t)) +
                                      QString(" B"));
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

//            ui->fileSize->setText(QString::number(eorkonf_hdr.file_len + sizeof(eorkonf_hdr_t)));
//            ui->fileVer->setText(QString("%1.%2").arg(eorkonf_hdr.ver).arg(eorkonf_hdr.rev));
            myForm = (CMyForm*)ui->stackedWidget->widget(GENERAL_CFG_FORM_ID);
            myForm->setCfg(&general_cfg);
            myForm->setFileVer(eorkonf_hdr.ver, eorkonf_hdr.rev);
            myForm->setFileSize(eorkonf_hdr.file_len + sizeof(eorkonf_hdr_t));
            ui->menuTreeWidget->setCurrentItem(ui->menuTreeWidget->topLevelItem(0));
        }
        else
        {
            QMessageBox::critical(this, "Błąd", "Wystąpił błąd podczas otwierania pliku do odczytu");
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
