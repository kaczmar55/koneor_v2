#include "ctgfmcfgform.h"
#include "ui_ctgfmcfgform.h"

CTgfmCfgForm::CTgfmCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CTgfmCfgForm)
{
    ui->setupUi(this);
}

CTgfmCfgForm::~CTgfmCfgForm()
{
    delete ui;
}

bool CTgfmCfgForm::setCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}

bool CTgfmCfgForm::getCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}
