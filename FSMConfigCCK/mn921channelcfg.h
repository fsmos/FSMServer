#ifndef MN921CHANNELCFG_H
#define MN921CHANNELCFG_H

#include <QDialog>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"

using fsm::MN;
using fsm::MNTypeDevice;
using fsm::MN_Channel;
using fsm::MN921TypeATS;
using fsm::MN921TypeTCH;
using fsm::MN921OutputCallFrequency;


namespace Ui {
class mn921channelcfg;
}

class mn921channelcfg : public QDialog
{
    Q_OBJECT

public:
    explicit mn921channelcfg(MN_Channel* mncfg,QWidget *parent = nullptr);
    ~mn921channelcfg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::mn921channelcfg *ui;
    MN_Channel* channelcfg;
};

#endif // MN921CHANNELCFG_H
