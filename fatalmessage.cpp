#include "fatalmessage.h"

FatalMessage::FatalMessage(QWidget *parent) :
    QDialog(parent)
{
    setModal(true);
    lay = new QHBoxLayout(this);
    msg = new QLabel(tr("You MUST specify a VALID root directory for the application to function. Restart application and specify a VALID root directory. Exiting now"));
    msg->setWordWrap(true);
    okButton = new QPushButton(tr("Exit"));
    lay->addWidget(msg);
    lay->addWidget(okButton);
    connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
}
