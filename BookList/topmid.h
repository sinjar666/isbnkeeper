#ifndef TOPMID_H
#define TOPMID_H

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QStringList>
#include <QDir>
#include "../xml/xfile.h"

class Topmid : public QWidget
{
    Q_OBJECT
    QListWidget *list_w;
    QHBoxLayout *lay_h;
    QLabel *lab_w;
    Xfile *Xml_top;
    QString filepath;
public:
    explicit Topmid(QString path,QWidget *parent = 0);
    void populatelist();
    void setMarkMode(bool status);
signals:
    void itemselect(QStringList names);
    void itemopen(QString name);

public slots:
        void selecteditem(QListWidgetItem *item);
        void openeditem(QListWidgetItem *item);
        //void loadimg(QListWidgetItem *item);
};

#endif // TOPMID_H
