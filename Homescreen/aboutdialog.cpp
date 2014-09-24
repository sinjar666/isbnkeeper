#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    setModal(false);
    view = new QLabel();
    view->setPixmap(QPixmap(QString(":/about.jpg")));
    area = new QScrollArea();
    area->setWidget(view);
    lay = new QHBoxLayout(this);
    lay->addWidget(area);
}
