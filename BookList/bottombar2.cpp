#include "bottombar2.h"

BottomBar2::BottomBar2(QWidget *parent) :
    QWidget(parent)
{
    camera_b = new QPushButton("Camera.");
    mark_b = new QPushButton("Mark");
    mark_b->setCheckable(true);
    delete_b = new QPushButton("Delete");
    lay = new QHBoxLayout(this);
    lay->addWidget(camera_b);
    lay->addWidget(mark_b);
    lay->addWidget(delete_b);
    connect(mark_b,SIGNAL(toggled(bool)),this,SLOT(markToggled(bool)));
    connect(delete_b,SIGNAL(clicked()),this,SLOT(deletePressed()));
    connect(camera_b,SIGNAL(clicked()),this,SLOT(cameraPressed()));
}

void BottomBar2::cameraPressed() {
    emit activateCamera();
}

void BottomBar2::deletePressed() {
    emit requestDelete();
}

void BottomBar2::markToggled(bool checked)   {
    emit sendToggle(checked);
}
