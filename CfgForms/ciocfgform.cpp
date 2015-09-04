#include "ciocfgform.h"
#include "ui_ciocfgform.h"

CIOCfgForm::CIOCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CIOCfgForm)
{
    ui->setupUi(this);
}

CIOCfgForm::~CIOCfgForm()
{
    delete ui;
}
