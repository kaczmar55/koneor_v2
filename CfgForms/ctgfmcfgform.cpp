#include "ctgfmcfgform.h"
#include "ui_ctgfmcfgform.h"

CTgfmCfgForm::CTgfmCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CTgfmCfgForm)
{
    ui->setupUi(this);
}

CTgfmCfgForm::~CTgfmCfgForm()
{
    delete ui;
}
