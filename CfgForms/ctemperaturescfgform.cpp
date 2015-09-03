#include "ctemperaturescfgform.h"
#include "ui_ctemperaturescfgform.h"

CTemperaturesCfgForm::CTemperaturesCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CTemperaturesCfgForm)
{
    ui->setupUi(this);
}

CTemperaturesCfgForm::~CTemperaturesCfgForm()
{
    delete ui;
}
