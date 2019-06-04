#include "poabonentlist.h"
#include "ui_poabonentlist.h"

POAbonentList::POAbonentList(PO_Channel* channel, int count , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::POAbonentList)
{
    ui->setupUi(this);
    this->channel = channel;
    this->count = count;
    for(int i=0;i<count;i++) {
        if(this->channel->subscriberforcall_size() <= i) channel->add_subscriberforcall();
        el_abonent[i] = new Ellistabonentpo(channel->mutable_subscriberforcall(i),i);
        ui->listabonent->addWidget(el_abonent[i]);
    }
}

POAbonentList::~POAbonentList()
{
    delete ui;
}

void POAbonentList::on_pushButton_clicked()
{
    for(int i=0;i<count;i++) {
        el_abonent[i]->Save();
    }
    accept();
}
