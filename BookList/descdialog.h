#ifndef DESCDIALOG_H
#define DESCDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QHBoxLayout>
#include "../xml/xfile.h"
#include "booklist.h"

class Descdialog : public QDialog
{
    Q_OBJECT
    QTextEdit *desc_text;
    Xfile *data;
    QHBoxLayout *lay;
    QString filepath;
public:
    explicit Descdialog(QString path,QWidget *parent = 0);

signals:

public slots:

};

#endif // DESCDIALOG_H
