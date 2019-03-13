#include "mn921cfg.h"
#include "ui_mn921cfg.h"
#include "clientcfgform.h"
#include "abonentmncfg.h"
#include "mn921channelcfg.h"
#include "r168s.h"



MN921Cfg::MN921Cfg(MN* mncfg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MN921Cfg)
{
    ui->setupUi(this);
    this->cfg = mncfg;
    ui->posobj->setProperty("intValue", QVariant(this->cfg->client().id()));
    if(this->cfg->channel_size() < 1) cfg->add_channel();
    if(this->cfg->channel_size() < 2) cfg->add_channel();
    this->channel[0] = cfg->mutable_channel(0);
    this->channel[1] = cfg->mutable_channel(1);
    this->ui->channel_1_sipnum->setText(QString::number(this->channel[0]->self_sip_number()));
    this->ui->channel_2_sipnum->setText(QString::number(this->channel[1]->self_sip_number()));
    ui->gr_dial1->setValue((int)(this->channel[0]->volume()));
    ui->gr_dial2->setValue((int)(this->channel[1]->volume()));
    ui->gr_spin1->setValue((int)(this->channel[0]->volume()));
    ui->gr_spin2->setValue((int)(this->channel[1]->volume()));
    ui->mb_ch1->setChecked((this->channel[0]->typedev() == MNTypeDevice::MB));
    ui->cb_ch1->setChecked((this->channel[0]->typedev() == MNTypeDevice::CB));
    ui->tch_ch1->setChecked((this->channel[0]->typedev() == MNTypeDevice::TCH));
    ui->ats_ch1->setChecked((this->channel[0]->typedev() == MNTypeDevice::ATS));
    ui->r168_ch1->setChecked((this->channel[0]->typedev() == MNTypeDevice::R168));
    ui->r168100kb_ch1->setChecked((this->channel[0]->typedev() == MNTypeDevice::R168100KB));
    ui->mb_ch2->setChecked((this->channel[1]->typedev() == MNTypeDevice::MB));
    ui->cb_ch2->setChecked((this->channel[1]->typedev() == MNTypeDevice::CB));
    ui->tch_ch2->setChecked((this->channel[1]->typedev() == MNTypeDevice::TCH));
    ui->ats_ch2->setChecked((this->channel[1]->typedev() == MNTypeDevice::ATS));
    ui->r168_ch2->setChecked((this->channel[1]->typedev() == MNTypeDevice::R168));
    ui->r168100kb_ch2->setChecked((this->channel[1]->typedev() == MNTypeDevice::R168100KB));
}

MN921Cfg::~MN921Cfg()
{
    delete ui;
}

void MN921Cfg::on_gr_spin1_valueChanged(int arg1)
{
    ui->gr_dial1->setValue(arg1);
    this->channel[0]->set_volume((uint)arg1);
}

void MN921Cfg::on_gr_dial1_valueChanged(int value)
{
    ui->gr_spin1->setValue(value);
    this->channel[0]->set_volume((uint)value);
}

void MN921Cfg::on_gr_spin2_valueChanged(int arg1)
{
    ui->gr_dial2->setValue(arg1);
    this->channel[1]->set_volume((uint)arg1);
}

void MN921Cfg::on_gr_dial2_valueChanged(int value)
{
    ui->gr_spin2->setValue(value);
    this->channel[1]->set_volume((uint)value);
}

void MN921Cfg::on_mb_ch1_clicked()
{
    ui->mb_ch1->setChecked(true);
    ui->cb_ch1->setChecked(false);
    ui->tch_ch1->setChecked(false);
    ui->ats_ch1->setChecked(false);
    ui->r168_ch1->setChecked(false);
    ui->r168100kb_ch1->setChecked(false);
    this->channel[0]->set_typedev(MNTypeDevice::MB);
}
void MN921Cfg::on_cb_ch1_clicked()
{
    ui->mb_ch1->setChecked(false);
    ui->cb_ch1->setChecked(true);
    ui->tch_ch1->setChecked(false);
    ui->ats_ch1->setChecked(false);
    ui->r168_ch1->setChecked(false);
    ui->r168100kb_ch1->setChecked(false);
    this->channel[0]->set_typedev(MNTypeDevice::CB);

}

void MN921Cfg::on_tch_ch1_clicked()
{
    ui->mb_ch1->setChecked(false);
    ui->cb_ch1->setChecked(false);
    ui->tch_ch1->setChecked(true);
    ui->ats_ch1->setChecked(false);
    ui->r168_ch1->setChecked(false);
    ui->r168100kb_ch1->setChecked(false);
    this->channel[0]->set_typedev(MNTypeDevice::TCH);
}

void MN921Cfg::on_ats_ch1_clicked()
{
    ui->mb_ch1->setChecked(false);
    ui->cb_ch1->setChecked(false);
    ui->tch_ch1->setChecked(false);
    ui->ats_ch1->setChecked(true);
    ui->r168_ch1->setChecked(false);
    ui->r168100kb_ch1->setChecked(false);
    this->channel[0]->set_typedev(MNTypeDevice::ATS);
}

