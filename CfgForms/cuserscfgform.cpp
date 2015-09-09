#include "cuserscfgform.h"
#include "ui_cuserscfgform.h"

CUsersCfgForm::CUsersCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CUsersCfgForm)
{
    ui->setupUi(this);
}

CUsersCfgForm::~CUsersCfgForm()
{
    delete ui;
}

bool CUsersCfgForm::setCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}

bool CUsersCfgForm::getCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}
