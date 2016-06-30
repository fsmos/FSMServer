#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QtNetwork>
#include "FSM/FSMDevice/fsm_statusstruct.h"
#include "FSM/FSMDevice/fcmprotocol.h"
typedef struct QIconFSMMod
{
    QString name;
    QString exec;
    QIcon icn;


} IcoFSM;

typedef struct FSMDevice
{
    QString name;
    QString exec;
    QMap<QString,IcoFSM> QFSMIC;
} FSMDev;

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMap<QString,FSMDev> dev_list;
    struct fsm_statusstruct fsmststr;
    void AddDeviceIcons();
    QTimer* ticktm;
    QLocalServer* server;
    struct FSM_SendCmdUserspace fsmdat;
private slots:
   void RepaintDevicePanel();
    void on_tableWidget_clicked(const QModelIndex &index);

    void on_treeWidget_activated(const QModelIndex &index);

    void on_treeWidget_clicked(const QModelIndex &index);

    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
