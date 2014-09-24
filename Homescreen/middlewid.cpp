#include "middlewid.h"

MiddleWid::MiddleWid(QString *arg,QWidget *parent) :
    QWidget(parent)
{
    rootdir=arg;
    filelist = new QListWidget();
    filelist->setSelectionMode(QAbstractItemView::SingleSelection);
    iconViewer = new QLabel();
    iconViewer->setMaximumSize(200,300);
    iconViewer->setPixmap(QPixmap::fromImage(QImage(":/appicon.png").scaled(200,300)));
    //adViewer->load(QUrl("http://www.google.co.in"));
    lay = new QHBoxLayout(this);
    populateList();

}

void MiddleWid::populateList()  {
    lay->removeWidget(filelist);
    delete(filelist);
    qDebug() << "here";
    QDir dir(*rootdir);
    qDebug() << *rootdir;
    QStringList filters;
    filters << "*.xml";
    dir.setNameFilters(filters);
    QStringList list = dir.entryList(QDir::Files,QDir::Time);
    qDebug() << list;
    lay->removeWidget(iconViewer);
    filelist=new QListWidget();
    filelist->insertItems(0,list);
    //filelist->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Preferred);
    lay->addWidget(filelist);
    lay->addWidget(iconViewer);
    connect(filelist,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemSelected(QListWidgetItem*)));
    connect(filelist,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemOpened(QListWidgetItem*)));
}

void MiddleWid::itemSelected(QListWidgetItem *item) {
    QList<QListWidgetItem *> selected;
    selected=filelist->selectedItems();
    QListWidgetItem *i;
    //QList<int> indexes;
    QStringList names;
    foreach(i,selected) {
        names << i->text();
    }
    emit sendSelectedList(names);
}

void MiddleWid::itemOpened(QListWidgetItem *item)   {
    emit displayContent(item->text());
}

void MiddleWid::setMarkMode(bool status)    {
    if(status)
        filelist->setSelectionMode(QAbstractItemView::MultiSelection);
    else
        filelist->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MiddleWid::showSearchResults(QStringList names) {
    filelist->clear();
    filelist->insertItems(0,names);
}

void MiddleWid::setSearchModeOn(bool status)    {
    if(status)
        filelist->clear();
    else    {
        populateList();
    }
}
