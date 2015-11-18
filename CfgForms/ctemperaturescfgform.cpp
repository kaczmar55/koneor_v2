#include "ctemperaturescfgform.h"
#include "ui_ctemperaturescfgform.h"

CTemperaturesCfgForm::CTemperaturesCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CTemperaturesCfgForm)
{
    ui->setupUi(this);
}

CTemperaturesCfgForm::~CTemperaturesCfgForm()
{
    delete ui;
}

bool CTemperaturesCfgForm::setCfg(void *cfg_struct)
{
    temperatures_cfg_t *temperatures_cfg = (temperatures_cfg_t*)cfg_struct;

    ui->TROnFrSpin->setValue(temperatures_cfg->t_r_on_fr / 10.0);
    ui->TROffFrSpin->setValue(temperatures_cfg->t_r_off_fr / 10.0);
    ui->TROnWetSpin->setValue(temperatures_cfg->t_r_on_wet / 10.0);
    ui->TROffWetSpin->setValue(temperatures_cfg->t_r_off_wet / 10.0);
    ui->TROnSnSpin->setValue(temperatures_cfg->t_r_on_sn / 10.0);
    ui->TROffSnSpin->setValue(temperatures_cfg->t_r_off_sn / 10.0);

    ui->TFrostOnRSpin->setValue(temperatures_cfg->t_frost_on_r / 10.0);
    ui->TFrostOffRSpin->setValue(temperatures_cfg->t_frost_off_r / 10.0);

    ui->tLocksOn->setValue(temperatures_cfg->t_frost_on_l / 10.0);
    ui->tLocksOff->setValue(temperatures_cfg->t_frost_off_l / 10.0);

    ui->tWetFreezing->setValue(temperatures_cfg->t_wet_freezing / 10.0);
    ui->tIsSnowFall->setValue(temperatures_cfg->t_is_snow_fall / 10.0);
    return true;
}

bool CTemperaturesCfgForm::getCfg(void *cfg_struct)
{
    temperatures_cfg_t *temperatures_cfg = (temperatures_cfg_t*)cfg_struct;

    memset(temperatures_cfg, 0, sizeof(temperatures_cfg_t));

    temperatures_cfg->t_r_on_fr = ui->TROnFrSpin->value() * 10;
    temperatures_cfg->t_r_off_fr = ui->TROffFrSpin->value() * 10;
    temperatures_cfg->t_r_on_wet = ui->TROnWetSpin->value() * 10;
    temperatures_cfg->t_r_off_wet = ui->TROffWetSpin->value() * 10;
    temperatures_cfg->t_r_on_sn = ui->TROnSnSpin->value() * 10;
    temperatures_cfg->t_r_off_sn = ui->TROffSnSpin->value() * 10;

    temperatures_cfg->t_frost_on_r = ui->TFrostOnRSpin->value() * 10;
    temperatures_cfg->t_frost_off_r = ui->TFrostOffRSpin->value() * 10;

    temperatures_cfg->t_frost_on_l = ui->tLocksOn->value() * 10;
    temperatures_cfg->t_frost_off_l = ui->tLocksOff->value() * 10;

    temperatures_cfg->t_wet_freezing = ui->tWetFreezing->value() * 10;
    temperatures_cfg->t_is_snow_fall = ui->tIsSnowFall->value() * 10;
    return true;
}

void CTemperaturesCfgForm::on_ecoBtn_clicked()
{
    ui->TROnFrSpin->setValue(1.0);
    ui->TROffFrSpin->setValue(3.0);
    ui->TROnWetSpin->setValue(2.0);
    ui->TROffWetSpin->setValue(5.0);
    ui->TROnSnSpin->setValue(2.0);
    ui->TROffSnSpin->setValue(5.0);

    ui->TFrostOnRSpin->setValue(-15.0);
    ui->TFrostOffRSpin->setValue(-12.0);

    ui->tLocksOn->setValue(0.0);
    ui->tLocksOff->setValue(2.0);

    ui->tWetFreezing->setValue(0.0);
    ui->tIsSnowFall->setValue(0.5);
}

void CTemperaturesCfgForm::on_stdBtn_clicked()
{
    ui->TROnFrSpin->setValue(1.0);
    ui->TROffFrSpin->setValue(3.0);
    ui->TROnWetSpin->setValue(4.0);
    ui->TROffWetSpin->setValue(7.0);
    ui->TROnSnSpin->setValue(4.0);
    ui->TROffSnSpin->setValue(7.0);

    ui->TFrostOnRSpin->setValue(-10.0);
    ui->TFrostOffRSpin->setValue(-7.0);

    ui->tLocksOn->setValue(0.0);
    ui->tLocksOff->setValue(2.0);

    ui->tWetFreezing->setValue(0.0);
    ui->tIsSnowFall->setValue(0.5);
}

void CTemperaturesCfgForm::on_maxBtn_clicked()
{
    ui->TROnFrSpin->setValue(1.0);
    ui->TROffFrSpin->setValue(3.0);
    ui->TROnWetSpin->setValue(6.0);
    ui->TROffWetSpin->setValue(10.0);
    ui->TROnSnSpin->setValue(6.0);
    ui->TROffSnSpin->setValue(10.0);

    ui->TFrostOnRSpin->setValue(-7.0);
    ui->TFrostOffRSpin->setValue(-4.0);

    ui->tLocksOn->setValue(0.0);
    ui->tLocksOff->setValue(2.0);

    ui->tWetFreezing->setValue(0.0);
    ui->tIsSnowFall->setValue(0.5);
}
