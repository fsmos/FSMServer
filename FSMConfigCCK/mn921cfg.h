#ifndef MN921CFG_H
#define MN921CFG_H

#include <QDialog>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"

using fsm::MN;
using fsm::MNTypeDevice;
using fsm::MN_Channel;

namespace Ui {
class MN921Cfg;
}

class MN921Cfg : public QDialog
{
    Q_OBJECT

public:
    explicit MN921Cfg(MN* mncfg,unsigned char type, QWidget *parent = 0);
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

    void on_setabonent_1_clicked();

    void on_setabonent_2_clicked();

    void on_setch_1_clicked();

    void on_setch_2_clicked();

    void on_r168seting_clicked();

private:
    Ui::MN921Cfg *ui;
    MN* cfg;
    MN_Channel* channel[2];

};

#endif // MN921CFG_H
