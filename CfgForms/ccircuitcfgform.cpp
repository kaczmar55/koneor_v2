#include "ccircuitcfgform.h"
#include "ui_ccircuitcfgform.h"
#include <QTextCodec>

CCircuitCfgForm::CCircuitCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CCircuitCfgForm)
{
    ui->setupUi(this);
}

CCircuitCfgForm::~CCircuitCfgForm()
{
    delete ui;
}

bool CCircuitCfgForm::setCfg(void *cfg_struct)
{
    circuit_cfg_t *circuit_cfg = (circuit_cfg_t*)cfg_struct;
    int ioModulesCount = 0;

    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-2");

    while((io_module_cfg[ioModulesCount].type != 0) && (io_module_cfg[ioModulesCount].type != CVM_TYPE))
        ioModulesCount++;

    ui->cirNameEdit->setText(codec->toUnicode(circuit_cfg->name));
    ui->cirDescriptionEdit->setText(codec->toUnicode(circuit_cfg->description));
    if(circuit_cfg->active == 0)
        ui->cirActiveChk->setChecked(false);
    else
        ui->cirActiveChk->setChecked(true);
    if(circuit_cfg->reference == 0)
        ui->cirReferenceChk->setChecked(false);
    else
        ui->cirReferenceChk->setChecked(true);
    ui->cirTypeCmb->setCurrentIndex(circuit_cfg->type);
    ui->cirGroupNo->setValue(circuit_cfg->group_id);
    ui->cirWeatherAutomNo->setValue(circuit_cfg->weather_autom_id);

    if(circuit_cfg->phase_cfg[0].active == 0)
        ui->l1ActiveChk->setChecked(false);
    else
        ui->l1ActiveChk->setChecked(true);
    if(circuit_cfg->phase_cfg[0].conf_input.active ==0)
        ui->l1ConfActiveChk->setChecked(false);
    else
        ui->l1ConfActiveChk->setChecked(true);
    ui->l1ConfIOMod->setValue(circuit_cfg->phase_cfg[0].conf_input.module_id);
    ui->l1ConfBitNo->setValue(circuit_cfg->phase_cfg[0].conf_input.bit_no);

    ui->l1CvmId->setValue(circuit_cfg->phase_cfg[0].cvm_id - ioModulesCount);
    ui->l1CvmCh->setValue(circuit_cfg->phase_cfg[0].cvm_ch_id);

    ui->p1Nominal->setValue(circuit_cfg->phase_cfg[0].p_nom / 10.0);
    ui->p1Tol->setValue(circuit_cfg->phase_cfg[0].p_tol / 10.0);
    ui->p1Factor->setCurrentIndex(circuit_cfg->phase_cfg[0].p_factor);

    if(circuit_cfg->phase_cfg[1].active == 0)
        ui->l2ActiveChk->setChecked(false);
    else
        ui->l2ActiveChk->setChecked(true);
    if(circuit_cfg->phase_cfg[1].conf_input.active ==0)
        ui->l2ConfActiveChk->setChecked(false);
    else
        ui->l2ConfActiveChk->setChecked(true);
    ui->l2ConfIOMod->setValue(circuit_cfg->phase_cfg[1].conf_input.module_id);
    ui->l2ConfBitNo->setValue(circuit_cfg->phase_cfg[1].conf_input.bit_no);

    ui->l2CvmId->setValue(circuit_cfg->phase_cfg[1].cvm_id - ioModulesCount);
    ui->l2CvmCh->setValue(circuit_cfg->phase_cfg[1].cvm_ch_id);

    ui->p2Nominal->setValue(circuit_cfg->phase_cfg[1].p_nom / 10.0);
    ui->p2Tol->setValue(circuit_cfg->phase_cfg[1].p_tol / 10.0);
    ui->p2Factor->setCurrentIndex(circuit_cfg->phase_cfg[1].p_factor);

    if(circuit_cfg->phase_cfg[2].active == 0)
        ui->l3ActiveChk->setChecked(false);
    else
        ui->l3ActiveChk->setChecked(true);
    if(circuit_cfg->phase_cfg[2].conf_input.active ==0)
        ui->l3ConfActiveChk->setChecked(false);
    else
        ui->l3ConfActiveChk->setChecked(true);
    ui->l3ConfIOMod->setValue(circuit_cfg->phase_cfg[2].conf_input.module_id);
    ui->l3ConfBitNo->setValue(circuit_cfg->phase_cfg[2].conf_input.bit_no);

    ui->l3CvmId->setValue(circuit_cfg->phase_cfg[2].cvm_id - ioModulesCount);
    ui->l3CvmCh->setValue(circuit_cfg->phase_cfg[2].cvm_ch_id);

    ui->p3Nominal->setValue(circuit_cfg->phase_cfg[2].p_nom / 10.0);
    ui->p3Tol->setValue(circuit_cfg->phase_cfg[2].p_tol / 10.0);
    ui->p3Factor->setCurrentIndex(circuit_cfg->phase_cfg[2].p_factor);

    ui->cirRelIOMod->setValue(circuit_cfg->relay.module_id);
    ui->cirRelBitNo->setValue(circuit_cfg->relay.bit_no);
    ui->cirRelConfIOMod->setValue(circuit_cfg->rel_conf.module_id);
    ui->cirRelConfBitNo->setValue(circuit_cfg->rel_conf.bit_no);

    return true;
}

