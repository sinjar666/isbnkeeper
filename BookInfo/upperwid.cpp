#include "upperwid.h"

UpperWid::UpperWid(QPixmap pixmap, QString isbn_a, QString title_a,
                   QString author_a, QString pub_a, QWidget *parent):
    QWidget(parent)
{
    w1 = new QLabel();
    w1->setMaximumSize(200,250);
    w1->setPixmap(pixmap);
    w2 = new AuthPubWid(title_a,author_a,pub_a,isbn_a);
    lay = new QHBoxLayout(this);
    lay->addWidget(w1);
    lay->addWidget(w2);
}
