#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QDebug>
#include "../errorfiledialog.h"
#include "../filecreationerr.h"
#include "../xml/xfile.h"

class NewFileDialog : public QDialog
{
    Q_OBJECT
    QGridLayout *lay;
    QLabel *name_l,*details_l,*blank_l;
    QTextEdit *details_e;
    QLineEdit *name_e;
    QPushButton *save_b;
    QString rootdir;
    ErrorFileDialog *err_d;
    FileCreationErr *ferr_d;

public:
    explicit NewFileDialog(QString arg,QWidget *parent = 0);

signals:

public slots:
    void createFile();

};

#endif // NEWFILEDIALOG_H
