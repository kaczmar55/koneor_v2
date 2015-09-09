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
    (void)cfg_struct;
    return true;
}

bool CTemperaturesCfgForm::getCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}
