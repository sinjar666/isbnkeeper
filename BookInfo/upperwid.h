#ifndef UPPERWID_H
#define UPPERWID_H

#include <QWidget>
#include <QHBoxLayout>
#include "authpubwid.h"

class UpperWid : public QWidget
{
    Q_OBJECT
    QLabel *w1;
    AuthPubWid *w2;
    QHBoxLayout *lay;
public:
    explicit UpperWid(QPixmap pixmap,QString isbn_a,QString title_a,QString author_a,QString pub_a,QWidget *parent = 0);

signals:

public slots:

};

#endif // UPPERWID_H
