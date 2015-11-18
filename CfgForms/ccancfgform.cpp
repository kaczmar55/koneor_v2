#include "ccancfgform.h"
#include "ui_ccancfgform.h"
#include "eor_cfg.hpp"
#include <string.h>

CCanCfgForm::CCanCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CCanCfgForm)
{
    ui->setupUi(this);
}

CCanCfgForm::~CCanCfgForm()
{
    delete ui;
}

bool CCanCfgForm::setCfg(void *cfg_struct)
{
    can_cfg_t *can_cfg = (can_cfg_t*)cfg_struct;

    if((can_cfg->can_no & CAN1ID) != 0)
        ui->can1ActiveChk->setChecked(true);
    else
        ui->can1ActiveChk->setChecked(false);

    if((can_cfg->can_no & CAN2ID) != 0)
        ui->can2ActiveChk->setChecked(true);
    else
        ui->can2ActiveChk->setChecked(false);

    if(can_cfg->accept_cmd != 0)
        ui->canAcceptCmd->setChecked(true);
    else
        ui->canAcceptCmd->setChecked(false);

    ui->canNoSpin->setValue(can_cfg->no);

    if(can_cfg->baud == 25)
        ui->canBaudCombo->setCurrentIndex(0);
    else
        ui->canBaudCombo->setCurrentIndex(1);

    if((can_cfg->can_functions & CAN_REPEATER_ENABLE) != 0)
        ui->canRepeaterActiveChk->setChecked(true);
    else
        ui->canRepeaterActiveChk->setChecked(false);

    if((can_cfg->can_functions & CAN_MON_ENABLE) != 0)
        ui->canMonEnableChk->setChecked(true);
    else
        ui->canMonEnableChk->setChecked(false);

    return true;
}

bool CCanCfgForm::getCfg(void *cfg_struct)
{
    can_cfg_t *can_cfg = (can_cfg_t*)cfg_struct;

    memset(can_cfg, 0, sizeof(can_cfg_t));

    if(ui->can1ActiveChk->isChecked())
        can_cfg->can_no |= CAN1ID;
    if(ui->can2ActiveChk->isChecked())
        can_cfg->can_no |= CAN2ID;
    if(can_cfg->can_no != 0)
        can_cfg->active = 1;

    if(ui->canAcceptCmd->isChecked())
        can_cfg->accept_cmd = 1;

    can_cfg->no = ui->canNoSpin->value();

    if(ui->canBaudCombo->currentIndex() == 0)
        can_cfg->baud = 25;
    else
        can_cfg->baud = 125;

    if(ui->canRepeaterActiveChk->isChecked())
        can_cfg->can_functions |= CAN_REPEATER_ENABLE;

    if(ui->canMonEnableChk->isChecked())
        can_cfg->can_functions |= CAN_MON_ENABLE;

    return true;
}
