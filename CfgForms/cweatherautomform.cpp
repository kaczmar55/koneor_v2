#include "cweatherautomform.h"
#include "ui_cweatherautomform.h"

CWeatherAutomForm::CWeatherAutomForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWeatherAutomForm)
{
    ui->setupUi(this);
}

CWeatherAutomForm::~CWeatherAutomForm()
{
    delete ui;
}
