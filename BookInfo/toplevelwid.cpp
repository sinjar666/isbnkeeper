#include "toplevelwid.h"

TopLevelWid::TopLevelWid(QPixmap pixmap, QString isbn_a, QString title_a, QString author_a, QString pub_a,QString summary_a, QWidget *parent) :
    QWidget(parent)
{
    upper= new UpperWid(pixmap,isbn_a,title_a,author_a,pub_a);
    summary_l = new QLabel();
    summary_l->setWordWrap(true);
    summary_l->setText(QString("<h3> <font color='red'> Summary: </font> </h3>")+summary_a);
    lay = new QVBoxLayout(this);
    lay->addWidget(upper);
    lay->addWidget(summary_l);
}
