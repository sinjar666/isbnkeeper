#ifndef INDEXITEM_H
#define INDEXITEM_H

#include <QString>
#include <QDebug>
#include <QDate>
#include <QDataStream>

class IndexItem
{
    QString fname,title,isbn;
    int type;

public:
    IndexItem()    {}
    IndexItem(const IndexItem &other);
    IndexItem(QString fname_a,QString isbn_a,QString title_a,int type_a);
    IndexItem &operator=(const IndexItem &o);


    QString getFname() const;
    QString getISBN() const;
    QString getTitle() const;
    int getType() const;

};
QDataStream & operator<<(QDataStream & stream,const IndexItem & item);
QDataStream & operator>>(QDataStream & in,IndexItem & item);
bool operator==(const IndexItem & a,const IndexItem & b);
#endif // INDEXITEM_H
