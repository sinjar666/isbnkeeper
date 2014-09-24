#include "loaderwidget.h"

LoaderWidget::LoaderWidget(QWidget *parent) :
    QWidget(parent)
{
    //viewer=new QDeclarativeView(QUrl("qrc:/retrieving.qml"));
    label = new QLabel("<font size=10> Retrieving..</font>");
    label->setAlignment(Qt::AlignCenter);
    lay = new QHBoxLayout(this);
    //lay->setMargin(50);
    lay->addWidget(label);
}
