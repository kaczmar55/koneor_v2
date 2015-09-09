#include "ciomodulescfgform.h"
#include "ui_ciomodulescfgform.h"

CIoModulesCfgForm::CIoModulesCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CIoModulesCfgForm)
{
    ui->setupUi(this);
}

CIoModulesCfgForm::~CIoModulesCfgForm()
{
    delete ui;
}

bool CIoModulesCfgForm::setCfg(void *cfg_struct)
{
    (void)cfg_struct;
}

bool CIoModulesCfgForm::getCfg(void *cfg_struct)
{
    (void)cfg_struct;
}
