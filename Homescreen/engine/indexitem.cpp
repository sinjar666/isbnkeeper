#include "indexitem.h"

IndexItem::IndexItem(const IndexItem &other)    {
    *this=other;
}

IndexItem::IndexItem(QString fname_a, QString isbn_a, QString title_a,int type_a)    {
    this->fname=fname_a;
    this->isbn=isbn_a;
    this->title=title_a.replace(" ","_");
    this->type=type_a;
}


IndexItem & IndexItem::operator=(const IndexItem &o)   {
    fname=o.getFname();
    isbn=o.getISBN();
    title=o.getTitle();
    type=o.getType();
    return *this;
}

QString IndexItem::getFname() const   {
    return fname;
}

QString IndexItem::getISBN() const    {
    return isbn;
}

QString IndexItem::getTitle() const   {
    return title;
}

int IndexItem::getType() const  {
    return type;
}

QDataStream & operator<<(QDataStream & stream,const IndexItem & item)    {
    stream << item.getFname() << item.getISBN() << item.getTitle() << item.getType();
    return stream;
}

QDataStream & operator>>(QDataStream & in,IndexItem & item) {
    QString a,c;
    QString b;
    int d;
    in >> a >> b >> c >> d;
    //qDebug()<<sdate;
    item = IndexItem(a,b,c,d);
    return in;
}

bool operator ==(const IndexItem & a, const IndexItem & b)  {
    if(a.getFname() == b.getFname() && a.getISBN() == b.getISBN() && a.getTitle() == b.getTitle() && a.getType()==b.getType())
        return true;
    else return false;
}
