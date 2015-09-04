#include "ccancfgform.h"
#include "ui_ccancfgform.h"

CCanCfgForm::CCanCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCanCfgForm)
{
    ui->setupUi(this);
}

CCanCfgForm::~CCanCfgForm()
{
    delete ui;
}
