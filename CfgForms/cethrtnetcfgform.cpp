#include "cethrtnetcfgform.h"
#include "ui_cethrtnetcfgform.h"

CEthrtnetCfgForm::CEthrtnetCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CEthrtnetCfgForm)
{
    ui->setupUi(this);
}

CEthrtnetCfgForm::~CEthrtnetCfgForm()
{
    delete ui;
}
