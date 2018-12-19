#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <grpcpp/grpcpp.h>
#include "mn921cfg.h"
#include <QDebug>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connparametr = "192.168.138.1:50051";
    auto client = CCKConfig::NewStub(grpc::CreateChannel(this->connparametr.toLatin1().data() , grpc::InsecureChannelCredentials()));
    GetDeviceRq rq;
    rq.set_id(2);
    MN401 resp;
    ClientContext context;
    auto status = client->GetCfgMN401(&context,rq,&resp);
    if(status.ok() == true) {
    this->on = true;
    ui->MN111->setStyleSheet(this->getdevstring(&resp,0));
    ui->pos1->setStyleSheet(this->getdevstring(&resp,1));
    ui->pos2->setStyleSheet(this->getdevstring(&resp,2));
    ui->pos3->setStyleSheet(this->getdevstring(&resp,3));
    ui->pos4->setStyleSheet(this->getdevstring(&resp,4));
    ui->pos5->setStyleSheet(this->getdevstring(&resp,5));
    ui->pos6->setStyleSheet(this->getdevstring(&resp,6));
    ui->pos7->setStyleSheet(this->getdevstring(&resp,7));
    ui->pos8->setStyleSheet(this->getdevstring(&resp,8));
    ui->pult1->setStyleSheet(this->getdevstring(&resp,10));
    ui->pult2->setStyleSheet(this->getdevstring(&resp,11));
    ui->pult3->setStyleSheet(this->getdevstring(&resp,12));
    ui->pult4->setStyleSheet(this->getdevstring(&resp,13));
    ui->pult5->setStyleSheet(this->getdevstring(&resp,14));
    ui->pult6->setStyleSheet(this->getdevstring(&resp,15));
    ui->pult7->setStyleSheet(this->getdevstring(&resp,16));
    ui->pult8->setStyleSheet(this->getdevstring(&resp,17));
    ui->MN141->setStyleSheet(QString::fromUtf8("background-image: url(:/MN141_on.png);"));
    ui->MN401->setStyleSheet(this->getdevstring(&resp,9));
    }
    else
    {
        ui->MN141->setStyleSheet(QString::fromUtf8("background-image: url(:/MN141.png);"));
        ui->MN111->setStyleSheet(QString::fromUtf8(""));
        ui->MN401->setStyleSheet(QString::fromUtf8(""));
        ui->pos1->setStyleSheet(QString::fromUtf8(""));
        ui->pos2->setStyleSheet(QString::fromUtf8(""));
        ui->pos3->setStyleSheet(QString::fromUtf8(""));
        ui->pos4->setStyleSheet(QString::fromUtf8(""));
        ui->pos5->setStyleSheet(QString::fromUtf8(""));
        ui->pos6->setStyleSheet(QString::fromUtf8(""));
        ui->pos7->setStyleSheet(QString::fromUtf8(""));
        ui->pos8->setStyleSheet(QString::fromUtf8(""));
        ui->pult1->setStyleSheet(QString::fromUtf8(""));
        ui->pult2->setStyleSheet(QString::fromUtf8(""));
        ui->pult3->setStyleSheet(QString::fromUtf8(""));
        ui->pult4->setStyleSheet(QString::fromUtf8(""));
        ui->pult5->setStyleSheet(QString::fromUtf8(""));
        ui->pult6->setStyleSheet(QString::fromUtf8(""));
        ui->pult7->setStyleSheet(QString::fromUtf8(""));
        ui->pult8->setStyleSheet(QString::fromUtf8(""));
    }
}

