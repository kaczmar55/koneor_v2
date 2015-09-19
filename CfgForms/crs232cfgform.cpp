#include "crs232cfgform.h"
#include "ui_crs232cfgform.h"
#include <QMessageBox>

CRs232CfgForm::CRs232CfgForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CRs232CfgForm)
{
    ui->setupUi(this);
}

CRs232CfgForm::~CRs232CfgForm()
{
    delete ui;
}

bool CRs232CfgForm::setCfg(void *cfg_struct)
{
    rs_cfg_t *rs_cfg = (rs_cfg_t*)cfg_struct;

    ui->rsActiveChk->setChecked(true);
    ui->rsBaudrateCmb->setCurrentText(QString::number(rs_cfg[0].baud));
    ui->rsStopBitsCmb->setCurrentIndex(rs_cfg[0].stop_bits);
    ui->rsParityCmb->setCurrentIndex(rs_cfg[0].parity);
    ui->rsProtocolCmb->setCurrentIndex(rs_cfg[0].protocol);
    if(rs_cfg[0].data_bits == 7)
        ui->rsDataBitsCmb->setCurrentIndex(0);
    else
        ui->rsDataBitsCmb->setCurrentIndex(1);

    if(rs_cfg[1].active == 0)
        ui->virtRs1ActiveChk->setChecked(false);
    else
        ui->virtRs1ActiveChk->setChecked(true);
    ui->virtRs1Port->setValue(rs_cfg[1].port);
    ui->virtRs1IpAddrEdit->setText(QString("%1.%2.%3.%4").arg(rs_cfg[1].server_ip[0]).arg(rs_cfg[1].server_ip[1]).arg(rs_cfg[1].server_ip[2]).arg(rs_cfg[1].server_ip[3]));
    ui->virtRs1ProtocolCmb->setCurrentIndex(rs_cfg[1].protocol);

    if(rs_cfg[2].active == 0)
        ui->virtRs2ActiveChk->setChecked(false);
    else
        ui->virtRs2ActiveChk->setChecked(true);
    ui->virtRs2Port->setValue(rs_cfg[2].port);
    ui->virtRs2IpAddrEdit->setText(QString("%1.%2.%3.%4").arg(rs_cfg[2].server_ip[0]).arg(rs_cfg[2].server_ip[1]).arg(rs_cfg[2].server_ip[2]).arg(rs_cfg[2].server_ip[3]));
    ui->virtRs2ProtocolCmb->setCurrentIndex(rs_cfg[2].protocol);

    if(rs_cfg[3].active == 0)
        ui->virtRs3ActiveChk->setChecked(false);
    else
        ui->virtRs3ActiveChk->setChecked(true);
    ui->virtRs3Port->setValue(rs_cfg[3].port);
    ui->virtRs3IpAddrEdit->setText(QString("%1.%2.%3.%4").arg(rs_cfg[3].server_ip[0]).arg(rs_cfg[3].server_ip[1]).arg(rs_cfg[3].server_ip[2]).arg(rs_cfg[3].server_ip[3]));
    ui->virtRs1ProtocolCmb->setCurrentIndex(rs_cfg[3].protocol);

    if(rs_cfg[4].active == 0)
        ui->virtRs4ActiveChk->setChecked(false);
    else
        ui->virtRs4ActiveChk->setChecked(true);
    ui->virtRs4Port->setValue(rs_cfg[4].port);
    ui->virtRs4IpAddrEdit->setText(QString("%1.%2.%3.%4").arg(rs_cfg[4].server_ip[0]).arg(rs_cfg[4].server_ip[1]).arg(rs_cfg[4].server_ip[2]).arg(rs_cfg[4].server_ip[3]));
    ui->virtRs4ProtocolCmb->setCurrentIndex(rs_cfg[4].protocol);

    return true;
}

