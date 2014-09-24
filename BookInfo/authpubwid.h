#ifndef AUTHPUBWID_H
#define AUTHPUBWID_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class AuthPubWid : public QWidget
{
    Q_OBJECT
    QGridLayout *lay;
    QLabel *author_l,*author,*pub_l,*pub,*title,*title_l,*isbn,*isbn_l;
public:
    explicit AuthPubWid(QString title_a,QString author_a,QString pub_a,QString isbn_a,QWidget *parent = 0);

signals:

public slots:

};

#endif // AUTHPUBWID_H
