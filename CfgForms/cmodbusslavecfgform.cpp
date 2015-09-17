#include "cmodbusslavecfgform.h"
#include "ui_cmodbusslavecfgform.h"

CModbusSlaveCfgForm::CModbusSlaveCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CModbusSlaveCfgForm)
{
    ui->setupUi(this);
}

CModbusSlaveCfgForm::~CModbusSlaveCfgForm()
{
    delete ui;
}

bool CModbusSlaveCfgForm::setCfg(void *cfg_struct)
{
    modbus_slave_cfg_t *modbus_slave_cfg = (modbus_slave_cfg_t*)cfg_struct;

    if(modbus_slave_cfg->active == 0)
        ui->modbusSlaveActiveChk->setChecked(false);
    else
        ui->modbusSlaveActiveChk->setChecked(true);
    ui->modbusSlaveAddr->setValue(modbus_slave_cfg->addr);
    ui->modbusSlaveMediumCmb->setCurrentIndex(modbus_slave_cfg->transmission_medium);
    ui->modbusSlavePort->setValue(modbus_slave_cfg->port_no);
    if(modbus_slave_cfg->accept_cmd == 0)
        ui->modbusSlaveAcceptCmdChk->setChecked(false);
    else
        ui->modbusSlaveAcceptCmdChk->setChecked(true);

    return true;
}

bool CModbusSlaveCfgForm::getCfg(void *cfg_struct)
{
    modbus_slave_cfg_t *modbus_slave_cfg = (modbus_slave_cfg_t*)cfg_struct;

    memset(modbus_slave_cfg, 0, sizeof(modbus_slave_cfg_t));
    modbus_slave_cfg->active = ui->modbusSlaveActiveChk->isChecked();
    modbus_slave_cfg->addr = ui->modbusSlaveAddr->value();
    modbus_slave_cfg->transmission_medium = ui->modbusSlaveMediumCmb->currentIndex();
    modbus_slave_cfg->port_no = ui->modbusSlavePort->value();
    modbus_slave_cfg->accept_cmd = ui->modbusSlaveAcceptCmdChk->isChecked();
    return true;
}

void CModbusSlaveCfgForm::on_modbusSlaveMediumCmb_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        ui->modbusSlavePort->setMinimum(1);
        ui->modbusSlavePort->setMaximum(6);
        break;
    case 1:
        ui->modbusSlavePort->setMinimum(0);
        ui->modbusSlavePort->setMaximum(65535);
        ui->modbusSlavePort->setValue(502);
        break;
    }
}
