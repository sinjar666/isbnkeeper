#include "fatalnotavail.h"

FatalNotAvail::FatalNotAvail(QString path, QWidget *parent) :
    QDialog(parent)
{
    setModal(true);
    lay = new QHBoxLayout(this);
    msg = new QLabel(QString("The root directory ")+path+QString(" is not ready or writeable. Ensure that the device is available before proceeding. If you have deleted the root directory you must reset the app. Press Reset to do that and exit..."));
    msg->setWordWrap(true);
    button = new QPushButton(tr("Exit"));
    reset = new QPushButton(tr("Reset"));
    lay->addWidget(msg);
    lay->addWidget(reset);
    lay->addWidget(button);
    connect(button,SIGNAL(clicked()),this,SLOT(accept()));
    connect(reset,SIGNAL(clicked()),this,SLOT(resetApp()));
}

void FatalNotAvail::resetApp()  {
    QFile t(tr("/home/user/.isbnkeeper-config"));
    t.remove();
    accept();
}
