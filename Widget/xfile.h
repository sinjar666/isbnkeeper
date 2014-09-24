#ifndef XFILE_H
#define XFILE_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include <QDomElement>
#include <QDomNodeList>
#include <QStringList>
#include <QDomText>

class Xfile : public QObject
{
    Q_OBJECT
    QString filepath;
public:
    explicit Xfile(QString path,QObject *parent = 0);
    bool newfile(QString filepath1,QString name,QString details);
    bool addbook(QString filepath1, QString name_t, QString author, QString publisher, QString isbn_no,QString time1,QString date1);
    QStringList displayxml(QString filepath1);
    bool deletexml(QString filepath1,QString name);
signals:

public slots:

};

#endif // XFILE_H