bool CRs232CfgForm::getCfg(void *cfg_struct)
{
    bool ok;
    bool err = false;
    rs_cfg_t *rs_cfg = (rs_cfg_t*)cfg_struct;

    QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "", "");
    msgBox->setWindowFlags(msgBox->windowFlags() | Qt::WindowStaysOnTopHint);
    msgBox->setWindowTitle("Błąd");

    memset(rs_cfg, 0, sizeof(rs_cfg_t) * RS_COUNT);

    rs_cfg[0].active = ui->rsActiveChk->isChecked();
    rs_cfg[0].type = 0;			//fizyczny
    rs_cfg[0].baud = ui->rsBaudrateCmb->currentText().toInt(&ok);
    rs_cfg[0].stop_bits = ui->rsStopBitsCmb->currentIndex();
    rs_cfg[0].parity = ui->rsParityCmb->currentIndex();
    rs_cfg[0].protocol = ui->rsProtocolCmb->currentIndex();
    if(ui->rsDataBitsCmb->currentIndex() == 0)
        rs_cfg[0].data_bits = 7;
    else
        rs_cfg[0].data_bits = 8;
    if((ok == false) && (rs_cfg[0].active != 0))
    {
        msgBox->setText("RS232/485 - błędnie wprowadzone Baudrate");
        msgBox->exec();
        //QMessageBox::critical(this, "Błąd", "COM1 - błędnie wprowadzone Baudrate");
    }

    rs_cfg[1].active = ui->virtRs1ActiveChk->isChecked();
    rs_cfg[1].type = 1;			//wirtualny
    rs_cfg[1].port = ui->virtRs1Port->value();
    if((err |= strToIp(rs_cfg[1].server_ip, ui->virtRs1IpAddrEdit->text())) && (rs_cfg[1].active != 0))
    {
        msgBox->setText("Błąd w adresie IP portu wirtualnego COM2");
        msgBox->exec();
        //QMessageBox::critical(this, "Błąd", "Błąd w adresie IP portu wirtualnego COM2");
    }
    rs_cfg[1].protocol = ui->virtRs1ProtocolCmb->currentIndex();

    rs_cfg[2].active = ui->virtRs2ActiveChk->isChecked();
    rs_cfg[2].type = 1;			//wirtualny
    rs_cfg[2].port = ui->virtRs2Port->value();
    if((err |= strToIp(rs_cfg[2].server_ip, ui->virtRs2IpAddrEdit->text())) && (rs_cfg[2].active != 0))
    {
        msgBox->setText("Błąd w adresie IP portu wirtualnego COM3");
        msgBox->exec();
        //QMessageBox::critical(this, "Błąd", "Błąd w adresie IP portu wirtualnego COM3");
    }
    rs_cfg[2].protocol = ui->virtRs2ProtocolCmb->currentIndex();

    rs_cfg[3].active = ui->virtRs3ActiveChk->isChecked();
    rs_cfg[3].type = 1;			//wirtualny
    rs_cfg[3].port = ui->virtRs3Port->value();
    if((err |= strToIp(rs_cfg[3].server_ip, ui->virtRs3IpAddrEdit->text())) && (rs_cfg[3].active != 0))
    {
        msgBox->setText("Błąd w adresie IP portu wirtualnego COM4");
        msgBox->exec();
        //QMessageBox::critical(this, "Błąd", "Błąd w adresie IP portu wirtualnego COM4");
    }
    rs_cfg[3].protocol = ui->virtRs3ProtocolCmb->currentIndex();

    rs_cfg[4].active = ui->virtRs4ActiveChk->isChecked();
    rs_cfg[4].type = 1;			//wirtualny
    rs_cfg[4].port = ui->virtRs4Port->value();
    if((err |= strToIp(rs_cfg[4].server_ip, ui->virtRs4IpAddrEdit->text())) && (rs_cfg[4].active != 0))
    {
        msgBox->setText("Błąd w adresie IP portu wirtualnego COM5");
        msgBox->exec();
        //QMessageBox::critical(this, "Błąd", "Błąd w adresie IP portu wirtualnego COM5");
    }
    rs_cfg[4].protocol = ui->virtRs4ProtocolCmb->currentIndex();

    delete msgBox;
    //return (err | ok);
    return true;
}

void CRs232CfgForm::on_rsProtocolCmb_currentIndexChanged(int index)
{
    switch(index)
    {
    case 1:
        ui->rsBaudrateCmb->setCurrentText("115200");
        ui->rsDataBitsCmb->setCurrentIndex(1);
        ui->rsParityCmb->setCurrentIndex(0);
        ui->rsStopBitsCmb->setCurrentIndex(0);
        break;
    case 3:
        ui->rsBaudrateCmb->setCurrentText("4800");
        ui->rsDataBitsCmb->setCurrentIndex(0);
        ui->rsParityCmb->setCurrentIndex(1);
        ui->rsStopBitsCmb->setCurrentIndex(0);
        break;
    default:
        break;
    }

    if(index == 3)
    {
        ui->rsBaudrateCmb->setEnabled(false);
        ui->rsDataBitsCmb->setEnabled(false);
        ui->rsParityCmb->setEnabled(false);
        ui->rsStopBitsCmb->setEnabled(false);
    }
    else
    {
        ui->rsBaudrateCmb->setEnabled(true);
        ui->rsDataBitsCmb->setEnabled(true);
        ui->rsParityCmb->setEnabled(true);
        ui->rsStopBitsCmb->setEnabled(true);
    }
}
