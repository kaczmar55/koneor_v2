#include "ciocfgform.h"
#include "ui_ciocfgform.h"

CIOCfgForm::CIOCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CIOCfgForm)
{
    ui->setupUi(this);
}

CIOCfgForm::~CIOCfgForm()
{
    delete ui;
}

bool CIOCfgForm::setCfg(void *cfg_struct)
{
    io_cfg_t *io_cfg = (io_cfg_t*)cfg_struct;

    if(io_cfg->door.active == 0)
        ui->dorChk->setChecked(false);
    else
        ui->dorChk->setChecked(true);
    ui->dorIOMod->setValue(io_cfg->door.module_id);
    ui->dorBitNo->setValue(io_cfg->door.bit_no);

    if(io_cfg->break_in.active == 0)
        ui->breakInChk->setChecked(false);
    else
        ui->breakInChk->setChecked(true);
    ui->breakInIOMod->setValue(io_cfg->break_in.module_id);
    ui->breakInBitNo->setValue(io_cfg->break_in.bit_no);

    if(io_cfg->surge_protect.active == 0)
        ui->surgeProtectChk->setChecked(false);
    else
        ui->surgeProtectChk->setChecked(true);
    ui->surgeProtectIOMod->setValue(io_cfg->surge_protect.module_id);
    ui->surgeProtectBitNo->setValue(io_cfg->surge_protect.bit_no);

    if(io_cfg->remote_ctrl.active == 0)
        ui->remoteCtrlChk->setChecked(false);
    else
        ui->remoteCtrlChk->setChecked(true);
    ui->remoteCtrlIOMod->setValue(io_cfg->remote_ctrl.module_id);
    ui->remoteCtrlBitNo->setValue(io_cfg->remote_ctrl.bit_no);

    ui->localCtrlChk->setChecked(true);
    ui->localCtrlIOMod->setValue(io_cfg->local_ctrl.module_id);
    ui->localCtrlBitNo->setValue(io_cfg->local_ctrl.bit_no);

    ui->handCtrlChk->setChecked(true);
    ui->handCtrlIOMod->setValue(io_cfg->hand_ctrl.module_id);
    ui->handCtrlBitNo->setValue(io_cfg->hand_ctrl.bit_no);

    if(io_cfg->lock_ctrl.active != 0)
        ui->lockCtrlChk->setChecked(true);
    else
        ui->lockCtrlChk->setChecked(false);
    ui->lockCtrlIOMod->setValue(io_cfg->lock_ctrl.module_id);
    ui->lockCtrlBitNo->setValue(io_cfg->lock_ctrl.bit_no);
    return true;
}

bool CIOCfgForm::getCfg(void *cfg_struct)
{
    io_cfg_t *io_cfg = (io_cfg_t*)cfg_struct;

    memset(io_cfg, 0, sizeof(io_cfg_t));

    io_cfg->door.active = ui->dorChk->isChecked();
    io_cfg->door.module_id = ui->dorIOMod->value();
    io_cfg->door.bit_no = ui->dorBitNo->value();
    if(io_cfg->door.active != 0)
        checkIoMod(io_cfg->door.module_id, 0, "Otwarcie drzwi szafy");

    io_cfg->break_in.active = ui->breakInChk->isChecked();
    io_cfg->break_in.module_id = ui->breakInIOMod->value();
    io_cfg->break_in.bit_no = ui->breakInBitNo->value();
    if(io_cfg->break_in.active != 0)
        checkIoMod(io_cfg->break_in.module_id, 0, "Otwarcie klapy transformatora");

    io_cfg->surge_protect.active = ui->surgeProtectChk->isChecked();
    io_cfg->surge_protect.module_id = ui->surgeProtectIOMod->value();
    io_cfg->surge_protect.bit_no = ui->surgeProtectBitNo->value();
    if(io_cfg->surge_protect.active != 0)
        checkIoMod(io_cfg->surge_protect.module_id, 0, "Potwierdzenie zabezpieczenia antyprzepięciowego");

    io_cfg->remote_ctrl.active = ui->remoteCtrlChk->isChecked();
    io_cfg->remote_ctrl.module_id = ui->remoteCtrlIOMod->value();
    io_cfg->remote_ctrl.bit_no = ui->remoteCtrlBitNo->value();
    if(io_cfg->remote_ctrl.active != 0)
        checkIoMod(io_cfg->remote_ctrl.module_id, 0, "Sterowanie zdalne");

    io_cfg->local_ctrl.active = ui->localCtrlChk->isChecked();
    io_cfg->local_ctrl.module_id = ui->localCtrlIOMod->value();
    io_cfg->local_ctrl.bit_no = ui->localCtrlBitNo->value();
    if(io_cfg->local_ctrl.active != 0)
        checkIoMod(io_cfg->local_ctrl.module_id, 0, "Sterowanie lokalne");

    io_cfg->hand_ctrl.active = ui->handCtrlChk->isChecked();
    io_cfg->hand_ctrl.module_id = ui->handCtrlIOMod->value();
    io_cfg->hand_ctrl.bit_no = ui->handCtrlBitNo->value();
    if(io_cfg->hand_ctrl.active != 0)
        checkIoMod(io_cfg->hand_ctrl.module_id, 0, "Sterowanie ręczne");

    io_cfg->lock_ctrl.active = ui->lockCtrlChk->isChecked();
    io_cfg->lock_ctrl.module_id = ui->lockCtrlIOMod->value();
    io_cfg->lock_ctrl.bit_no = ui->lockCtrlBitNo->value();
    if(io_cfg->lock_ctrl.active != 0)
        checkIoMod(io_cfg->lock_ctrl.module_id, 0, "Blokada sterowania");

    return true;
}
