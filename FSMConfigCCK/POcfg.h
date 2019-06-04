#ifndef POCFG_H
#define POCFG_H

#include <QDialog>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"

using fsm::P0;
using fsm::PO_Channel;

namespace Ui {
class POCfg;
}

class POCfg : public QDialog
{
    Q_OBJECT

public:
    explicit POCfg(P0* mncfg,unsigned char type, QWidget *parent = 0);
    ~POCfg();

private slots:
    void on_gr_spin1_valueChanged(int arg1);

    void on_gr_dial1_valueChanged(int value);

    void on_gr_spin2_valueChanged(int arg1);

    void on_gr_dial2_valueChanged(int value);


    void on_savetodevice_clicked();

    void on_netsetting_clicked();

    void on_setabonent_1_clicked();

    void on_setabonent_2_clicked();

    void on_r168seting_clicked();

    void on_conf_clicked();

    void on_csv_clicked();

private:
    Ui::POCfg *ui;
    P0* cfg;
    PO_Channel* channel[2];
    int countel;

};

#endif // POCFG_H
