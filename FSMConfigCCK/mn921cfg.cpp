#include "mn921cfg.h"
#include "ui_mn921cfg.h"
#include "clientcfgform.h"


MN921Cfg::MN921Cfg(MN* mncfg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MN921Cfg)
{
    ui->setupUi(this);
    this->cfg = mncfg;
    ui->posobj->setProperty("intValue", QVariant(this->cfg->client().id()));
}

MN921Cfg::~MN921Cfg()
{
    delete ui;
}

void MN921Cfg::on_gr_spin1_valueChanged(int arg1)
{
    ui->gr_dial1->setValue(arg1);
}

void MN921Cfg::on_gr_dial1_valueChanged(int value)
{
    ui->gr_spin1->setValue(value);
}

void MN921Cfg::on_gr_spin2_valueChanged(int arg1)
{
    ui->gr_dial2->setValue(arg1);
}

void MN921Cfg::on_gr_dial2_valueChanged(int value)
{
    ui->gr_spin2->setValue(value);
}

void MN921Cfg::on_mb_ch1_clicked()
{
    ui->mb_ch1->setChecked(true);
    ui->cb_ch1->setChecked(false);
    ui->tch_ch1->setChecked(false);
    ui->ats_ch1->setChecked(false);
    ui->r168_ch1->setChecked(false);
    ui->r168100kb_ch1->setChecked(false);
   // this->cfg->channel(0).set_typedev(MNTypeDevice::MB);
}

void MN921Cfg::on_cb_ch1_clicked()
{
    ui->mb_ch1->setChecked(false);
    ui->cb_ch1->setChecked(true);
    ui->tch_ch1->setChecked(false);
    ui->ats_ch1->setChecked(false);
    ui->r168_ch1->setChecked(false);
    ui->r168100kb_ch1->setChecked(false);
   // this->cfg->channel(0).set_typedev(MNTypeDevice::CB);
}

void MN921Cfg::on_tch_ch1_clicked()
{
    ui->mb_ch1->setChecked(false);
    ui->cb_ch1->setChecked(false);
    ui->tch_ch1->setChecked(true);
    ui->ats_ch1->setChecked(false);
    ui->r168_ch1->setChecked(false);
    ui->r168100kb_ch1->setChecked(false);
    //this->cfg->channel(0).set_typedev(MNTypeDevice::TCH);
}

void MN921Cfg::on_ats_ch1_clicked()
{
    ui->mb_ch1->setChecked(false);
    ui->cb_ch1->setChecked(false);
    ui->tch_ch1->setChecked(false);
    ui->ats_ch1->setChecked(true);
    ui->r168_ch1->setChecked(false);
    ui->r168100kb_ch1->setChecked(false);
   // this->cfg->channel(0).set_typedev(MNTypeDevice::ATS);
}

void MN921Cfg::on_r168_ch1_clicked()
{
    ui->mb_ch1->setChecked(false);
    ui->cb_ch1->setChecked(false);
    ui->tch_ch1->setChecked(false);
    ui->ats_ch1->setChecked(false);
    ui->r168_ch1->setChecked(true);
    ui->r168100kb_ch1->setChecked(false);
   // this->cfg->channel(0).set_typedev(MNTypeDevice::R168);
}

void MN921Cfg::on_r168100kb_ch1_clicked()
{
    ui->mb_ch1->setChecked(false);
    ui->cb_ch1->setChecked(false);
    ui->tch_ch1->setChecked(false);
    ui->ats_ch1->setChecked(false);
    ui->r168_ch1->setChecked(false);
    ui->r168100kb_ch1->setChecked(true);
   // this->cfg->channel(0).set_typedev(MNTypeDevice::R168100KB);
}

void MN921Cfg::on_mb_ch2_clicked()
{
    ui->mb_ch2->setChecked(true);
    ui->cb_ch2->setChecked(false);
    ui->tch_ch2->setChecked(false);
    ui->ats_ch2->setChecked(false);
    ui->r168_ch2->setChecked(false);
    ui->r168100kb_ch2->setChecked(false);
}

void MN921Cfg::on_cb_ch2_clicked()
{
    ui->mb_ch2->setChecked(false);
    ui->cb_ch2->setChecked(true);
    ui->tch_ch2->setChecked(false);
    ui->ats_ch2->setChecked(false);
    ui->r168_ch2->setChecked(false);
    ui->r168100kb_ch2->setChecked(false);
}

void MN921Cfg::on_tch_ch2_clicked()
{
    ui->mb_ch2->setChecked(false);
    ui->cb_ch2->setChecked(false);
    ui->tch_ch2->setChecked(true);
    ui->ats_ch2->setChecked(false);
    ui->r168_ch2->setChecked(false);
    ui->r168100kb_ch2->setChecked(false);
}

void MN921Cfg::on_ats_ch2_clicked()
{
    ui->mb_ch2->setChecked(false);
    ui->cb_ch2->setChecked(false);
    ui->tch_ch2->setChecked(false);
    ui->ats_ch2->setChecked(true);
    ui->r168_ch2->setChecked(false);
    ui->r168100kb_ch2->setChecked(false);
}

void MN921Cfg::on_r168_ch2_clicked()
{
    ui->mb_ch2->setChecked(false);
    ui->cb_ch2->setChecked(false);
    ui->tch_ch2->setChecked(false);
    ui->ats_ch2->setChecked(false);
    ui->r168_ch2->setChecked(true);
    ui->r168100kb_ch2->setChecked(false);
}

void MN921Cfg::on_r168100kb_ch2_clicked()
{
    ui->mb_ch2->setChecked(false);
    ui->cb_ch2->setChecked(false);
    ui->tch_ch2->setChecked(false);
    ui->ats_ch2->setChecked(false);
    ui->r168_ch2->setChecked(false);
    ui->r168100kb_ch2->setChecked(true);
}

void MN921Cfg::on_savetodevice_clicked()
{
    accept();
}

void MN921Cfg::on_netsetting_clicked()
{
    ClientCfgForm* mncfgdialog = new ClientCfgForm((ClientInfo*)&cfg->client());
    mncfgdialog->exec();
}
