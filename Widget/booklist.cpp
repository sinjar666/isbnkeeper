#include "booklist.h"

Booklist::Booklist(QString path,QWidget *parent) :
    QWidget(parent)
{
    filepath=path;
    top_w=new Topmid();
    bottom_w=new BottomBar();
    layout_w=new QVBoxLayout(this);
    layout_w->addWidget(top_w);
    layout_w->addWidget(bottom_w);
    connect(bottom_w,SIGNAL(activateCamera()),this,SLOT(activateCamera()));
    connect(bottom_w,SIGNAL(requestDelete()),this,SLOT(deletepressed()));
    connect(bottom_w,SIGNAL(sendToggle(bool)),this,SLOT(markpressed(bool)));
    connect(top_w,SIGNAL(itemselect(QStringList)),this,SLOT(selected_item(QStringList)));
    connect(top_w,SIGNAL(itemselect(QStringList)),this,SLOT(load_img(QStringList)));
    connect(top_w,SIGNAL(itemopen(QString)),this,SLOT(double_clicked(QString)));
    connect(top_w,SIGNAL(/*camera-signal*/),this,SLOT(list_update()));
}
void Booklist::activateCamera()
{
    qDebug()<<"activate camera";
}
void Booklist::selected_item(QStringList name)
{
    current_files=name;
}

void Booklist::deletepressed()
{
    Xml_list=new Xfile();
    QString select_name;
    if(confirm_dialog->exec())
    {
        foreach(select_name,current_files)
        {
            Xml_list->deletexml(filepath,select_name);
        }
    }
    top_w->populatelist();
}
void Booklist::double_clicked(QString name)
{
    emit book_info(name);
}
void Booklist::markpressed(bool status)
{        Mark_mode=staus;
        top_w->setMarkMode(status);
}
void Booklist::load_img(QStringList item)
{
    if(item.length()==1)
    {
        manager=new QNetworkAccessManager(this);
        req=new QNetworkRequest(QUrl(img_src));
        manager->get(*req);
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(reply_label(QNetworkReply*)));
    }
    else
    {
        QString item_select=item.length();
        label_image=new QLabel();
        label_image->setMaximumSize(200,400);
        label_image->setWordWrap(true);
        label_image->setText(item_select);
    }
}
void Booklist::reply_label(QNetworkReply *rep)
{
    qDebug("donwload complete");
    if(rep->error())
    {return;
    }
    QByteArray pic=rep->readAll();
    pix_map=new QPixmap();
    if(!pix_map.loadFromData(pic))
        qDebug("image not loaded");
    label_image=new QLabel();
    label_image.pixmap(pix_map);
}
void Booklist::list_update()
{
    top_w->populatelist();
}
