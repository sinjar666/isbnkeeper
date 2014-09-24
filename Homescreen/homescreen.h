#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QRegExp>
#include <QImage>
#include <QProgressDialog>
#include <QErrorMessage>
#include "searchbar.h"
#include "middlewid.h"
#include "bottombar.h"
#include "delconfirmdialog.h"
#include "configdialog.h"
#include "engine/engine.h"
#include "../xml/xfile.h"
#include "../stillcam.h"
#include "../xml/isbn.h"
#include "../xml/xfile.h"
#include "../BookInfo/bookinfowid.h"
#include "../BookList/booklist.h"
#include "aboutdialog.h"
#include "../fatalmessage.h"
#include "../fatalnotavail.h"

class HomeScreen : public QWidget
{
    Q_OBJECT
    bool searchMode,markMode;
    SearchBar *top;
    MiddleWid *middle;
    BottomBar *bottom;
    QVBoxLayout *lay;
    Engine *engine;
    QString *rootdir,isbn_no,Path;
    QStringList currentFiles;
    QStringList resultNames,data;
    DelConfirmDialog *confirm_dialog;
    bool image_failed;

    QMenuBar *menu_bar;
    StillCam *camera;
    Isbn *fetcher;
    QProgressDialog *loading;
    Xfile *xml_engine;
    BookInfoWid *book_info;
    Booklist *book_list;

    QImage cover;
    QErrorMessage *err_d;
    AboutDialog *about_d;

public:
    explicit HomeScreen(QWidget *parent=0);
    void getRootpath();

signals:
    void startCamera(QString path);
    void requestOpenFile(QString path);
    void requestShowBook(QString path,QString isbn);

public slots:
    void activateCamera();
    void toggleSelectionMode(bool checked);
    void changeSelectedList(QStringList newFiles);
    void setSearchMode(bool status);
    void performSearch(QString key);
    void performDelete();
    void openFile(QString fname);
    void openOthers();
    void sendRefresh();

    void fetchInfo(QString isbn);
    void displayInfoAfterLoad();
    void cancelDisplayInfo();
    void setImageFailed();
    void setImageFailed2();
    void displayInfoFromFile();
    void cancelFetchImage();

    void menuTriggered(QAction *action);

};

#endif // HOMESCREEN_H
