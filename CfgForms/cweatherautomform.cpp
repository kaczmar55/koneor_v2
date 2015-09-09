#include "cweatherautomform.h"
#include "ui_cweatherautomform.h"

CWeatherAutomForm::CWeatherAutomForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CWeatherAutomForm)
{
    ui->setupUi(this);
}

CWeatherAutomForm::~CWeatherAutomForm()
{
    delete ui;
}

bool CWeatherAutomForm::setCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}

bool CWeatherAutomForm::getCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}
