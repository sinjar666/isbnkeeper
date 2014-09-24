#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFile>
#include <QLineEdit>
#include <QTextStream>

class ConfigDialog : public QDialog
{
    Q_OBJECT
    QLineEdit *path_e;
    QPushButton *browse_b;
    QHBoxLayout *lay;
    QFile *fil;
public:
    explicit ConfigDialog(QWidget *parent = 0);
    
signals:
    
public slots:
    void chooseFile();
    
};

#endif // CONFIGDIALOG_H
