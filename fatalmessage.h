#ifndef FATALMESSAGE_H
#define FATALMESSAGE_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class FatalMessage : public QDialog
{
    Q_OBJECT
    QLabel *msg;
    QPushButton *okButton;
    QHBoxLayout *lay;
public:
    explicit FatalMessage(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // FATALMESSAGE_H