bool CCircuitCfgForm::getCfg(void *cfg_struct)
{
    circuit_cfg_t *circuit_cfg = (circuit_cfg_t*)cfg_struct;
    int i;
    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-2");
    int ioModulesCount = 0;

    while((io_module_cfg[ioModulesCount].type != 0) && (io_module_cfg[ioModulesCount].type != CVM_TYPE))
        ioModulesCount++;

    memset(circuit_cfg, 0, sizeof(circuit_cfg_t));

    strcpy(circuit_cfg->name, codec->fromUnicode(ui->cirNameEdit->text()).data());
    strcpy(circuit_cfg->description, codec->fromUnicode(ui->cirDescriptionEdit->text()).data());
    circuit_cfg->active = ui->cirActiveChk->isChecked();
    circuit_cfg->reference = ui->cirReferenceChk->isChecked();
    circuit_cfg->type = ui->cirTypeCmb->currentIndex();
    circuit_cfg->group_id = ui->cirGroupNo->value();
    circuit_cfg->weather_autom_id = ui->cirWeatherAutomNo->value();

    circuit_cfg->phase_cfg[0].active = ui->l1ActiveChk->isChecked();
    circuit_cfg->phase_cfg[0].conf_input.active = ui->l1ConfActiveChk->isChecked();
    circuit_cfg->phase_cfg[0].conf_input.module_id = ui->l1ConfIOMod->value();
    circuit_cfg->phase_cfg[0].conf_input.bit_no = ui->l1ConfBitNo->value();

    circuit_cfg->phase_cfg[0].cvm_id = ui->l1CvmId->value() + ioModulesCount;
    circuit_cfg->phase_cfg[0].cvm_ch_id = ui->l1CvmCh->value();

    circuit_cfg->phase_cfg[0].p_nom = ui->p1Nominal->value() * 10;
    circuit_cfg->phase_cfg[0].p_tol = ui->p1Tol->value() * 10;
    circuit_cfg->phase_cfg[0].p_factor = ui->p1Factor->currentIndex();

    circuit_cfg->phase_cfg[1].active = ui->l2ActiveChk->isChecked();
    circuit_cfg->phase_cfg[1].conf_input.active = ui->l2ConfActiveChk->isChecked();
    circuit_cfg->phase_cfg[1].conf_input.module_id = ui->l2ConfIOMod->value();
    circuit_cfg->phase_cfg[1].conf_input.bit_no = ui->l2ConfBitNo->value();

    circuit_cfg->phase_cfg[1].cvm_id = ui->l2CvmId->value() + ioModulesCount;
    circuit_cfg->phase_cfg[1].cvm_ch_id = ui->l2CvmCh->value();

    circuit_cfg->phase_cfg[1].p_nom = ui->p2Nominal->value() * 10;
    circuit_cfg->phase_cfg[1].p_tol = ui->p2Tol->value() * 10;
    circuit_cfg->phase_cfg[1].p_factor = ui->p2Factor->currentIndex();

    circuit_cfg->phase_cfg[2].active = ui->l3ActiveChk->isChecked();
    circuit_cfg->phase_cfg[2].conf_input.active = ui->l3ConfActiveChk->isChecked();
    circuit_cfg->phase_cfg[2].conf_input.module_id = ui->l3ConfIOMod->value();
    circuit_cfg->phase_cfg[2].conf_input.bit_no = ui->l3ConfBitNo->value();

    circuit_cfg->phase_cfg[2].cvm_id = ui->l3CvmId->value() + ioModulesCount;
    circuit_cfg->phase_cfg[2].cvm_ch_id = ui->l3CvmCh->value();

    circuit_cfg->phase_cfg[2].p_nom = ui->p3Nominal->value() * 10;
    circuit_cfg->phase_cfg[2].p_tol = ui->p3Tol->value() * 10;
    circuit_cfg->phase_cfg[2].p_factor = ui->p3Factor->currentIndex();

    circuit_cfg->relay.active = 1;
    circuit_cfg->relay.module_id = ui->cirRelIOMod->value();
    circuit_cfg->relay.bit_no = ui->cirRelBitNo->value();
    circuit_cfg->rel_conf.active = 1;
    circuit_cfg->rel_conf.module_id = ui->cirRelConfIOMod->value();
    circuit_cfg->rel_conf.bit_no = ui->cirRelConfBitNo->value();

    if(checkIoMod(circuit_cfg->rel_conf.module_id, 0, "Potwierdzenie stycznika") == 1)
        return false;

    if(checkIoMod(circuit_cfg->relay.module_id, 1, "Sterowanie stycznikem") == 1)
        return false;

    for(i = 0; i < 3; i++)
    {
        if((circuit_cfg->phase_cfg[i].active != 0) &&
                (circuit_cfg->phase_cfg[i].conf_input.active != 0))
        {
            if(checkIoMod(circuit_cfg->phase_cfg[i].conf_input.module_id, 0, QString("Potwierdzenie zabezpieczenia fazy L%1").arg(i + 1)) == 1)
                return false;

            if(checkIoMod(circuit_cfg->phase_cfg[i].cvm_id, 3, QString("Moduł CVM fazy L%1").arg(i + 1)) == 1)
                return false;
        }
    }
    return true;
}

