#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QScrollArea>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>

class AboutDialog : public QDialog
{
    Q_OBJECT
    QHBoxLayout *lay;
    QLabel *view;
    QScrollArea *area;
public:
    explicit AboutDialog(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // ABOUTDIALOG_H
