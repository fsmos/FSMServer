#ifndef R168S_H
#define R168S_H

#include <QDialog>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"

using fsm::MN;

namespace Ui {
class r168s;
}

class r168s : public QDialog
{
    Q_OBJECT

public:
    explicit r168s(MN* cfg,QWidget *parent = nullptr);
    ~r168s();

private slots:
    void on_pushButton_clicked();
    unsigned short getConfigureInfo();
    void setConfigureInfo(unsigned short _value);

private:
    Ui::r168s *ui;
    MN* cfgmn;
};

#endif // R168S_H
