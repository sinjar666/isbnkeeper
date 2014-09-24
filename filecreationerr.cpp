#include "filecreationerr.h"

FileCreationErr::FileCreationErr(QWidget *parent) :
    QDialog(parent)
{
    setModal(true);
    lay = new QHBoxLayout(this);
    msg = new QLabel(tr("Unable to write to disk. Disk may be write protected."));
    msg->setWordWrap(true);
    okButton = new QPushButton(tr("Ok"));
    lay->addWidget(msg);
    lay->addWidget(okButton);
    connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
}
