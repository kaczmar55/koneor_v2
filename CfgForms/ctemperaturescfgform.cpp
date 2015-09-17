#include "ctemperaturescfgform.h"
#include "ui_ctemperaturescfgform.h"

CTemperaturesCfgForm::CTemperaturesCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CTemperaturesCfgForm)
{
    int i, j, row, col;
    QDoubleSpinBox *spin;

    ui->setupUi(this);

    row = ui->weatherAutomTempTable->rowCount();
    col = ui->weatherAutomTempTable->columnCount();

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            spin = new QDoubleSpinBox();
            spin->setMinimum(-50.0);
            spin->setMaximum(100.0);
            spin->setDecimals(1);
            spin->setSingleStep(0.1);
            ui->weatherAutomTempTable->setCellWidget(i, j, spin);
        }
    }
}

CTemperaturesCfgForm::~CTemperaturesCfgForm()
{
    delete ui;
}

bool CTemperaturesCfgForm::setCfg(void *cfg_struct)
{
    temperatures_cfg_t *temperatures_cfg = (temperatures_cfg_t*)cfg_struct;
    QDoubleSpinBox *spin;

    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(0, 0);
    spin->setValue(temperatures_cfg->t_r_on_fr / 10.0);
    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(0, 1);
    spin->setValue(temperatures_cfg->t_r_off_fr / 10.0);
    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(1, 0);
    spin->setValue(temperatures_cfg->t_r_on_wet / 10.0);
    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(1, 1);
    spin->setValue(temperatures_cfg->t_r_off_wet / 10.0);
    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(2, 0);
    spin->setValue(temperatures_cfg->t_r_on_sn / 10.0);
    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(2, 1);
    spin->setValue(temperatures_cfg->t_r_off_sn / 10.0);

    ui->frostTempIn->setValue(temperatures_cfg->t_frost_on_r / 10.0);
    ui->frostTempOut->setValue(temperatures_cfg->t_frost_off_r / 10.0);

    ui->tLocksOn->setValue(temperatures_cfg->t_frost_on_l / 10.0);
    ui->tLocksOff->setValue(temperatures_cfg->t_frost_off_l / 10.0);
    return true;
}

bool CTemperaturesCfgForm::getCfg(void *cfg_struct)
{
    temperatures_cfg_t *temperatures_cfg = (temperatures_cfg_t*)cfg_struct;

    memset(temperatures_cfg, 0, sizeof(temperatures_cfg_t));

    QDoubleSpinBox *spin;

    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(0, 0);
    temperatures_cfg->t_r_on_fr = spin->value() * 10;
    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(0, 1);
    temperatures_cfg->t_r_off_fr = spin->value() * 10;
    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(1, 0);
    temperatures_cfg->t_r_on_wet = spin->value() * 10;
    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(1, 1);
    temperatures_cfg->t_r_off_wet = spin->value() * 10;
    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(2, 0);
    temperatures_cfg->t_r_on_sn = spin->value() * 10;
    spin = (QDoubleSpinBox*)ui->weatherAutomTempTable->cellWidget(2, 1);
    temperatures_cfg->t_r_off_sn = spin->value() * 10;

    temperatures_cfg->t_frost_on_r = ui->frostTempIn->value() * 10;
    temperatures_cfg->t_frost_off_r = ui->frostTempOut->value() * 10;

    temperatures_cfg->t_frost_on_l = ui->tLocksOn->value() * 10;
    temperatures_cfg->t_frost_off_l = ui->tLocksOff->value() * 10;
    return true;
}
