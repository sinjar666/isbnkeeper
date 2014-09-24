#ifndef FATALNOTAVAIL_H
#define FATALNOTAVAIL_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QPushButton>

class FatalNotAvail : public QDialog
{
    Q_OBJECT
    QLabel *msg;
    QPushButton *button,*reset;
    QHBoxLayout *lay;
public:
    explicit FatalNotAvail(QString path,QWidget *parent = 0);
    
signals:
    
public slots:
    void resetApp();
    
};

#endif // FATALNOTAVAIL_H
