#ifndef ABONENTMNCFG_H
#define ABONENTMNCFG_H

#include <QDialog>

namespace Ui {
class abonentmncfg;
}

class abonentmncfg : public QDialog
{
    Q_OBJECT

public:
    explicit abonentmncfg(QWidget *parent = 0);
    ~abonentmncfg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::abonentmncfg *ui;
};

#endif // ABONENTMNCFG_H
