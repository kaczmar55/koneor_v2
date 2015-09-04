#include "crs232cfgform.h"
#include "ui_crs232cfgform.h"

CRs232CfgForm::CRs232CfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRs232CfgForm)
{
    ui->setupUi(this);
}

CRs232CfgForm::~CRs232CfgForm()
{
    delete ui;
}
