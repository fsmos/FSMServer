#include "POcfg.h"
#include "ui_POcfg.h"
#include "clientcfgform.h"
#include "cpp/fsm_cckconfig_service.grpc.pb.h"
#include "poabonentlist.h"
#include "groupselect.h"

using fsm::CCKTypeDevice;

POCfg::POCfg(P0* pocfg,unsigned char type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::POCfg)
{
    ui->setupUi(this);
    this->cfg = pocfg;
    ui->posobj->setProperty("intValue", QVariant(this->cfg->client().id()));
    if(this->cfg->channel_size() < 1) cfg->add_channel();
    if(this->cfg->channel_size() < 2) cfg->add_channel();
    this->channel[0] = cfg->mutable_channel(0);
    this->channel[1] = cfg->mutable_channel(1);
    this->ui->channel_1_sipnum->setText(QString::number(this->channel[0]->self_sip_number()));
    this->ui->channel_2_sipnum->setText(QString::number(this->channel[1]->self_sip_number()));
    this->ui->rtp_port_ch1->setText(QString::number(this->channel[0]->self_rtp_port()));
    this->ui->rtp_port_ch2->setText(QString::number(this->channel[1]->self_rtp_port()));
    this->ui->sip_port_ch1->setText(QString::number(this->channel[0]->self_sip_port()));
    this->ui->sip_port_ch2->setText(QString::number(this->channel[1]->self_sip_port()));
    ui->gr_dial1->setValue((int)(this->channel[0]->volume()));
    ui->gr_dial2->setValue((int)(this->channel[1]->volume()));
    ui->gr_spin1->setValue((int)(this->channel[0]->volume()));
    ui->gr_spin2->setValue((int)(this->channel[1]->volume()));
    if(CCKTypeDevice::DT_PO08 == type) {
        this->ui->channel_2_sipnum->setEnabled(false);
        this->ui->rtp_port_ch2->setEnabled(false);
        this->ui->sip_port_ch2->setEnabled(false);
        ui->gr_dial2->setEnabled(false);
        ui->gr_spin2->setEnabled(false);
        ui->setabonent_2->setEnabled(false);
        countel = 8;
    }
    if(CCKTypeDevice::DT_PO07 == type) {
        countel = 12;
    }
    if(CCKTypeDevice::DT_PO06 == type) {
        countel = 12;
    }
}

POCfg::~POCfg()
{
    delete ui;
}

void POCfg::on_gr_spin1_valueChanged(int arg1)
{
    ui->gr_dial1->setValue(arg1);
    this->channel[0]->set_volume((uint)arg1);
}

void POCfg::on_gr_dial1_valueChanged(int value)
{
    ui->gr_spin1->setValue(value);
    this->channel[0]->set_volume((uint)value);
}

void POCfg::on_gr_spin2_valueChanged(int arg1)
{
    ui->gr_dial2->setValue(arg1);
    this->channel[1]->set_volume((uint)arg1);
}

void POCfg::on_gr_dial2_valueChanged(int value)
{
    ui->gr_spin2->setValue(value);
    this->channel[1]->set_volume((uint)value);
}



void POCfg::on_savetodevice_clicked()
{
    this->channel[0]->set_self_sip_number(this->ui->channel_1_sipnum->text().toUInt());
    this->channel[1]->set_self_sip_number(this->ui->channel_2_sipnum->text().toUInt());
    this->channel[0]->set_self_rtp_port(this->ui->rtp_port_ch1->text().toUInt());
    this->channel[1]->set_self_rtp_port(this->ui->rtp_port_ch2->text().toUInt());
    this->channel[0]->set_self_sip_port(this->ui->sip_port_ch1->text().toUInt());
    this->channel[1]->set_self_sip_port(this->ui->sip_port_ch2->text().toUInt());
    accept();
}

void POCfg::on_netsetting_clicked()
{
    ClientCfgForm* pocfgdialog = new ClientCfgForm((ClientInfo*)&cfg->client());
    pocfgdialog->exec();
}

void POCfg::on_setabonent_1_clicked()
{
    POAbonentList* abonentcfg = new POAbonentList(this->channel[0],countel);
    abonentcfg->exec();

}

void POCfg::on_setabonent_2_clicked()
{
    POAbonentList* abonentcfg = new POAbonentList(this->channel[1],countel);
    abonentcfg->exec();
}

void POCfg::on_r168seting_clicked()
{

}

void POCfg::on_conf_clicked()
{
    GroupSelect* grpsel = new GroupSelect(cfg->mutable_grp()->mutable_cnfg());
    grpsel->exec();
}

void POCfg::on_csv_clicked()
{
    GroupSelect* grpsel = new GroupSelect(cfg->mutable_grp()->mutable_csvg());
    grpsel->exec();
}
