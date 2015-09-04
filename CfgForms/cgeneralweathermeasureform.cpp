#include "cgeneralweathermeasureform.h"
#include "ui_cgeneralweathermeasureform.h"

CGeneralWeatherMeasureForm::CGeneralWeatherMeasureForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CGeneralWeatherMeasureForm)
{
    ui->setupUi(this);
}

CGeneralWeatherMeasureForm::~CGeneralWeatherMeasureForm()
{
    delete ui;
}
