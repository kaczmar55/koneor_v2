#include "crs232cfgform.h"
#include "ui_crs232cfgform.h"

CRs232CfgForm::CRs232CfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CRs232CfgForm)
{
    ui->setupUi(this);
}

CRs232CfgForm::~CRs232CfgForm()
{
    delete ui;
}

bool CRs232CfgForm::setCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}

bool CRs232CfgForm::getCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}
