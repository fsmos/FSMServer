#include "groupselect.h"
#include "ui_groupselect.h"

GroupSelect::GroupSelect(P0_Group_el* el,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupSelect)
{
    ui->setupUi(this);
    this->elem = el;
    if(el->grp_size() > 0) {
      if(el->mutable_grp(0)->abonent_size() > 0) ui->grp_1_1->setText(QString::number(el->mutable_grp(0)->abonent(0)));
      if(el->mutable_grp(0)->abonent_size() > 1) ui->grp_1_2->setText(QString::number(el->mutable_grp(0)->abonent(1)));
      if(el->mutable_grp(0)->abonent_size() > 2) ui->grp_1_3->setText(QString::number(el->mutable_grp(0)->abonent(2)));
      if(el->mutable_grp(0)->abonent_size() > 3) ui->grp_1_4->setText(QString::number(el->mutable_grp(0)->abonent(3)));
      if(el->mutable_grp(0)->abonent_size() > 4) ui->grp_1_5->setText(QString::number(el->mutable_grp(0)->abonent(4)));
      if(el->mutable_grp(0)->abonent_size() > 5) ui->grp_1_6->setText(QString::number(el->mutable_grp(0)->abonent(5)));
      if(el->mutable_grp(0)->abonent_size() > 6) ui->grp_1_7->setText(QString::number(el->mutable_grp(0)->abonent(6)));
      if(el->mutable_grp(0)->abonent_size() > 7) ui->grp_1_8->setText(QString::number(el->mutable_grp(0)->abonent(7)));
      if(el->mutable_grp(0)->abonent_size() > 8) ui->grp_1_9->setText(QString::number(el->mutable_grp(0)->abonent(8)));
      if(el->mutable_grp(0)->abonent_size() > 9) ui->grp_1_10->setText(QString::number(el->mutable_grp(0)->abonent(9)));
      if(el->mutable_grp(0)->abonent_size() > 10) ui->grp_1_11->setText(QString::number(el->mutable_grp(0)->abonent(10)));
      if(el->mutable_grp(0)->abonent_size() > 11) ui->grp_1_12->setText(QString::number(el->mutable_grp(0)->abonent(11)));
    }
    if(el->grp_size() > 1) {
      if(el->mutable_grp(1)->abonent_size() > 0) ui->grp_2_1->setText(QString::number(el->mutable_grp(1)->abonent(0)));
      if(el->mutable_grp(1)->abonent_size() > 1) ui->grp_2_2->setText(QString::number(el->mutable_grp(1)->abonent(1)));
      if(el->mutable_grp(1)->abonent_size() > 2) ui->grp_2_3->setText(QString::number(el->mutable_grp(1)->abonent(2)));
      if(el->mutable_grp(1)->abonent_size() > 3) ui->grp_2_4->setText(QString::number(el->mutable_grp(1)->abonent(3)));
      if(el->mutable_grp(1)->abonent_size() > 4) ui->grp_2_5->setText(QString::number(el->mutable_grp(1)->abonent(4)));
      if(el->mutable_grp(1)->abonent_size() > 5) ui->grp_2_6->setText(QString::number(el->mutable_grp(1)->abonent(5)));
      if(el->mutable_grp(1)->abonent_size() > 6) ui->grp_2_7->setText(QString::number(el->mutable_grp(1)->abonent(6)));
      if(el->mutable_grp(1)->abonent_size() > 7) ui->grp_2_8->setText(QString::number(el->mutable_grp(1)->abonent(7)));
      if(el->mutable_grp(1)->abonent_size() > 8) ui->grp_2_9->setText(QString::number(el->mutable_grp(1)->abonent(8)));
      if(el->mutable_grp(1)->abonent_size() > 9) ui->grp_2_10->setText(QString::number(el->mutable_grp(1)->abonent(9)));
      if(el->mutable_grp(1)->abonent_size() > 10) ui->grp_2_11->setText(QString::number(el->mutable_grp(1)->abonent(10)));
      if(el->mutable_grp(1)->abonent_size() > 11) ui->grp_2_12->setText(QString::number(el->mutable_grp(1)->abonent(11)));
    }
    if(el->grp_size() > 2) {
      if(el->mutable_grp(2)->abonent_size() > 0) ui->grp_3_1->setText(QString::number(el->mutable_grp(2)->abonent(0)));
      if(el->mutable_grp(2)->abonent_size() > 1) ui->grp_3_2->setText(QString::number(el->mutable_grp(2)->abonent(1)));
      if(el->mutable_grp(2)->abonent_size() > 2) ui->grp_3_3->setText(QString::number(el->mutable_grp(2)->abonent(2)));
      if(el->mutable_grp(2)->abonent_size() > 3) ui->grp_3_4->setText(QString::number(el->mutable_grp(2)->abonent(3)));
      if(el->mutable_grp(2)->abonent_size() > 4) ui->grp_3_5->setText(QString::number(el->mutable_grp(2)->abonent(4)));
      if(el->mutable_grp(2)->abonent_size() > 5) ui->grp_3_6->setText(QString::number(el->mutable_grp(2)->abonent(5)));
      if(el->mutable_grp(2)->abonent_size() > 6) ui->grp_3_7->setText(QString::number(el->mutable_grp(2)->abonent(6)));
      if(el->mutable_grp(2)->abonent_size() > 7) ui->grp_3_8->setText(QString::number(el->mutable_grp(2)->abonent(7)));
      if(el->mutable_grp(2)->abonent_size() > 8) ui->grp_3_9->setText(QString::number(el->mutable_grp(2)->abonent(8)));
      if(el->mutable_grp(2)->abonent_size() > 9) ui->grp_3_10->setText(QString::number(el->mutable_grp(2)->abonent(9)));
      if(el->mutable_grp(2)->abonent_size() > 10) ui->grp_3_11->setText(QString::number(el->mutable_grp(2)->abonent(10)));
      if(el->mutable_grp(2)->abonent_size() > 11) ui->grp_3_12->setText(QString::number(el->mutable_grp(2)->abonent(11)));
    }
    if(el->grp_size() > 3) {
      if(el->mutable_grp(3)->abonent_size() > 0) ui->grp_4_1->setText(QString::number(el->mutable_grp(3)->abonent(0)));
      if(el->mutable_grp(3)->abonent_size() > 1) ui->grp_4_2->setText(QString::number(el->mutable_grp(3)->abonent(1)));
      if(el->mutable_grp(3)->abonent_size() > 2) ui->grp_4_3->setText(QString::number(el->mutable_grp(3)->abonent(2)));
      if(el->mutable_grp(3)->abonent_size() > 3) ui->grp_4_4->setText(QString::number(el->mutable_grp(3)->abonent(3)));
      if(el->mutable_grp(3)->abonent_size() > 4) ui->grp_4_5->setText(QString::number(el->mutable_grp(3)->abonent(4)));
      if(el->mutable_grp(3)->abonent_size() > 5) ui->grp_4_6->setText(QString::number(el->mutable_grp(3)->abonent(5)));
      if(el->mutable_grp(3)->abonent_size() > 6) ui->grp_4_7->setText(QString::number(el->mutable_grp(3)->abonent(6)));
      if(el->mutable_grp(3)->abonent_size() > 7) ui->grp_4_8->setText(QString::number(el->mutable_grp(3)->abonent(7)));
      if(el->mutable_grp(3)->abonent_size() > 8) ui->grp_4_9->setText(QString::number(el->mutable_grp(3)->abonent(8)));
      if(el->mutable_grp(3)->abonent_size() > 9) ui->grp_4_10->setText(QString::number(el->mutable_grp(3)->abonent(9)));
      if(el->mutable_grp(3)->abonent_size() > 10) ui->grp_4_11->setText(QString::number(el->mutable_grp(3)->abonent(10)));
      if(el->mutable_grp(3)->abonent_size() > 11) ui->grp_4_12->setText(QString::number(el->mutable_grp(3)->abonent(11)));
    }

}

