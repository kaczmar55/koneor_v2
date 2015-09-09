#include "cmodbusslavecfgform.h"
#include "ui_cmodbusslavecfgform.h"

CModbusSlaveCfgForm::CModbusSlaveCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CModbusSlaveCfgForm)
{
    ui->setupUi(this);
}

CModbusSlaveCfgForm::~CModbusSlaveCfgForm()
{
    delete ui;
}

bool CModbusSlaveCfgForm::setCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}

bool CModbusSlaveCfgForm::getCfg(void *cfg_struct)
{
    (void)cfg_struct;
    return true;
}
