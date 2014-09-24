#ifndef FILECREATIONERR_H
#define FILECREATIONERR_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class FileCreationErr : public QDialog
{
    Q_OBJECT
    QHBoxLayout *lay;
    QPushButton *okButton;
    QLabel *msg;
public:
    explicit FileCreationErr(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // FILECREATIONERR_H
