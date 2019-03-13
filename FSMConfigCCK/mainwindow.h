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
    MN401 mncfg;

private slots:
    void on_MN141_clicked();

    void on_pos1_clicked();

    void on_pos2_clicked();

    void on_pos3_clicked();

    void on_pos4_clicked();

    void on_pos5_clicked();

    void on_pos6_clicked();

    void on_pos7_clicked();

    void on_pos8_clicked();

    void on_pult1_clicked();

    void on_pult2_clicked();

    void on_pult3_clicked();

    void on_pult4_clicked();

    void on_pult5_clicked();

    void on_pult6_clicked();

    void on_pult7_clicked();

    void on_pult8_clicked();

private:
    Ui::MainWindow *ui;
    void OpenSettingStation(int position);
    bool on;
};

#endif // MAINWINDOW_H
