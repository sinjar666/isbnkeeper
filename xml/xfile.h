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
#include <QDomAttr>
#include <QDomText>
#include <QDomNode>

class Xfile : public QObject
{
    Q_OBJECT
public:
    explicit Xfile(QObject *parent = 0);
    bool newfile(QString filepath1,QString name,QString details);
    bool addbook(QString filepath1, QString name_t, QString author, QString publisher,
                 QString isbn_no,QString time1,QString date1,QString summary, QString url_a);
    QStringList displayxml(QString filepath1);
    bool deletexml(QString filepath1,QString isbn_no);
    QStringList getbookinfo(QString filepath1,QString isbn_no);
    QString getdescription(QString filepath1);
signals:

public slots:

};

#endif // XFILE_H
