#include "mainwindow.h"
#include "ui_mainwindow.h"
extern "C"
{
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fsm_electrodevice.h"
#include "FSM/FSMDevice/fsm_statusstruct.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMSetting/FSM_settings.h"
}
#include <QDir>
#include <QtXml>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AddDeviceIcons();
    server = new QLocalServer();
    if (!server->listen("fsmstat"))
    {
    qDebug("eror");
    server->close();
    close();
    }
    connect(server,SIGNAL(newConnection()),this,SLOT(RepaintDevicePanel()));
    fsmdat.cmd=FSMIOCTLStat_Requst;
    fsmdat.IDDevice=FSM_StatistickIOCtlId;
    fsmdat.countparam=1;
    qDebug("Start");
    FSM_SendCtlCmd(&fsmdat);
//}
// (0,new QListWidgetItem(dev_list["fsmelsheet1"].QFSMIC[0].icn,dev_list["fsmelsheet1"].QFSMIC[0].icndesc));
}

MainWindow::~MainWindow()
{
    delete ui;
    server->close();
}
void MainWindow::RepaintDevicePanel()
{
    QLocalSocket *clientConnection = server->nextPendingConnection();
    qDebug("Event");
    fsmdat.cmd=FSMIOCTLStat_Read;
    //qDebug("Memcpy sg");
    //memcpy(&fsmststr,fsmdat.Data,sizeof(struct fsm_statusstruct));
    qDebug("Memcpy Clear");
    int sh=0;
    ui->treeWidget->clear();
    for(int i=0;i<scolumn_cnt;i++)
        for(int j=0;j<srow_cnt;j++)
        {
            fsmdat.Data[0]=j;
            fsmdat.Data[1]=i;
            qDebug("Send cMD");
            FSM_SendCtlCmd(&fsmdat);
            qDebug("Memcpy");
            memcpy(&fsmststr.statel[j][i],fsmdat.Data,sizeof(struct fsm_status_element));
            ui->tableWidget->setItem(j,i,new QTableWidgetItem());
            ui->tableWidget->item(j,i)->setIcon(dev_list[fsmststr.statel[j][i].fsmdevcode].QFSMIC[fsmststr.statel[j][i].state].icn);
            ui->tableWidget->item(j,i)->setToolTip(dev_list[fsmststr.statel[j][i].fsmdevcode].name+"-"+dev_list[fsmststr.statel[j][i].fsmdevcode].QFSMIC[fsmststr.statel[j][i].state].name);
            ui->treeWidget->insertTopLevelItem(sh,new QTreeWidgetItem(QStringList(((QString("%1: ").arg(sh)+dev_list[fsmststr.statel[j][i].fsmdevcode].name+"-"+dev_list[fsmststr.statel[j][i].fsmdevcode].QFSMIC[fsmststr.statel[j][i].state].name)))));
            sh++;
        }

   clientConnection->flush();
   clientConnection->disconnectFromServer();
}

void MainWindow::AddDeviceIcons()
{
FSMDev dev;
QDir dir("devices");
QFileInfoList dirContent = dir.entryInfoList(QStringList(),
          QDir::Dirs | QDir::NoDotAndDotDot);
for(int i=0;i<dirContent.count();i++)
{

    QSettings settings(dirContent[i].absoluteFilePath()+"/index.fsmdev", QSettings::IniFormat);
    dev.name=settings.value("Name").toString();
    dev.exec=settings.value("exec").toString();
    for(int j=0;j<settings.childGroups().count();j++)
    {
     dev.QFSMIC[settings.childGroups()[j]].name=settings.value(settings.childGroups()[j]+"/Name").toString();
     dev.QFSMIC[settings.childGroups()[j]].icn=QIcon((dirContent[i].absoluteFilePath())+"/"+(settings.value(settings.childGroups()[j]+"/img").toString()));
     dev.QFSMIC[settings.childGroups()[j]].exec=settings.value(settings.childGroups()[j]+"/exec").toString();
    }
    dev_list[dirContent[i].baseName()]=dev;
}
}

void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
    setWindowTitle(((QString("%1").arg((fsmststr.statel[index.row()][index.column()].devid)))));
    setWindowIcon(dev_list[fsmststr.statel[index.row()][index.column()].fsmdevcode].QFSMIC[fsmststr.statel[index.row()][index.column()].state].icn);
}

void MainWindow::on_treeWidget_activated(const QModelIndex &index)
{

}

void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    setWindowTitle((QString("%1").arg(index.row())));

}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{

    QProcess::execute(QString("devices/%1/").arg(fsmststr.statel[index.row()][index.column()].fsmdevcode)+dev_list[fsmststr.statel[index.row()][index.column()].fsmdevcode].exec,QStringList()<<fsmststr.statel[index.row()][index.column()].fsmdevcode<<QString("%1").arg(fsmststr.statel[index.row()][index.column()].devid) );
    QProcess::execute(dev_list[fsmststr.statel[index.row()][index.column()].fsmdevcode].QFSMIC[fsmststr.statel[index.row()][index.column()].state].exec,QStringList()<<fsmststr.statel[index.row()][index.column()].fsmdevcode<<QString("%1").arg(fsmststr.statel[index.row()][index.column()].devid) );
}