void MN921Cfg::on_r168_ch1_clicked()
{
    ui->mb_ch1->setChecked(false);
    ui->cb_ch1->setChecked(false);
    ui->tch_ch1->setChecked(false);
    ui->ats_ch1->setChecked(false);
    ui->r168_ch1->setChecked(true);
    ui->r168100kb_ch1->setChecked(false);
    this->channel[0]->set_typedev(MNTypeDevice::R168);
}

void MN921Cfg::on_r168100kb_ch1_clicked()
{
    ui->mb_ch1->setChecked(false);
    ui->cb_ch1->setChecked(false);
    ui->tch_ch1->setChecked(false);
    ui->ats_ch1->setChecked(false);
    ui->r168_ch1->setChecked(false);
    ui->r168100kb_ch1->setChecked(true);
    this->channel[0]->set_typedev(MNTypeDevice::R168100KB);
}

void MN921Cfg::on_mb_ch2_clicked()
{
    ui->mb_ch2->setChecked(true);
    ui->cb_ch2->setChecked(false);
    ui->tch_ch2->setChecked(false);
    ui->ats_ch2->setChecked(false);
    ui->r168_ch2->setChecked(false);
    ui->r168100kb_ch2->setChecked(false);
    this->channel[1]->set_typedev(MNTypeDevice::MB);

}

void MN921Cfg::on_cb_ch2_clicked()
{
    ui->mb_ch2->setChecked(false);
    ui->cb_ch2->setChecked(true);
    ui->tch_ch2->setChecked(false);
    ui->ats_ch2->setChecked(false);
    ui->r168_ch2->setChecked(false);
    ui->r168100kb_ch2->setChecked(false);
    this->channel[1]->set_typedev(MNTypeDevice::CB);
}

void MN921Cfg::on_tch_ch2_clicked()
{
    ui->mb_ch2->setChecked(false);
    ui->cb_ch2->setChecked(false);
    ui->tch_ch2->setChecked(true);
    ui->ats_ch2->setChecked(false);
    ui->r168_ch2->setChecked(false);
    ui->r168100kb_ch2->setChecked(false);
    this->channel[1]->set_typedev(MNTypeDevice::TCH);
}

void MN921Cfg::on_ats_ch2_clicked()
{
    ui->mb_ch2->setChecked(false);
    ui->cb_ch2->setChecked(false);
    ui->tch_ch2->setChecked(false);
    ui->ats_ch2->setChecked(true);
    ui->r168_ch2->setChecked(false);
    ui->r168100kb_ch2->setChecked(false);
    this->channel[1]->set_typedev(MNTypeDevice::ATS);

}

void MN921Cfg::on_r168_ch2_clicked()
{
    ui->mb_ch2->setChecked(false);
    ui->cb_ch2->setChecked(false);
    ui->tch_ch2->setChecked(false);
    ui->ats_ch2->setChecked(false);
    ui->r168_ch2->setChecked(true);
    ui->r168100kb_ch2->setChecked(false);
    this->channel[1]->set_typedev(MNTypeDevice::R168);

}

void MN921Cfg::on_r168100kb_ch2_clicked()
{
    ui->mb_ch2->setChecked(false);
    ui->cb_ch2->setChecked(false);
    ui->tch_ch2->setChecked(false);
    ui->ats_ch2->setChecked(false);
    ui->r168_ch2->setChecked(false);
    ui->r168100kb_ch2->setChecked(true);
    this->channel[1]->set_typedev(MNTypeDevice::R168100KB);
}

void MN921Cfg::on_savetodevice_clicked()
{
    this->channel[0]->set_self_sip_number(this->ui->channel_1_sipnum->text().toUInt());
    this->channel[1]->set_self_sip_number(this->ui->channel_2_sipnum->text().toUInt());

    accept();
}

void MN921Cfg::on_netsetting_clicked()
{
    ClientCfgForm* mncfgdialog = new ClientCfgForm((ClientInfo*)&cfg->client());
    mncfgdialog->exec();
}

void MN921Cfg::on_setabonent_1_clicked()
{
    abonentmncfg* abonentcfg = new abonentmncfg(this->channel[0]);
    abonentcfg->exec();

}

void MN921Cfg::on_setabonent_2_clicked()
{
    abonentmncfg* abonentcfg = new abonentmncfg(this->channel[1]);
    abonentcfg->exec();
}

void MN921Cfg::on_setch_1_clicked()
{
    mn921channelcfg* devcfg = new mn921channelcfg(this->channel[0]);
    devcfg->exec();
}

void MN921Cfg::on_setch_2_clicked()
{
    mn921channelcfg* devcfg = new mn921channelcfg(this->channel[1]);
    devcfg->exec();
}

void MN921Cfg::on_r168seting_clicked()
{
    r168s* devcfg = new r168s(this->cfg);
    devcfg->exec();
}
