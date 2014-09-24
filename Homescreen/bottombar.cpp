#include "bottombar.h"

BottomBar::BottomBar(QString *arg,QWidget *parent) :
    QWidget(parent)
{
    //obj=e;
    rootdir=arg;
    camera_b = new QPushButton("Camera.");
    new_b = new QPushButton("New File");
    delete_b = new QPushButton("Delete");
    lay = new QHBoxLayout(this);
    lay->addWidget(camera_b);
    lay->addWidget(new_b);
    lay->addWidget(delete_b);
    connect(new_b,SIGNAL(clicked()),this,SLOT(showNewFileDialog()));
    connect(delete_b,SIGNAL(clicked()),this,SLOT(deletePressed()));
    connect(camera_b,SIGNAL(clicked()),this,SLOT(cameraPressed()));
}

void BottomBar::cameraPressed() {
    emit activateCamera();
}

void BottomBar::deletePressed() {
    emit requestDelete();
}

void BottomBar::showNewFileDialog() {
    dialog = new NewFileDialog(*rootdir,this);
    dialog->exec();
    emit requestRefresh();
    //delete(dialog);
}

void BottomBar::enableCamera(bool status)   {
    if(status) camera_b->setEnabled(true);
    else camera_b->setDisabled(true);
}
