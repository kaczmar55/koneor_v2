#include "ciomodulescfgform.h"
#include "ui_ciomodulescfgform.h"

CIoModulesCfgForm::CIoModulesCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CIoModulesCfgForm)
{
    ui->setupUi(this);
}

CIoModulesCfgForm::~CIoModulesCfgForm()
{
    delete ui;
}
