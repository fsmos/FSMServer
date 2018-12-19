#include "clientcfgform.h"
#include "ui_clientcfgform.h"

#include <QHostAddress>

ClientCfgForm::ClientCfgForm(ClientInfo* cinfo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientCfgForm)
{
    ui->setupUi(this);
    this->cinfo = cinfo;
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->ipedit->setValidator(ipValidator);
    ui->gatewayedit->setValidator(ipValidator);
    ui->maskedit->setValidator(ipValidator);
    ui->ipedit->setText(QHostAddress(this->cinfo->ip()).toString());
    ui->gatewayedit->setText(QHostAddress(this->cinfo->gateway()).toString());
    ui->maskedit->setText(QHostAddress(this->cinfo->subnetmask()).toString());
    ui->lsposition->setText(QString::number(this->cinfo->id()));
    ui->interfaceedit->setCurrentIndex(this->cinfo->iid());
    close();
}

ClientCfgForm::~ClientCfgForm()
{

    delete ui;
}

void ClientCfgForm::on_savebutton_clicked()
{
    this->cinfo->set_ip(QHostAddress(ui->ipedit->text()).toIPv4Address());
    this->cinfo->set_gateway(QHostAddress(ui->gatewayedit->text()).toIPv4Address());
    this->cinfo->set_subnetmask(QHostAddress(ui->maskedit->text()).toIPv4Address());
    this->cinfo->set_iid(QHostAddress(ui->interfaceedit->currentIndex()).toIPv4Address());
    accept();
}
