#include "mn921channelcfg.h"
#include "ui_mn921channelcfg.h"

mn921channelcfg::mn921channelcfg(MN_Channel* mncfg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mn921channelcfg)
{
    ui->setupUi(this);
    channelcfg = mncfg;
    ui->cb_timeoc->setText(QString::number(channelcfg->cb().timeoutputcall()));
    ui->mb_timeoc->setText(QString::number(channelcfg->mb().timeoutputcall()));
    ui->tch_timeoc->setText(QString::number(channelcfg->tch().timeoutputcall()));
    ui->tch_maxtimeoc->setText(QString::number(channelcfg->tch().maxtimeoutputcall()));
    ui->tch_mintimeoc->setText(QString::number(channelcfg->tch().mintimeoutputcall()));
    ui->r168_timeoc->setText(QString::number(channelcfg->r168().timeoutputcall()));
    switch(channelcfg->ats().typeats()) {
            case MN921TypeATS::Pulse:
                ui->ats_type->setCurrentIndex(0);
            break;
            case MN921TypeATS::Tone:
                 ui->ats_type->setCurrentIndex(1);
            break;
    }
    switch(channelcfg->tch().typetch()) {
            case MN921TypeTCH::TwoWire:
                ui->tch_type->setCurrentIndex(0);
            break;
            case MN921TypeTCH::FourWire_FL:
                ui->tch_type->setCurrentIndex(1);
            break;
            case MN921TypeTCH::FourWire_TCH:
                ui->tch_type->setCurrentIndex(2);
            break;
    }
    switch(channelcfg->tch().ocfr()) {
            case MN921OutputCallFrequency::F_600:
                ui->tch_fr->setCurrentIndex(0);
            break;
            case MN921OutputCallFrequency::F_2100:
                ui->tch_fr->setCurrentIndex(1);
            break;
    }


}

mn921channelcfg::~mn921channelcfg()
{
    delete ui;
}

void mn921channelcfg::on_pushButton_clicked()
{
    channelcfg->mutable_cb()->set_timeoutputcall(ui->cb_timeoc->text().toInt());
    channelcfg->mutable_mb()->set_timeoutputcall(ui->mb_timeoc->text().toInt());
    channelcfg->mutable_tch()->set_timeoutputcall(ui->tch_timeoc->text().toInt());
    channelcfg->mutable_tch()->set_mintimeoutputcall(ui->tch_mintimeoc->text().toInt());
    channelcfg->mutable_tch()->set_maxtimeoutputcall(ui->tch_maxtimeoc->text().toInt());
    channelcfg->mutable_r168()->set_timeoutputcall(ui->r168_timeoc->text().toInt());
    switch(ui->ats_type->currentIndex()) {
            case 0:
                channelcfg->mutable_ats()->set_typeats(MN921TypeATS::Pulse);
            break;
            case 1:
                 channelcfg->mutable_ats()->set_typeats(MN921TypeATS::Tone);
            break;
    }
    switch(ui->tch_type->currentIndex()) {
            case 0:
                channelcfg->mutable_tch()->set_typetch(MN921TypeTCH::TwoWire);
            break;
            case 1:
                channelcfg->mutable_tch()->set_typetch(MN921TypeTCH::FourWire_FL);
            break;
            case 2:
                channelcfg->mutable_tch()->set_typetch(MN921TypeTCH::FourWire_TCH);
            break;
    }
    switch(channelcfg->tch().ocfr()) {
            case 0:
                ui->tch_fr->setCurrentIndex(0);
                channelcfg->mutable_tch()->set_ocfr(MN921OutputCallFrequency::F_600);
            break;
            case 1:
                channelcfg->mutable_tch()->set_ocfr(MN921OutputCallFrequency::F_2100);
            break;
    }
    accept();
}
