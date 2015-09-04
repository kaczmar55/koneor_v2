#include "cuserscfgform.h"
#include "ui_cuserscfgform.h"

CUsersCfgForm::CUsersCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CUsersCfgForm)
{
    ui->setupUi(this);
}

CUsersCfgForm::~CUsersCfgForm()
{
    delete ui;
}
