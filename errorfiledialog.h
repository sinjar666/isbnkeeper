#ifndef ERRORFILEDIALOG_H
#define ERRORFILEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class ErrorFileDialog : public QDialog
{
    Q_OBJECT
    QPushButton *okButton;
    QLabel *msg;
    QHBoxLayout *lay;
public:
    explicit ErrorFileDialog(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // ERRORFILEDIALOG_H
