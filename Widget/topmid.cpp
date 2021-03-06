#include "topmid.h"

Topmid::Topmid(QString path,QWidget *parent) :
    QWidget(parent)
{
    filepath=path;
    lay_h=new QHBoxLayout(this);
    lab_w=new QLabel();
    list_w=new QListWidget();
    list_w->setSelectionMode(QAbstractItemView::SingleSelection);
    //lay_h->addWidget(list_w);
    //lay_h->addWidget(lab_w);
    populatelist();
    connect(list_w,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(selecteditem(QListWidgetItem*)));
    connect(list_w,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(openeditem(QListWidgetItem*)));
    connect(list_w,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(loadimg(QListWidgetItem*)));

}
void Topmid::populatelist()
{
    lay_h->removeWidget(list_w);
    delete(list_w);
    lay_h->removeWidget(lab_w);
    delete(lab_w);
    QStringList list1;
    Xml_top=new Xfile();
    list1=Xml_top->displayxml(filepath);
    list_w=new QListWidget();
    lab_w=new QLabel();
    list_w->insertItems(0,list1);
    lay_h->addWidget(list_w);
    lay_h->addWidget(lab_w);
}
void Topmid::selecteditem(QListWidgetItem *item)
{
    QList<QListWidgetItem *> selected;
    selected=list_w->selectedItems();
    QListWidgetItem *i;
    QStringList list;
    foreach(i,selected)
    {
        list<<i->text();
    }
    emit itemselect(list);
}
void Topmid::openeditem(QListWidgetItem *item)
{
    emit itemopen(item->text());
}
void Topmid::setMarkMode(bool status)
{
    if(status)
        list_w->setSelectionMode(QAbstractItemView::MultiSelection);
    else
        list_w->setSelectionMode(QAbstractItemView::SingleSelection);
}

//void Topmid::loadimg(QListWidgetItem *item)
//{
//    QList<QListWidgetItem *> selected;
//    selected=list_w->selectedItems();
//    QListWidgetItem *i;
//    QStringList list;
//    foreach(i,selected)
//    {
//        list<<i->text();
//    }
//    emit itemselect(list);
//}
