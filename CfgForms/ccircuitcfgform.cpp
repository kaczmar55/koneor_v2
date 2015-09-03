#include "ccircuitcfgform.h"
#include "ui_ccircuitcfgform.h"

CCircuitCfgForm::CCircuitCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCircuitCfgForm)
{
    ui->setupUi(this);
}

CCircuitCfgForm::~CCircuitCfgForm()
{
    delete ui;
}
