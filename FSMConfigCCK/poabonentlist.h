#ifndef POABONENTLIST_H
#define POABONENTLIST_H

#include <QDialog>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"
#include "ellistabonentpo.h"

using fsm::PO_Channel;

namespace Ui {
class POAbonentList;
}

class POAbonentList : public QDialog
{
    Q_OBJECT

public:
    explicit POAbonentList(PO_Channel* channel, int count ,QWidget *parent = nullptr);
    ~POAbonentList();

private slots:
    void on_pushButton_clicked();

private:
    Ui::POAbonentList *ui;
    PO_Channel* channel;
    int count;
    Ellistabonentpo* el_abonent[16];
};

#endif // POABONENTLIST_H
