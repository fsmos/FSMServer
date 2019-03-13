#include "r168s.h"
#include "ui_r168s.h"

r168s::r168s(MN* cfg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::r168s)
{
    ui->setupUi(this);
    cfgmn = cfg;
    ui->r168cfgport->setText(QString::number(cfg->r168().r168port()));
    setConfigureInfo(cfg->r168().apd());
}

r168s::~r168s()
{
    delete ui;
}

unsigned short r168s::getConfigureInfo(){

        unsigned short _apd_data = 0x00;

        switch (ui->ApdInputFL->currentIndex()){

                case 0://FL1

                        _apd_data |= 0x01;

                        break;

                case 1://FL2

                        break;

        }

        switch (ui->ApdInputKR->currentIndex()){

                case 0://KR1

                        break;

                case 1://KR2

                        _apd_data |= 0x04;

                        break;

        }

        switch (ui->ApdOutputFL->currentIndex()){

                case 0://FL1

                        break;

                case 1://FL2

                        _apd_data |= 0x02;

                        break;

        }

        switch (ui->ApdOutputKR->currentIndex()){

                case 0://KR1

                        break;

                case 1://KR2

                        _apd_data |= 0x08;

                        break;

        }

        switch (ui->SelectDevCh2->currentIndex()){

                case 0://MN825

                        break;

                case 1://ApdTch

                        _apd_data |= 0x10;

                        break;

        }

        switch (ui->SelectDevCh1->currentIndex()){

                case 0://MN825

                        break;

                case 1://ApdTch

                        _apd_data |= 0x20;

                        break;

        }

        switch (ui->ApdInputTch->currentIndex()){

                case 0://TCH1

                        _apd_data |= 0x40;

                        break;

                case 1://TCH2

                        break;

        }

        switch (ui->ApdInputKR_2->currentIndex()){

                case 0://KR1

                        break;

                case 1://KR2

                        _apd_data |= 0x100;

                        break;

        }

        switch (ui->ApdOutputTch->currentIndex()){

                case 0://TCH1

                        break;

                case 1://TCH2

                        _apd_data |= 0x80;

                        break;

        }

        switch (ui->ApdOutputKR_2->currentIndex()){

                case 0://KR1

                        break;

                case 1://KR2

                        _apd_data |= 0x200;

                        break;

        }

        return _apd_data;

}

void r168s::setConfigureInfo(unsigned short _value){

        if (_value & 0x01)

                ui->ApdInputFL->setCurrentIndex(0); else ui->ApdInputFL->setCurrentIndex(1);

        if (_value & 0x02)

                ui->ApdOutputFL->setCurrentIndex(1); else ui->ApdOutputFL->setCurrentIndex(0);

        if (_value & 0x04)

                ui->ApdInputKR->setCurrentIndex(1); else ui->ApdInputKR->setCurrentIndex(0);

        if (_value & 0x08)

                ui->ApdOutputKR->setCurrentIndex(1); else ui->ApdOutputKR->setCurrentIndex(0);

        if (_value & 0x40)

                ui->ApdInputTch->setCurrentIndex(0); else ui->ApdInputTch->setCurrentIndex(1);

        if (_value & 0x80)

                ui->ApdOutputTch->setCurrentIndex(1); else ui->ApdOutputTch->setCurrentIndex(0);

        if (_value & 0x100)

                ui->ApdInputKR_2->setCurrentIndex(1); else ui->ApdInputKR_2->setCurrentIndex(0);

        if (_value & 0x200)

                ui->ApdOutputKR_2->setCurrentIndex(1); else ui->ApdOutputKR_2->setCurrentIndex(0);

        if (_value & 0x10)

                ui->SelectDevCh2->setCurrentIndex(1); else ui->SelectDevCh2->setCurrentIndex(0);

        if (_value & 0x20)

                ui->SelectDevCh1->setCurrentIndex(1); else ui->SelectDevCh1->setCurrentIndex(0);

}

void r168s::on_pushButton_clicked()
{
    cfgmn->mutable_r168()->set_r168port(ui->r168cfgport->text().toInt());
    cfgmn->mutable_r168()->set_apd(getConfigureInfo());
    accept();
}
