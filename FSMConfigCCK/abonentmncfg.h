#ifndef ABONENTMNCFG_H
#define ABONENTMNCFG_H

#include <QDialog>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"

using fsm::MN_Channel;
namespace Ui {
class abonentmncfg;
}

class abonentmncfg : public QDialog
{
    Q_OBJECT

public:
    explicit abonentmncfg(MN_Channel* channel,QWidget *parent = 0);
    ~abonentmncfg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::abonentmncfg *ui;
    MN_Channel* channel;
};

#endif // ABONENTMNCFG_H
