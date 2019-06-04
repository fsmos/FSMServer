#ifndef ELLISTABONENTPO_H
#define ELLISTABONENTPO_H

#include <QWidget>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"

using fsm::PO_Subscriber;

namespace Ui {
class Ellistabonentpo;
}

class Ellistabonentpo : public QWidget
{
    Q_OBJECT

public:
    explicit Ellistabonentpo(PO_Subscriber* subscriber, int index, QWidget *parent = nullptr);
    ~Ellistabonentpo();
    void Save();

private:
    Ui::Ellistabonentpo *ui;
    PO_Subscriber* subscriber;
};

#endif // ELLISTABONENTPO_H
