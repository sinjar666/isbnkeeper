#include "authpubwid.h"

AuthPubWid::AuthPubWid(QString title_a,QString author_a, QString pub_a,QString isbn_a, QWidget *parent) :
    QWidget(parent)
{
    author = new QLabel("<font color='yellow'>Author:</font>");
    author_l = new QLabel(author_a);
    author_l->setWordWrap(true);
    pub = new QLabel("<font color='green'>Publisher:</font>");
    pub_l = new QLabel(pub_a);
    pub_l->setWordWrap(true);
    title= new QLabel("<font color='cyan'>Title:</font>");
    title_l = new QLabel(title_a.toUpper());
    isbn = new QLabel("<font color='orange'>ISBN:</font>");
    isbn_l = new QLabel(isbn_a);
    lay = new QGridLayout(this);
    lay->addWidget(title,0,0);
    lay->addWidget(title_l,0,1);
    lay->addWidget(author,1,0);
    lay->addWidget(author_l,1,1);
    lay->addWidget(pub,2,0);
    lay->addWidget(pub_l,2,1);
    lay->addWidget(isbn,3,0);
    lay->addWidget(isbn_l,3,1);
}
