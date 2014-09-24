#include "delconfirmdialog.h"

DelConfirmDialog::DelConfirmDialog(QWidget *parent) :
    QDialog(parent)
{
    setModal(true);
    confirm_l = new QLabel("Are you sure you wish to delete?");
    yes = new QPushButton("Yes");
    no = new QPushButton("No");
    lay = new QGridLayout(this);
    lay->addWidget(confirm_l,0,0);
    lay->addWidget(yes,0,1);
    lay->addWidget(no,1,1);
    lay->addItem(new QSpacerItem(lay->columnMinimumWidth(1),lay->rowMinimumHeight(1)),1,0);
    connect(yes,SIGNAL(clicked()),this,SLOT(accept()));
    connect(no,SIGNAL(clicked()),this,SLOT(reject()));
}