void CCircuitCfgForm::on_l1ActiveChk_toggled(bool checked)
{
    if(checked)
    {
        ui->l1ConfActiveChk->setEnabled(true);
        ui->l1ConfIOMod->setEnabled(true);
        ui->l1ConfBitNo->setEnabled(true);
        ui->l1CvmId->setEnabled(true);
        ui->l1CvmCh->setEnabled(true);
        ui->p1Nominal->setEnabled(true);
        ui->p1Tol->setEnabled(true);
        ui->p1Factor->setEnabled(true);
    }
    else
    {
        ui->l1ConfActiveChk->setEnabled(false);
        ui->l1ConfIOMod->setEnabled(false);
        ui->l1ConfBitNo->setEnabled(false);
        ui->l1CvmId->setEnabled(false);
        ui->l1CvmCh->setEnabled(false);
        ui->p1Nominal->setEnabled(false);
        ui->p1Tol->setEnabled(false);
        ui->p1Factor->setEnabled(false);
    }
}

void CCircuitCfgForm::on_l2ActiveChk_toggled(bool checked)
{
    if(checked)
    {
        ui->l2ConfActiveChk->setEnabled(true);
        ui->l2ConfIOMod->setEnabled(true);
        ui->l2ConfBitNo->setEnabled(true);
        ui->l2CvmId->setEnabled(true);
        ui->l2CvmCh->setEnabled(true);
        ui->p2Nominal->setEnabled(true);
        ui->p2Tol->setEnabled(true);
        ui->p2Factor->setEnabled(true);
    }
    else
    {
        ui->l2ConfActiveChk->setEnabled(false);
        ui->l2ConfIOMod->setEnabled(false);
        ui->l2ConfBitNo->setEnabled(false);
        ui->l2CvmId->setEnabled(false);
        ui->l2CvmCh->setEnabled(false);
        ui->p2Nominal->setEnabled(false);
        ui->p2Tol->setEnabled(false);
        ui->p2Factor->setEnabled(false);
    }
}

void CCircuitCfgForm::on_l3ActiveChk_toggled(bool checked)
{
    if(checked)
    {
        ui->l3ConfActiveChk->setEnabled(true);
        ui->l3ConfIOMod->setEnabled(true);
        ui->l3ConfBitNo->setEnabled(true);
        ui->l3CvmId->setEnabled(true);
        ui->l3CvmCh->setEnabled(true);
        ui->p3Nominal->setEnabled(true);
        ui->p3Tol->setEnabled(true);
        ui->p3Factor->setEnabled(true);
    }
    else
    {
        ui->l3ConfActiveChk->setEnabled(false);
        ui->l3ConfIOMod->setEnabled(false);
        ui->l3ConfBitNo->setEnabled(false);
        ui->l3CvmId->setEnabled(false);
        ui->l3CvmCh->setEnabled(false);
        ui->p3Nominal->setEnabled(false);
        ui->p3Tol->setEnabled(false);
        ui->p3Factor->setEnabled(false);
    }
}
