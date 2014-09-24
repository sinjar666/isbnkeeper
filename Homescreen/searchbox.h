#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

class SearchBox : public QWidget
{
    Q_OBJECT
    QHBoxLayout *lay;
    QLineEdit *editor;
    QLabel *icon;
public:
    explicit SearchBox(QWidget *parent = 0);
    
signals:
    void keyPressed(QString text);
    
public slots:
    void sendText(QString text);
    
};

#endif // SEARCHBOX_H
