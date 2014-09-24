#include "bookinfowid.h"

BookInfoWid::BookInfoWid(QImage cover, QString isbn_a, QString title_a, QString author_a, QString pub_a, QString summary_a, QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("ISBN Keeper -- ")+title_a);
    pixmap=QPixmap::fromImage(cover.scaled(200,250));
    w = new TopLevelWid(pixmap,isbn_a,title_a,author_a,pub_a,summary_a);
    area = new QScrollArea();
    area->setWidget(w);
    lay = new QHBoxLayout(this);
    lay->addWidget(area);
}
