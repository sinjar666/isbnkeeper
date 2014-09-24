#include "errorfiledialog.h"

ErrorFileDialog::ErrorFileDialog(QWidget *parent) :
    QDialog(parent)
{
    setModal(true);
    lay = new QHBoxLayout(this);
    msg = new QLabel(tr("The file already exists!! Please change the name"));
    okButton = new QPushButton(tr("Ok"));
    lay->addWidget(msg);
    lay->addWidget(okButton);
    connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
}
