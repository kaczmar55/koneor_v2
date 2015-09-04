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
#include "CfgForms/cethrtnetcfgform.h"
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
    QTreeWidgetItem *item, *childItem;
    int i;

    ui->setupUi(this);

    ui->actionOtw_rz->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->actionZapisz->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->actionZako_cz->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogCloseButton));

    item = addForm("Podstawowe", new CGeneralCfgForm(), GENERAL_CFG_FORM_ID, 0, NULL);
    ui->menuTreeWidget->setCurrentItem(item);
    ui->stackedWidget->setCurrentIndex(0);

    addForm("Moduły", new CIoModulesCfgForm(), IO_MODULES_FORM_ID, 0, NULL);
    addForm("Podstawowe pomiary pogody", new CGeneralWeatherMeasureForm(), GENERAL_WEATHER_MEASURE_FORM_ID, 0, NULL);
    addForm("Temperatury", new CTemperaturesCfgForm(), TEMPERATURES_FORM_ID, 0, NULL);
    item = addForm("Automaty pogodowe", new CWeatherAutomForm(), WEATHER_AUTOM_FORM_ID, 0, NULL);

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
    addForm("Ethernet", new CEthrtnetCfgForm(), ETHERNET_FORM_ID, 0, item);
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
    int newIndex = current->data(0, Qt::UserRole).toInt();
    int prevIndex;
    bool ok = true;

    if(previous == NULL)
        prevIndex = -1;
    else
        prevIndex = previous->data(0, Qt::UserRole).toInt();

    switch(prevIndex)
    {
    case GENERAL_CFG_FORM_ID:
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
        //do pomyślenia
        circuitCfgForm = (CCircuitCfgForm*)ui->stackedWidget->widget(prevIndex);
        ok = circuitCfgForm->getCfg(&circuit_cfg[previous->data(0, Qt::UserRole + 1).toInt()]);
        break;
    case IO_FORM_ID:
        break;
    case RS232_FORM_ID:
        break;
    case ETHERNET_FORM_ID:
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
            circuitCfgForm->setCfg(&circuit_cfg[current->data(0, Qt::UserRole + 1).toInt()]);
            break;
        case IO_FORM_ID:
            break;
        case RS232_FORM_ID:
            break;
        case ETHERNET_FORM_ID:
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
