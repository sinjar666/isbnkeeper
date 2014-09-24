#ifndef READEAN13_H
#define READEAN13_H

#include <QThread>
#include <QImage>
#include <QPixmap>
#include <QByteArray>
#include <QString>
#include <QMap>
#include <QSet>
#include <QDebug>
#include <QFile>


class ReadEAN13 : public QThread
{
    Q_OBJECT
    QMap<uchar,uchar> code1A,code1B,code2;
    QMap<QString,uchar> patt;
public:
    explicit ReadEAN13(QString arg,QObject *parent = 0);
    QString getResult();
    void run();


private:
    void initialize();
    bool readBit();
    uchar readBlock();
    void getLimits();
    bool read2to7();
    bool read8to13();
    bool check();
    void prepare();


    QImage src,binary,tmp;

    QString *imgpath;
    uint left,right,curr_pos,r,offset;
    QString result,leftpatt;
    uint sum_odd, sum_even,last_digit,d1;


signals:

public slots:

};

#endif // READEAN13_H
