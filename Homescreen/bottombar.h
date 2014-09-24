#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "newfiledialog.h"

class BottomBar : public QWidget
{
    Q_OBJECT
    QPushButton *camera_b,*new_b,*delete_b;
    QHBoxLayout *lay;
    NewFileDialog *dialog;
    QString *rootdir;
public:
    explicit BottomBar(QString *arg,QWidget *parent = 0);
    void enableCamera(bool status);
signals:
    void activateCamera();
    void requestDelete();
    void requestRefresh();

public slots:
    void cameraPressed();
    void showNewFileDialog();
    void deletePressed();
};

#endif // BOTTOMBAR_H
