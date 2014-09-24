#ifndef TOPLEVELWID_H
#define TOPLEVELWID_H

#include <QWidget>
#include "upperwid.h"

class TopLevelWid : public QWidget
{
    Q_OBJECT
    UpperWid *upper;
    QLabel *summary_l;
    QVBoxLayout *lay;
public:
    explicit TopLevelWid(QPixmap pixmap,QString isbn_a,QString title_a,QString author_a,QString pub_a,QString summary_a,QWidget *parent = 0);

signals:

public slots:

};

#endif // TOPLEVELWID_H
