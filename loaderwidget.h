#ifndef LOADERWIDGET_H
#define LOADERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class LoaderWidget : public QWidget
{
    Q_OBJECT
    QLabel *label;
    QHBoxLayout *lay;
public:
    explicit LoaderWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // LOADERWIDGET_H
