#include "cethernetcfgform.h"
#include "ui_cethernetcfgform.h"

#include <QMessageBox>

CEthernetCfgForm::CEthernetCfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CEthernetCfgForm)
{
    ui->setupUi(this);
}

CEthernetCfgForm::~CEthernetCfgForm()
{
    delete ui;
}

bool CEthernetCfgForm::getCfg(void* cfg_struct)
{
    bool ip_err = false;
    bool mask_err = false;
    bool gateway_err = false;
    eth_cfg_t *eth_cfg = (eth_cfg_t*)cfg_struct;

    QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "", "");
    msgBox->setWindowFlags(msgBox->windowFlags() | Qt::WindowStaysOnTopHint);
    msgBox->setWindowTitle("Błąd");

    memset(eth_cfg, 0, sizeof(eth_cfg_t));
    ip_err = strToIp(eth_cfg->ip, ui->ipAddrEdit->text());
    if(ip_err)
    {
        msgBox->setText("Błąd w adresie IP");
        msgBox->exec();
        //QMessageBox::critical(this, "Błąd", "Błąd w adresie IP");
      //ip_err = QMessageBox::critical(this, "Błąd", "Błąd w adresie IP", "Ignoruj", "Popraw");
    }

    mask_err = strToIp(eth_cfg->mask, ui->maskEdit->text());
    if(mask_err)
    {
        msgBox->setText("Błąd w masce podsieci");
        msgBox->exec();
        //QMessageBox::critical(this, "Błąd", "Błąd w masce podsieci");
        //mask_err = QMessageBox::critical(this, "Błąd", "Błąd w masce podsieci", "Ignoruj", "Popraw");
    }

    gateway_err = strToIp(eth_cfg->gateway, ui->gatewayEdit->text());
    if(gateway_err)
    {
        msgBox->setText("Błąd w adresie IP bramy domyślnej");
        msgBox->exec();
        //QMessageBox::critical(this, "Błąd", "Błąd w adresie IP bramy domyślnej");
        //gateway_err = QMessageBox::critical(this, "Błąd", "Błąd w adresie IP bramy domyślnej", "Ignoruj", "Popraw");
    }

    delete msgBox;
    //return !(ip_err || mask_err || gateway_err);
    return true;
}

bool CEthernetCfgForm::setCfg(void* cfg_struct)
{
    eth_cfg_t *eth_cfg = (eth_cfg_t*)cfg_struct;
    ui->ipAddrEdit->setText(QString("%1.%2.%3.%4").arg(eth_cfg->ip[0]).arg(eth_cfg->ip[1]).arg(eth_cfg->ip[2]).arg(eth_cfg->ip[3]));
    ui->maskEdit->setText(QString("%1.%2.%3.%4").arg(eth_cfg->mask[0]).arg(eth_cfg->mask[1]).arg(eth_cfg->mask[2]).arg(eth_cfg->mask[3]));
    ui->gatewayEdit->setText(QString("%1.%2.%3.%4").arg(eth_cfg->gateway[0]).arg(eth_cfg->gateway[1]).arg(eth_cfg->gateway[2]).arg(eth_cfg->gateway[3]));

    return true;
}
