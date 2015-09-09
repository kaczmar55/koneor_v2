#include "ccancfgform.h"
#include "ui_ccancfgform.h"

CCanCfgForm::CCanCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CCanCfgForm)
{
    ui->setupUi(this);
}

CCanCfgForm::~CCanCfgForm()
{
    delete ui;
}

bool CCanCfgForm::getCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}

bool CCanCfgForm::setCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}