QString MainWindow::getdevstring(MN401* mn401cfg, int position)
{
    switch(mn401cfg->devlist().Get(position))
    {
        case CCKTypeDevice::DT_None:
        return QString::fromUtf8("");
        break;
        case CCKTypeDevice::DT_MN921:
            return QString::fromUtf8("background-image: url(:/MN921.png);");
        break;
        case CCKTypeDevice::DT_MN825:
            return QString::fromUtf8("background-image: url(:/MN825.png);");
        break;
        case CCKTypeDevice::DT_MN524:
            return QString::fromUtf8("background-image: url(:/MN524.png);");
        break;
        case CCKTypeDevice::DT_MN401:
            return QString::fromUtf8("background-image: url(:/MN401.png);");
        break;
        case CCKTypeDevice::DT_MN111:
            return QString::fromUtf8("background-image: url(:/MN111.png);");
        break;
        case CCKTypeDevice::DT_PO06:
            return QString::fromUtf8("background-image: url(:/PO06.png);");
        break;
        case CCKTypeDevice::DT_PO07:
            return QString::fromUtf8("background-image: url(:/PO07.png);");
        break;
        case CCKTypeDevice::DT_PO08:
            return QString::fromUtf8("background-image: url(:/PO08.png);");
        break;
        case CCKTypeDevice::DT_VirtPO:
            return QString::fromUtf8("");
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MN141_clicked()
{
    if(this->on == true)
    {
    ui->MN141->setStyleSheet(QString::fromUtf8("background-image: url(:/MN141.png);"));
    ui->MN401->setStyleSheet(QString::fromUtf8(""));
    ui->pos1->setStyleSheet(QString::fromUtf8(""));
    ui->pos2->setStyleSheet(QString::fromUtf8(""));
    ui->pos3->setStyleSheet(QString::fromUtf8(""));
    ui->pos4->setStyleSheet(QString::fromUtf8(""));
    ui->pos5->setStyleSheet(QString::fromUtf8(""));
    ui->pos6->setStyleSheet(QString::fromUtf8(""));
    ui->pos7->setStyleSheet(QString::fromUtf8(""));
    ui->pos8->setStyleSheet(QString::fromUtf8(""));
    ui->pult1->setStyleSheet(QString::fromUtf8(""));
    ui->pult2->setStyleSheet(QString::fromUtf8(""));
    ui->pult3->setStyleSheet(QString::fromUtf8(""));
    ui->pult4->setStyleSheet(QString::fromUtf8(""));
    ui->pult5->setStyleSheet(QString::fromUtf8(""));
    ui->pult6->setStyleSheet(QString::fromUtf8(""));
    ui->pult7->setStyleSheet(QString::fromUtf8(""));
    ui->pult8->setStyleSheet(QString::fromUtf8(""));
    ui->MN111->setStyleSheet(QString::fromUtf8(""));
    this->on = false;
    }
    else
    {
    auto client = CCKConfig::NewStub(grpc::CreateChannel(this->connparametr.toLatin1().data(), grpc::InsecureChannelCredentials()));
    GetDeviceRq rq;
    rq.set_id(0);
    MN401 resp;
    ClientContext context;
    auto status = client->GetCfgMN401(&context,rq,&resp);
    if(status.ok() == true)
    {
    ui->MN111->setStyleSheet(this->getdevstring(&resp,0));
    ui->pos1->setStyleSheet(this->getdevstring(&resp,1));
    ui->pos2->setStyleSheet(this->getdevstring(&resp,2));
    ui->pos3->setStyleSheet(this->getdevstring(&resp,3));
    ui->pos4->setStyleSheet(this->getdevstring(&resp,4));
    ui->pos5->setStyleSheet(this->getdevstring(&resp,5));
    ui->pos6->setStyleSheet(this->getdevstring(&resp,6));
    ui->pos7->setStyleSheet(this->getdevstring(&resp,7));
    ui->pos8->setStyleSheet(this->getdevstring(&resp,8));
    ui->pult1->setStyleSheet(this->getdevstring(&resp,10));
    ui->pult2->setStyleSheet(this->getdevstring(&resp,11));
    ui->pult3->setStyleSheet(this->getdevstring(&resp,12));
    ui->pult4->setStyleSheet(this->getdevstring(&resp,13));
    ui->pult5->setStyleSheet(this->getdevstring(&resp,14));
    ui->pult6->setStyleSheet(this->getdevstring(&resp,15));
    ui->pult7->setStyleSheet(this->getdevstring(&resp,16));
    ui->pult8->setStyleSheet(this->getdevstring(&resp,17));
    ui->MN141->setStyleSheet(QString::fromUtf8("background-image: url(:/MN141_on.png);"));
    ui->MN401->setStyleSheet(this->getdevstring(&resp,9));
    }
    this->on = true;
    }

}

void MainWindow::on_pos1_clicked()
{
    auto client = CCKConfig::NewStub(grpc::CreateChannel(this->connparametr.toLatin1().data(), grpc::InsecureChannelCredentials()));
    GetDeviceRq rq;
    rq.set_id(1);
    MN mncfg;
    ClientContext context;
    SetDeviceResp resp;
    auto status = client->GetCfgMN(&context,rq,&mncfg);
    if(status.ok() == true)
    {
        MN921Cfg* mncfgdialog = new MN921Cfg(&mncfg);
        mncfgdialog->exec();
        auto client = CCKConfig::NewStub(grpc::CreateChannel(this->connparametr.toLatin1().data(), grpc::InsecureChannelCredentials()));
        auto status = client->SetCfgMN(&context,mncfg,&resp);
    }
}
