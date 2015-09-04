#include "cmodbusslavecfgform.h"
#include "ui_cmodbusslavecfgform.h"

CModbusSlaveCfgForm::CModbusSlaveCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CModbusSlaveCfgForm)
{
    ui->setupUi(this);
}

CModbusSlaveCfgForm::~CModbusSlaveCfgForm()
{
    delete ui;
}
