#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
//#include "engine/engine.h"

class BottomBar : public QWidget
{
    Q_OBJECT
    QPushButton *camera_b,*mark_b,*delete_b;
    QHBoxLayout *lay;
public:
    explicit BottomBar(QWidget *parent = 0);
signals:
    void activateCamera();
    void requestDelete();
    //void requestRefresh();
    void sendToggle(bool checked);

public slots:
    void cameraPressed();
    void deletePressed();
    void markToggled(bool checked);
};

#endif // BOTTOMBAR_H