GroupSelect::~GroupSelect()
{
    delete ui;
}
void GroupSelect::AddAbonent(QLineEdit* le, int i, int j) {
    if(this->elem->mutable_grp(i)->abonent_size() <= j)
    {
        elem->mutable_grp(i)->add_abonent(le->text().toUInt());
    } else {
        elem->mutable_grp(i)->set_abonent(j,le->text().toUInt());
    }
}
void GroupSelect::on_pushButton_clicked()
{
    if(this->elem->grp_size() <= 0) elem->add_grp();

    AddAbonent(ui->grp_1_1,0,0);
    AddAbonent(ui->grp_1_2,0,1);
    AddAbonent(ui->grp_1_3,0,2);
    AddAbonent(ui->grp_1_4,0,3);
    AddAbonent(ui->grp_1_5,0,4);
    AddAbonent(ui->grp_1_6,0,5);
    AddAbonent(ui->grp_1_7,0,6);
    AddAbonent(ui->grp_1_8,0,7);
    AddAbonent(ui->grp_1_9,0,8);
    AddAbonent(ui->grp_1_10,0,9);
    AddAbonent(ui->grp_1_11,0,10);
    AddAbonent(ui->grp_1_12,0,11);

    if(this->elem->grp_size() <= 1) elem->add_grp();

    AddAbonent(ui->grp_2_1,1,0);
    AddAbonent(ui->grp_2_2,1,1);
    AddAbonent(ui->grp_2_3,1,2);
    AddAbonent(ui->grp_2_4,1,3);
    AddAbonent(ui->grp_2_5,1,4);
    AddAbonent(ui->grp_2_6,1,5);
    AddAbonent(ui->grp_2_7,1,6);
    AddAbonent(ui->grp_2_8,1,7);
    AddAbonent(ui->grp_2_9,1,8);
    AddAbonent(ui->grp_2_10,1,9);
    AddAbonent(ui->grp_2_11,1,10);
    AddAbonent(ui->grp_2_12,1,11);

    if(this->elem->grp_size() <= 2) elem->add_grp();

    AddAbonent(ui->grp_3_1,2,0);
    AddAbonent(ui->grp_3_2,2,1);
    AddAbonent(ui->grp_3_3,2,2);
    AddAbonent(ui->grp_3_4,2,3);
    AddAbonent(ui->grp_3_5,2,4);
    AddAbonent(ui->grp_3_6,2,5);
    AddAbonent(ui->grp_3_7,2,6);
    AddAbonent(ui->grp_3_8,2,7);
    AddAbonent(ui->grp_3_9,2,8);
    AddAbonent(ui->grp_3_10,2,9);
    AddAbonent(ui->grp_3_11,2,10);
    AddAbonent(ui->grp_3_12,2,11);

    if(this->elem->grp_size() <= 3) elem->add_grp();

    AddAbonent(ui->grp_4_1,3,0);
    AddAbonent(ui->grp_4_2,3,1);
    AddAbonent(ui->grp_4_3,3,2);
    AddAbonent(ui->grp_4_4,3,3);
    AddAbonent(ui->grp_4_5,3,4);
    AddAbonent(ui->grp_4_6,3,5);
    AddAbonent(ui->grp_4_7,3,6);
    AddAbonent(ui->grp_4_8,3,7);
    AddAbonent(ui->grp_4_9,3,8);
    AddAbonent(ui->grp_4_10,3,9);
    AddAbonent(ui->grp_4_11,3,10);
    AddAbonent(ui->grp_4_12,3,11);
    accept();
}
