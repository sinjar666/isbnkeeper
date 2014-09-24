#ifndef BOOKLIST_H
#define BOOKLIST_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>
#include <QRegExp>
#include <QImage>
#include <QMenuBar>
#include <QProgressDialog>
#include <QErrorMessage>
#include "bottombar2.h"
#include "topmid.h"
#include "../Homescreen/delconfirmdialog.h"
#include "../Homescreen/engine/engine.h"
#include "../xml/xfile.h"
#include "../stillcam.h"
#include "../xml/isbn.h"
#include "../xml/xfile.h"
#include "../BookInfo/bookinfowid.h"
#include "descdialog.h"

class Booklist : public QWidget
{
    Q_OBJECT
    QVBoxLayout *layout_w;
    BottomBar2 *bottom_w;
    Topmid *top_w;
    DelConfirmDialog *confirm_dialog;
    QStringList current_files;
    Xfile *Xml_list;
    QString filepath,Path;
    bool Mark_mode;
    QNetworkAccessManager *manager;
    QNetworkRequest *req;
    //QLabel *label_image;
    QPixmap *pix_map;
    QMenuBar *menu;

    Engine *engine;
    bool image_failed;

    QImage cover;
    QString isbn_no;
    QStringList data;
    StillCam *camera;
    Isbn *fetcher;
    QProgressDialog *loading;
    Xfile *xml_engine;
    BookInfoWid *book_info;
    QErrorMessage *err_d;
public:
    explicit Booklist(Engine *engine_a,QString path, QWidget *parent = 0);
signals:
    //void book_info(QString isbn);
    void startCamera(QString path);

public slots:
    //void load_img(QStringList item);
    void activateCamera();
    void deletepressed();
    void markpressed(bool status);
    //void reply_label(QNetworkReply *rep);
    void double_clicked(QString name);
    void selected_item(QStringList name);
    void list_update();

    void fetchInfo(QString isbn);
    void setImageFailed();
    void setImageFailed2();
    void displayInfoAfterLoad();
    void cancelDisplayInfo();
    void displayInfoFromFile();
    void cancelFetchImage();
    void displaydescription(QAction *act);
};

#endif // BOOKLIST_H
