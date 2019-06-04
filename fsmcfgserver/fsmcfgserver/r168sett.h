#ifndef R168SETT_H
#define R168SETT_H

#include <QDialog>

namespace Ui {
class r168sett;
}

class r168sett : public QDialog
{
    Q_OBJECT

public:
    explicit r168sett(QWidget *parent = nullptr);
    ~r168sett();

private:
    Ui::r168sett *ui;
};

#endif // R168SETT_H
