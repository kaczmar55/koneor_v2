#include "cgeneralcfgform.h"
#include "ui_cgeneralcfgform.h"

#include <QTextCodec>

CGeneralCfgForm::CGeneralCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CGeneralCfgForm)
{
    ui->setupUi(this);
}

CGeneralCfgForm::~CGeneralCfgForm()
{
    delete ui;
}

bool CGeneralCfgForm::getCfg(void* cfg_struct)
{
    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-2");
    general_cfg_t *general_cfg = (general_cfg_t*)cfg_struct;

    memset(general_cfg, 0, sizeof(general_cfg_t));
    strcpy(general_cfg->name, codec->fromUnicode(ui->objName->text()).data());
    strncpy(general_cfg->description, codec->fromUnicode(ui->objDescription->toPlainText()).data(), 255);
    general_cfg->cir_count = ui->cirCount->value();
    general_cfg->weather_autom_count = ui->weatherAutomCount->value();
    general_cfg->ctrl_group_cnt = 6;
    general_cfg->ind_on_time = ui->indOnTime->value();
    general_cfg->phase_asymmetry_check = ui->phaseAssymetryCheck->isChecked();
    general_cfg->phase_assymetry_tolerance = ui->phaseAssymetryTolerance->value();
    general_cfg->min_phase_voltage = ui->minPhaseVoltage->value();
    general_cfg->ctrl_user_level = ui->ctrlUserLevel->value();
    general_cfg->param_edit_user_level = ui->paramEditUserLevel->value();
    general_cfg->screen_saver_enable = ui->screenSaverEnable->isChecked();
    general_cfg->screen_saver_time = ui->screenSaverTime->value();
    general_cfg->wet_sign_hold_time = ui->wetSignHoldTime->value();

    return true;
}

bool CGeneralCfgForm::setCfg(void* cfg_struct)
{
    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-2");
    general_cfg_t *general_cfg = (general_cfg_t*)cfg_struct;

    ui->objName->setText(codec->toUnicode(general_cfg->name));
    ui->objDescription->setPlainText(codec->toUnicode(general_cfg->description));
    ui->cirCount->setValue(general_cfg->cir_count);
    ui->weatherAutomCount->setValue(general_cfg->weather_autom_count);
    ui->indOnTime->setValue(general_cfg->ind_on_time);
    if(general_cfg->phase_asymmetry_check == 0)
        ui->phaseAssymetryCheck->setChecked(false);
    else
        ui->phaseAssymetryCheck->setChecked(true);
    ui->phaseAssymetryTolerance->setValue(general_cfg->phase_assymetry_tolerance);
    ui->minPhaseVoltage->setValue(general_cfg->min_phase_voltage);
    ui->ctrlUserLevel->setValue(general_cfg->ctrl_user_level);
    ui->paramEditUserLevel->setValue(general_cfg->param_edit_user_level);
    if(general_cfg->screen_saver_enable == 0)
        ui->screenSaverEnable->setChecked(false);
    else
        ui->screenSaverEnable->setChecked(true);
    ui->screenSaverTime->setValue(general_cfg->screen_saver_time);
    ui->wetSignHoldTime->setValue(general_cfg->wet_sign_hold_time);

    return true;
}

void CGeneralCfgForm::on_cirCount_valueChanged(int arg1)
{
    emit cirCountChange(arg1);
}

void CGeneralCfgForm::on_weatherAutomCount_valueChanged(int arg1)
{
    emit weatherAutomCountChange(arg1);
}

void CGeneralCfgForm::setFileVer(uint8_t ver, uint8_t rev)
{
    ui->fileVer->setText(QString("%1.%2").arg(ver).arg(rev));
}


void CGeneralCfgForm::setFileSize(uint32_t len)
{
    ui->fileSize->setText(QString::number(len));
}
