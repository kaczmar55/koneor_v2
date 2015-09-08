#include "cethernetcfgform.h"
#include "ui_cethernetcfgform.h"

#include <QMessageBox>

CEthernetCfgForm::CEthernetCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CEthernetCfgForm)
{
    ui->setupUi(this);
}

CEthernetCfgForm::~CEthernetCfgForm()
{
    delete ui;
}

bool CEthernetCfgForm::getCfg(eth_cfg_t *eth_cfg)
{
    bool ip_err = false;
    bool mask_err = false;
    bool gateway_err = false;

    memset(eth_cfg, 0, sizeof(eth_cfg_t));
    ip_err = strToIp(eth_cfg->ip, ui->ipAddrEdit->text());
    if(ip_err)
    {
      ip_err = QMessageBox::critical(this, "Błąd", "Błąd w adresie IP", "Ignoruj", "Popraw");
    }

    mask_err = strToIp(eth_cfg->mask, ui->maskEdit->text());
    if(mask_err)
        mask_err = QMessageBox::critical(this, "Błąd", "Błąd w masce podsieci", "Ignoruj", "Popraw");

    gateway_err = strToIp(eth_cfg->gateway, ui->gatewayEdit->text());
    if(gateway_err)
        gateway_err = QMessageBox::critical(this, "Błąd", "Błąd w adresie IP bramy domyślnej", "Ignoruj", "Popraw");

    return !(ip_err || mask_err || gateway_err);
}

bool CEthernetCfgForm::setCfg(eth_cfg_t *eth_cfg)
{
    ui->ipAddrEdit->setText(QString("%1.%2.%3.%4").arg(eth_cfg->ip[0]).arg(eth_cfg->ip[1]).arg(eth_cfg->ip[2]).arg(eth_cfg->ip[3]));
    ui->maskEdit->setText(QString("%1.%2.%3.%4").arg(eth_cfg->mask[0]).arg(eth_cfg->mask[1]).arg(eth_cfg->mask[2]).arg(eth_cfg->mask[3]));
    ui->gatewayEdit->setText(QString("%1.%2.%3.%4").arg(eth_cfg->gateway[0]).arg(eth_cfg->gateway[1]).arg(eth_cfg->gateway[2]).arg(eth_cfg->gateway[3]));

    return true;
}
