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
    CCircuitCfgForm *circuitCfgForm;
    CEthernetCfgForm *ethernetCfgForm;
    CGeneralCfgForm *generalCfgForm;
    int newIndex = current->data(0, Qt::UserRole).toInt();
    int prevIndex;
    bool ok = true;

    if(previous == NULL)
        prevIndex = -1;
    else
        prevIndex = previous->data(0, Qt::UserRole).toInt();

    if(doNotChange)
    {
        doNotChange = false;
        ok = false;
    }
    else
    {
        switch(prevIndex)
        {
        case GENERAL_CFG_FORM_ID:
            generalCfgForm = (CGeneralCfgForm*)ui->stackedWidget->widget(prevIndex);
            if(generalCfgForm)
                ok = generalCfgForm->getCfg(&general_cfg);
            break;
        case IO_MODULES_FORM_ID:
            break;
        case GENERAL_WEATHER_MEASURE_FORM_ID:
            break;
        case TEMPERATURES_FORM_ID:
            break;
        case WEATHER_AUTOM_FORM_ID:
            break;
        case CIRCUIT_FORM_ID:
            if((prevIndex != newIndex) || (previous->data(0, Qt::UserRole + 1) != current->data(0, Qt::UserRole + 1)))
            {
                circuitCfgForm = (CCircuitCfgForm*)ui->stackedWidget->widget(prevIndex);
                if(circuitCfgForm)
                    ok = circuitCfgForm->getCfg(&circuit_cfg[previous->data(0, Qt::UserRole + 1).toInt()]);
            }
            else
            {
                ok = false;
            }
            break;
        case IO_FORM_ID:
            break;
        case RS232_FORM_ID:
            break;
        case ETHERNET_FORM_ID:
            ethernetCfgForm = (CEthernetCfgForm*)ui->stackedWidget->widget(prevIndex);
            if(ethernetCfgForm)
                ok = ethernetCfgForm->getCfg(&eth_cfg);
            break;
        case MODBUS_SLAVE_FORM_ID:
            break;
        case CAN_FORM_ID:
            break;
        case TGFM_FORM_ID:
            break;
        case USERS_FORM_ID:
            break;
        }

        if(ok)
        {
            switch(newIndex)
            {
            case GENERAL_CFG_FORM_ID:
                generalCfgForm = (CGeneralCfgForm*)ui->stackedWidget->widget(newIndex);
                if(generalCfgForm)
                    ok = generalCfgForm->setCfg(&general_cfg);
                break;
            case IO_MODULES_FORM_ID:
                break;
            case GENERAL_WEATHER_MEASURE_FORM_ID:
                break;
            case TEMPERATURES_FORM_ID:
                break;
            case WEATHER_AUTOM_FORM_ID:
                break;
            case CIRCUIT_FORM_ID:
                circuitCfgForm = (CCircuitCfgForm*)ui->stackedWidget->widget(newIndex);
                if(circuitCfgForm)
                    circuitCfgForm->setCfg(&circuit_cfg[current->data(0, Qt::UserRole + 1).toInt()]);
                break;
            case IO_FORM_ID:
                break;
            case RS232_FORM_ID:
                break;
            case ETHERNET_FORM_ID:
                ethernetCfgForm = (CEthernetCfgForm*)ui->stackedWidget->widget(newIndex);
                if(ethernetCfgForm)
                    ok = ethernetCfgForm->setCfg(&eth_cfg);
                break;
            case MODBUS_SLAVE_FORM_ID:
                break;
            case CAN_FORM_ID:
                break;
            case TGFM_FORM_ID:
                break;
            case USERS_FORM_ID:
                break;
            }
            ui->stackedWidget->setCurrentIndex(newIndex);
            current->setExpanded(true);
        }
        else
        {
            doNotChange = true;
            ui->menuTreeWidget->setCurrentItem(previous);//, 0, QItemSelectionModel::Select);
        }
    }
    if((current->text(0) == "Automaty pogodowe") &&
            ((previous->parent() == NULL) ||
                ((previous->parent() != NULL) && (previous->parent()->text(0) != "Automaty pogodowe"))))
    {
        qDebug() << "Główny z automatami";
    }
    else if((current->parent() != NULL) && (current->parent()->text(0) == "Automaty pogodowe"))
    {
        qDebug() << "Jeden z automatów pogodowych";
    }
    else if((current->text(0) == "Obwody sterowania") &&
                ((previous->parent() == NULL) ||
                    ((previous->parent() != NULL) && (previous->parent()->text(0) != "Obwody sterowania"))))
    {
        qDebug() << "Główny z obwodami";
    }
    else if((current->parent() != NULL) && (current->parent()->text(0) == "Obwody sterowania"))
    {
        qDebug() << "Jeden z obwodów sterowania";
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
