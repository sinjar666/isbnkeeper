#ifndef BOOKLIST_H
#define BOOKLIST_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include "bottombar.h"
#include "topmid.h"
#include "delconfirmdialog.h"
#include "xfile.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>

class Booklist : public QWidget
{
    Q_OBJECT
    QVBoxLayout *layout_w;
    BottomBar *bottom_w;
    Topmid *top_w;
    DelConfirmDialog *confirm_dialog;
    QStringList current_files;
    Xfile *Xml_list;
    QString filepath;
    bool Mark_mode;
    QNetworkAccessManager *manager;
    QNetworkRequest *req;
    QLabel *label_image;
    QPixmap *pix_map;
public:
    explicit Booklist(QString path,QWidget *parent = 0);
    void load_img(QStringList item);
signals:
    void book_info(QString name);

public slots:
    void activateCamera();
    void deletepressed();
    void markpressed(bool status);
    void reply_label(QNetworkReply *rep);
    void double_clicked(QString name);
    void selected_item(QStringList name);
    void list_update();
};

#endif // BOOKLIST_H
