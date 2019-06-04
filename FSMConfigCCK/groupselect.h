#ifndef GROUPSELECT_H
#define GROUPSELECT_H

#include <QDialog>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"
#include <QLineEdit>
using fsm::P0_Group_el;

namespace Ui {
class GroupSelect;
}

class GroupSelect : public QDialog
{
    Q_OBJECT

public:
    explicit GroupSelect(P0_Group_el* el,QWidget *parent = nullptr);
    ~GroupSelect();
    void AddAbonent(QLineEdit* le, int i, int j);

private slots:
    void on_pushButton_clicked();

private:
    Ui::GroupSelect *ui;
    P0_Group_el* elem;
};

#endif // GROUPSELECT_H
