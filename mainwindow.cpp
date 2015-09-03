#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CfgForms/cgeneralcfgform.h"
#include "CfgForms/ciomodulescfgform.h"
#include "CfgForms/cgeneralweathermeasureform.h"
#include "CfgForms/ctemperaturescfgform.h"
#include "CfgForms/cweatherautomform.h"
#include "CfgForms/ccircuitcfgform.h"
#include "eor_cfg.hpp"
#include <QDebug>

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

    item = addForm("Podstawowe", new CGeneralCfgForm(), 0);
    ui->menuTreeWidget->setCurrentItem(item);
    ui->stackedWidget->setCurrentIndex(0);

    addForm("Moduły", new CIoModulesCfgForm(), 1);
    addForm("Podstawowe pomiary pogody", new CGeneralWeatherMeasureForm(), 2);
    addForm("Temperatury", new CTemperaturesCfgForm(), 3);
    item = addForm("Automaty pogodowe", new CWeatherAutomForm(), 4);
    for(i = 0; i < WEATHER_AUTOM_COUNT; i++)
    {
        childItem = new QTreeWidgetItem();
        childItem->setText(0, QString("Automat nr %1").arg(i + 1));
        childItem->setData(0, Qt::UserRole, 4);
        childItem->setData(0, Qt::UserRole + 1, i);
        item->addChild(childItem);
        if(i == 0)
            childItem->setHidden(false);
        else
            childItem->setHidden(true);
    }

    item = addForm("Obwody sterowania", new CCircuitCfgForm(), 5);
    for(i = 0; i < CIRCUIT_COUNT; i++)
    {
        childItem = new QTreeWidgetItem();
        childItem->setText(0, QString("Obwód nr %1").arg(i + 1));
        childItem->setData(0, Qt::UserRole, 5);
        childItem->setData(0, Qt::UserRole + 1, i);
        item->addChild(childItem);
        if(i == 0)
            childItem->setHidden(false);
        else
            childItem->setHidden(true);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidgetItem *MainWindow::addForm(QString name, QWidget* widget, int id)
{
    QTreeWidgetItem *item;

    ui->stackedWidget->addWidget(widget);

    item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setData(0, Qt::UserRole, id);
    item->setData(0, Qt::UserRole + 1, 0);
    ui->menuTreeWidget->addTopLevelItem(item);

    return item;
}

void MainWindow::on_menuTreeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    (void)previous;
    int newIndex = current->data(0, Qt::UserRole).toInt();

    ui->stackedWidget->setCurrentIndex(newIndex);
    current->setExpanded(true);
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
