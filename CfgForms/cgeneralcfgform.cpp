#include "cgeneralcfgform.h"
#include "ui_cgeneralcfgform.h"

CGeneralCfgForm::CGeneralCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CGeneralCfgForm)
{
    ui->setupUi(this);
}

CGeneralCfgForm::~CGeneralCfgForm()
{
    delete ui;
}
