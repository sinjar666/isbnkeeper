#ifndef DELCONFIRMDIALOG_H
#define DELCONFIRMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class DelConfirmDialog : public QDialog
{
    Q_OBJECT
    QLabel *confirm_l;
    QPushButton *yes,*no;
    QGridLayout *lay;
public:
    explicit DelConfirmDialog(QWidget *parent = 0);

signals:

public slots:

};

#endif // DELCONFIRMDIALOG_H
