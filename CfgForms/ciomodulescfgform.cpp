#include "ciomodulescfgform.h"
#include "ui_ciomodulescfgform.h"

#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>

CIoModulesCfgForm::CIoModulesCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CIoModulesCfgForm)
{
    ui->setupUi(this);

    ui->ioModulesTable->setColumnWidth(2, 50);
    ui->jsn2ModulesTable->setColumnWidth(1, 104);
    ui->energyMetersTab->setColumnWidth(1, 104);

}

CIoModulesCfgForm::~CIoModulesCfgForm()
{
    delete ui;
}

bool CIoModulesCfgForm::setCfg(void *cfg_struct)
{
    QTableWidget *ioModuleTable = ui->ioModulesTable;
    int i, row;
    QComboBox *cb;
    io_module_cfg_t *io_module_cfg = (io_module_cfg_t*)cfg_struct;

    while(ioModuleTable->rowCount() > 0)
        ioModuleTable->removeRow(ioModuleTable->rowCount() - 1);
    for(i = 0; i < IO_MODULE_COUNT; i++)
    {
        if(io_module_cfg[i].type != 0)
        {
            cb = new QComboBox();
            cb->addItem(QString("IO10/5"), IO10_5_TYPE);
            cb->addItem(QString("TH"), TH_TYPE);
            cb->addItem(QString("I12"), I12_TYPE);
            cb->addItem(QString("I20"), I20_TYPE);
            cb->addItem(QString("O10"), O10_TYPE);
            cb->addItem(QString("CVM"), CVM_TYPE);
            cb->addItem(QString("ISC3"), ISC3_TYPE);
            cb->addItem(QString("IO4/7"), IO4_7_TYPE);
            cb->addItem(QString("O8"), O8_TYPE);
            cb->addItem(QString("GMR IO"), GMR_IO_TYPE);

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

bool CIoModulesCfgForm::getCfg(void *cfg_struct)
{    
    int count = ui->ioModulesTable->rowCount();
    int i;
    QComboBox* cmb;
    bool ok = true;
    io_module_cfg_t *io_module_cfg = (io_module_cfg_t*)cfg_struct;

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

void CIoModulesCfgForm::on_addIoModuleBtn_clicked()
{
    QComboBox* cb;
    QComboBox* prev_cb;

    int rows = ui->ioModulesTable->rowCount();
    if(rows < IO_MODULE_COUNT)
    {
        ui->ioModulesTable->insertRow(rows);

        cb = new QComboBox();
        cb->addItem(QString("IO10/5"), IO10_5_TYPE);
        cb->addItem(QString("TH"), TH_TYPE);
        cb->addItem(QString("I12"), I12_TYPE);
        cb->addItem(QString("I20"), I20_TYPE);
        cb->addItem(QString("O10"), O10_TYPE);
        cb->addItem(QString("CVM"), CVM_TYPE);
        cb->addItem(QString("ISC3"), ISC3_TYPE);
        cb->addItem(QString("IO4/7"), IO4_7_TYPE);
        cb->addItem(QString("O8"), O8_TYPE);
        cb->addItem(QString("GMR IO"), GMR_IO_TYPE);

        ui->ioModulesTable->setCellWidget(rows, 0, cb);
        ui->ioModulesTable->setItem(rows, 1, new QTableWidgetItem());
        if(rows == 0)
        {
            ui->ioModulesTable->item(0, 1)->setText("0x12");
        }
        else
        {
            prev_cb = (QComboBox*)ui->ioModulesTable->cellWidget(rows - 1, 0);
            cb->setCurrentIndex(prev_cb->currentIndex());
            ui->ioModulesTable->item(rows, 1)->setText(QString("0x") + QString::number(ui->ioModulesTable->item(rows - 1, 1)->text().toInt(NULL, 0) + 1, 16));
        }
    }
}

void CIoModulesCfgForm::on_delIoModuleBtn_clicked()
{
    int row;

    if(ui->ioModulesTable->rowCount() > 0)
    {
        row = ui->ioModulesTable->currentRow();
        ui->ioModulesTable->removeRow(row);
    }
}

bool CIoModulesCfgForm::getCfgJsn2(jsn2_module_cfg_t *jsn2_module_cfg)
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
        jsn2_module_cfg[i].com_no = ui->jsn2ModulesTable->item(i, 1)->text().toInt(&ok, 0);
        if(ok == false)
            break;
    }

    return ok;
}

bool CIoModulesCfgForm::setCfgJsn2(jsn2_module_cfg_t *jsn2_module_cfg)
{
    QTableWidget *jsn2Table = ui->jsn2ModulesTable;
    int i, row;

    while(jsn2Table->rowCount() > 0)
        jsn2Table->removeRow(jsn2Table->rowCount() - 1);
    for(i = 0; i < JSN2_MODULE_COUNT; i++)
    {
        if(jsn2_module_cfg[i].type != 0)
        {
            row = jsn2Table->rowCount();
            jsn2Table->insertRow(row);
            jsn2Table->setItem(row, 0, new QTableWidgetItem());
            jsn2Table->item(row, 0)->setText(QString::number(jsn2_module_cfg[i].addr));
            jsn2Table->setItem(row, 1, new QTableWidgetItem());
            jsn2Table->item(row, 1)->setText(QString::number(jsn2_module_cfg[i].com_no));
        }
    }
    return true;
}

void CIoModulesCfgForm::on_addJsn2Btn_clicked()
{
    QTableWidgetItem *prev_item;
    int rows = ui->jsn2ModulesTable->rowCount();
    if(rows < JSN2_MODULE_COUNT)
    {
        ui->jsn2ModulesTable->insertRow(rows);
        if(rows > 0)
        {
            prev_item = ui->jsn2ModulesTable->item(rows - 1, 0);
            if(prev_item != NULL)
            {
                ui->jsn2ModulesTable->setItem(rows, 0, new QTableWidgetItem());
                ui->jsn2ModulesTable->item(rows, 0)->setText(QString::number(prev_item->text().toInt(NULL, 0) + 1));
            }

            prev_item = ui->jsn2ModulesTable->item(rows - 1, 1);
            if(prev_item != NULL)
            {
                ui->jsn2ModulesTable->setItem(rows, 1, new QTableWidgetItem());
                ui->jsn2ModulesTable->item(rows, 1)->setText(QString::number(prev_item->text().toInt(NULL, 0)));
            }
        }
    }
}

void CIoModulesCfgForm::on_delJsn2Btn_clicked()
{
    int row;

    if(ui->jsn2ModulesTable->rowCount() > 0)
    {
        row = ui->jsn2ModulesTable->currentRow();
        ui->jsn2ModulesTable->removeRow(row);
    }
}

bool CIoModulesCfgForm::getCfgMeter(meter_cfg_t *meter_cfg)
{
    int count = ui->energyMetersTab->rowCount();
    int i;
    bool ok = true;

    memset(meter_cfg, 0, sizeof(meter_cfg_t) * METER_COUNT);
    for(i = 0; i < count; i++)
    {
        meter_cfg[i].type = 1;
        strncpy(meter_cfg[i].id, ui->energyMetersTab->item(i, 0)->text().toUtf8().data(), 14);
        meter_cfg[i].com_no = ui->energyMetersTab->item(i, 1)->text().toInt(&ok, 0);
        if(ok == false)
            break;
    }

    return ok;
}

bool CIoModulesCfgForm::setCfgMeter(meter_cfg_t *meter_cfg)
{
    QTableWidget *energyMetersTab = ui->energyMetersTab;
    int i, row;

    while(energyMetersTab->rowCount() > 0)
        energyMetersTab->removeRow(energyMetersTab->rowCount() - 1);
    for(i = 0; i < METER_COUNT; i++)
    {
        if(meter_cfg[i].type != 0)
        {
            row = energyMetersTab->rowCount();
            energyMetersTab->insertRow(row);
            energyMetersTab->setItem(row, 0, new QTableWidgetItem());
            energyMetersTab->item(row, 0)->setText(meter_cfg[i].id);
            energyMetersTab->setItem(row, 1, new QTableWidgetItem());
            energyMetersTab->item(row, 1)->setText(QString::number(meter_cfg[i].com_no));
        }
    }
    return true;
}

void CIoModulesCfgForm::on_addMeterBtn_clicked()
{
    QTableWidgetItem *prev_item;

    int rows = ui->energyMetersTab->rowCount();
    if(rows < METER_COUNT)
    {
        ui->energyMetersTab->insertRow(rows);
        if(rows > 0)
        {
            prev_item = ui->energyMetersTab->item(rows - 1, 1);
            if(prev_item != NULL)
            {
                ui->energyMetersTab->setItem(rows, 1, new QTableWidgetItem());
                ui->energyMetersTab->item(rows, 1)->setText(QString::number(prev_item->text().toInt(NULL, 0)));
            }
        }
    }
}

void CIoModulesCfgForm::on_delMeterBtn_clicked()
{
    int row;

    if(ui->energyMetersTab->rowCount() > 0)
    {
        row = ui->energyMetersTab->currentRow();
        ui->energyMetersTab->removeRow(row);
    }
}
