#ifndef CLIENTCFGFORM_H
#define CLIENTCFGFORM_H

#include <QDialog>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"

namespace Ui {
class ClientCfgForm;
}
using fsm::ClientInfo;


class ClientCfgForm : public QDialog
{
    Q_OBJECT

public:
    explicit ClientCfgForm(ClientInfo* cinfo, QWidget *parent = 0);
    ClientInfo* cinfo;
    ~ClientCfgForm();

private slots:
    void on_savebutton_clicked();

private:
    Ui::ClientCfgForm *ui;
};

#endif // CLIENTCFGFORM_H
