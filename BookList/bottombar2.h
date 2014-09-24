#ifndef BOTTOMBAR2_H
#define BOTTOMBAR2_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "../Homescreen/engine/engine.h"

class BottomBar2 : public QWidget
{
    Q_OBJECT
    QPushButton *camera_b,*mark_b,*delete_b;
    QHBoxLayout *lay;
public:
    explicit BottomBar2(QWidget *parent = 0);
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

#endif // BOTTOMBAR2_H
