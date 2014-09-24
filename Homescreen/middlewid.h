#ifndef MIDDLEWID_H
#define MIDDLEWID_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QString>
#include <QStringList>
#include <QHBoxLayout>
#include <QDir>
#include <QDebug>

class MiddleWid : public QWidget
{
    Q_OBJECT
    QListWidget *filelist;
    QLabel *iconViewer;
    QHBoxLayout *lay;
    QString *rootdir;
public:
    explicit MiddleWid(QString *arg,QWidget *parent = 0);
    void populateList();
    void showSearchResults(QStringList names);
    void setMarkMode(bool status);
    void setSearchModeOn(bool status);

signals:
    void sendSelectedList(QStringList names);
    void displayContent(QString name);

public slots:
    void itemSelected(QListWidgetItem *item);
    void itemOpened(QListWidgetItem *item);


};

#endif // MIDDLEWID_H
