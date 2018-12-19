#ifndef MN921CFG_H
#define MN921CFG_H

#include <QDialog>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"

using fsm::MN;
using fsm::MNTypeDevice;

namespace Ui {
class MN921Cfg;
}

class MN921Cfg : public QDialog
{
    Q_OBJECT

public:
    explicit MN921Cfg(MN* mncfg,QWidget *parent = 0);
    ~MN921Cfg();

private slots:
    void on_gr_spin1_valueChanged(int arg1);

    void on_gr_dial1_valueChanged(int value);

    void on_gr_spin2_valueChanged(int arg1);

    void on_gr_dial2_valueChanged(int value);

    void on_mb_ch1_clicked();

    void on_cb_ch1_clicked();

    void on_tch_ch1_clicked();

    void on_ats_ch1_clicked();

    void on_r168_ch1_clicked();

    void on_r168100kb_ch1_clicked();

    void on_mb_ch2_clicked();

    void on_cb_ch2_clicked();

    void on_tch_ch2_clicked();

    void on_ats_ch2_clicked();

    void on_r168_ch2_clicked();

    void on_r168100kb_ch2_clicked();

    void on_savetodevice_clicked();

    void on_netsetting_clicked();

private:
    Ui::MN921Cfg *ui;
    MN* cfg;
};

#endif // MN921CFG_H
