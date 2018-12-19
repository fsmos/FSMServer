#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"
namespace Ui {
class MainWindow;
}
using fsm::CCKConfig;
using fsm::GetDeviceRq;
using fsm::SetDeviceResp;
using fsm::MN401;
using fsm::MN;
using fsm::P0;
using fsm::VirtP0;
using fsm::CCKTypeDevice;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString getdevstring(MN401* mn401cfg,int position);
    QString connparametr;

private slots:
    void on_MN141_clicked();

    void on_pos1_clicked();

private:
    Ui::MainWindow *ui;
    bool on;
};

#endif // MAINWINDOW_H
