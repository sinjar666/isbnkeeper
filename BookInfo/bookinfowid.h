#ifndef BOOKINFOWID_H
#define BOOKINFOWID_H

#include <QWidget>
#include <QImage>
#include <QScrollArea>
#include "toplevelwid.h"

class BookInfoWid : public QWidget
{
    Q_OBJECT
    TopLevelWid *w;
    QScrollArea *area;
    QPixmap pixmap;
    QHBoxLayout *lay;
public:
    explicit BookInfoWid(QImage cover,QString isbn_a,QString title_a,QString author_a,QString pub_a,QString summary_a,QWidget *parent = 0);

signals:

public slots:

};

#endif // BOOKINFOWID_H
