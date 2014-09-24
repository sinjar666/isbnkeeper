#include "homescreen.h"

HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent)
{

    setWindowTitle(tr("ISBN Keeper -- HOME"));
    rootdir = new QString();
    getRootpath();
    qDebug() << *rootdir;
    //rootdir=new QString("/home/user/MyDocs/");
    engine=new Engine(*rootdir);
    //engine->setPath(*rootdir);
    engine->loadIndex();
    searchMode=false;
    currentFiles << "others.xml";
    top = new SearchBar(engine);
    qDebug() << "here";
    middle = new MiddleWid(rootdir);
    bottom = new BottomBar(rootdir);
    lay=new QVBoxLayout(this);
    lay->addWidget(top);
    lay->addWidget(middle);
    lay->addWidget(bottom);
    menu_bar = new QMenuBar(this);
    //menu_bar->addAction(QString("Settings"));
    menu_bar->addAction(QString("About"));
    confirm_dialog = new DelConfirmDialog(this);
    about_d = new AboutDialog(this);
    connect(bottom,SIGNAL(activateCamera()),this,SLOT(activateCamera()));
    connect(top,SIGNAL(sendToggle(bool)),this,SLOT(toggleSelectionMode(bool)));
    connect(middle,SIGNAL(sendSelectedList(QStringList)),this,SLOT(changeSelectedList(QStringList)));
    connect(top,SIGNAL(enterSearchMode(bool)),this,SLOT(setSearchMode(bool)));
    connect(top,SIGNAL(sendSearchText(QString)),this,SLOT(performSearch(QString)));
    connect(top,SIGNAL(openOthers()),this,SLOT(openOthers()));
    connect(middle,SIGNAL(displayContent(QString)),this,SLOT(openFile(QString)));
    connect(bottom,SIGNAL(requestDelete()),this,SLOT(performDelete()));
    connect(bottom,SIGNAL(requestRefresh()),this,SLOT(sendRefresh()));
    connect(menu_bar,SIGNAL(triggered(QAction*)),this,SLOT(menuTriggered(QAction*)));
    err_d = new QErrorMessage(this);
    //setFocusProxy(top);
}

void HomeScreen::getRootpath()  {
    QFile fil("/home/user/.isbnkeeper-config");
    if(!fil.open(QIODevice::ReadOnly))  {
        qDebug() << "No Config";
        bool status;

            ConfigDialog *dialog = new ConfigDialog(this);
            status=dialog->exec();
            if(!status) {
                fil.remove();
                FatalMessage *w = new FatalMessage(this);
                w->exec();
                w->deleteLater();
                exit(1);
            }

        fil.open(QIODevice::ReadOnly);
    }
    QTextStream stream(&fil);
    stream >> *rootdir;
    fil.close();
    fil.setFileName(*rootdir+"others.xml");
    if(!fil.open(QIODevice::ReadOnly))  {
        Xfile *obj = new Xfile();
        bool flag=obj->newfile(*rootdir+"others.xml",tr("others"),QString("Contains miscellaneous books"));
        if(!flag)   {
            FatalNotAvail *w = new FatalNotAvail(*rootdir,this);
            w->exec();
            w->deleteLater();
            exit(1);
        }
        delete(obj);
    }
    fil.close();
}

void HomeScreen::toggleSelectionMode(bool checked)  {
    markMode = checked;
    middle->setMarkMode(checked);
    if(!searchMode)
        top->toggleOthers(!checked);
    if(searchMode)
        top->giveFocus();
}

void HomeScreen::setSearchMode(bool status) {
    if(status != searchMode && status==true)    {
        currentFiles.clear();
        top->checkMark(false);
        toggleSelectionMode(false);
    }
    if(status!= searchMode && status == false)  {
        currentFiles = QStringList(tr("others.xml"));
        top->checkMark(false);
        toggleSelectionMode(false);
    }
    searchMode=status;
    middle->setSearchModeOn(status);
    top->toggleOthers(!status);
    bottom->enableCamera(!status);
    if(!status && currentFiles.length()==0)
        currentFiles << "others.xml";
}

void HomeScreen::performSearch(QString key) {
    QList<IndexItem> results;
    resultNames.clear();
    results=engine->getEntry(key);
    results.append(engine->getSubstringMatch(key));
    IndexItem result;
    foreach(result,results) {
        resultNames << "["+result.getFname()+ "] "+ result.getTitle() + "(" + result.getISBN() + ")";
    }
    //resultNames.removeDuplicates();
    middle->showSearchResults(resultNames);
}

void HomeScreen::changeSelectedList(QStringList newFiles)    {
    currentFiles = newFiles;
    if(!searchMode && currentFiles.length()==0)
        currentFiles << "others.xml";
    qDebug() << "Currently selected.." << currentFiles;
}

void HomeScreen::activateCamera()   {
    if(!searchMode) {
    if(currentFiles.length()==1)    {
        //emit startCamera(*rootdir+currentFiles.at(0));
        Path = *rootdir+currentFiles.at(0);
        qDebug() << "start camera." + currentFiles.at(0);
        camera = new StillCam(this);
        //camera->setAttribute(setOrientation(ScreenOrientationLockLandscape));
        camera->setAttribute(Qt::WA_Maemo5StackedWindow);
        camera->setAttribute(Qt::WA_DeleteOnClose);
        camera->setWindowFlags(camera->windowFlags() | Qt::Window);
        connect(camera,SIGNAL(gotISBN(QString)),this,SLOT(fetchInfo(QString)));
        camera->show();
    }
    else    {
        qDebug() << "Multiple files selected.";
        err_d->showMessage("Choose a single file before pressing Camera!");
    }
}
}

void HomeScreen::fetchInfo(QString isbn) {
    camera->close();
    delete(camera);
    image_failed=false;
    isbn_no = isbn;
    fetcher = new Isbn();
    fetcher->openwebpage(isbn);
    connect(fetcher,SIGNAL(img_error()),this,SLOT(setImageFailed()));
    connect(fetcher,SIGNAL(load_complete()),this,SLOT(displayInfoAfterLoad()));
    loading = new QProgressDialog(tr("ISBN:: ")+isbn_no+tr("\n")+tr("Retrieving data from server."),tr("Stop"),0,0,this);
    loading->setAutoClose(true);
    loading->setWindowTitle(tr("Please wait"));
    connect(loading,SIGNAL(canceled()),this,SLOT(cancelDisplayInfo()));
    loading->show();
}

void HomeScreen::cancelDisplayInfo()    {
    fetcher->deleteLater();
}

void HomeScreen::setImageFailed()    {
    image_failed = true;
}

void HomeScreen::displayInfoAfterLoad() {

    if(fetcher->getError() == Isbn::ISBN_INVALID)   {
        qDebug("in handler of invaliod");
        fetcher->deleteLater();
        loading->reset();
        err_d->showMessage(tr("The returned ISBN is invalid!!"));
        return;
    }
    if(fetcher->getError() == Isbn::ISBN_NOTFOUND) {
        qDebug("in handler of not found");
        fetcher->deleteLater();
        loading->reset();
        err_d->showMessage(tr("The requested book was not found in the online database. Must be a very rare book."));
        return;
    }
    QString title,author,publisher,summary,img_url;
    title=fetcher->getname();
    author=fetcher->getauthor();
    publisher=fetcher->getpublisher();
    summary=fetcher->getreview();
    img_url=fetcher->getUrl();
    qDebug() << "fetch done..";
    fetcher->deleteLater();
    if(title==""||author==""||publisher==""||summary==""||img_url=="")  {
        loading->reset();
        err_d->showMessage(tr("Unable to fetch the content. Check internet connection and retry..."));
        return;
    }
    xml_engine = new Xfile();
    bool rval=xml_engine->addbook(Path,title,author,publisher,isbn_no,
                        QTime::currentTime().toString(),QDate::currentDate().toString(),summary,img_url);
    if(!rval)   {
        loading->reset();
        err_d->showMessage(tr("Unable to save to file. Either file is corrupt or disk write-protected."));
        return;
    }
    QRegExp exp("\\/{1,1}\\w+\\.{1,1}");
    int pos=Path.indexOf(exp,0);
    QString fname = Path.mid(pos+1,Path.length()-pos-1);
    qDebug() << "index:fname=" << fname;
    IndexItem item(fname,isbn_no,title,1);
    engine->addEntry(title,item);
    item=IndexItem(fname,isbn_no,title,2);
    engine->addEntry(author,item);
    item=IndexItem(fname,isbn_no,title,3);
    engine->addEntry(publisher,item);
    engine->saveIndex();
    QImage cover;
    if(!image_failed)
        cover = QImage("/home/user/isbn-book.jpg");
    else
        cover=QImage(":/leather-book-preview.png"); //default image

    //loading->close();
    loading->reset();
    xml_engine->deleteLater();
    //delete(loading);
    qDebug() << "here.";
    book_info = new BookInfoWid(cover,isbn_no,title,author,publisher,summary,this);
    //book_info->setAttribute(setOrientation(ScreenOrientationLockLandscape));
    book_info->setAttribute(Qt::WA_Maemo5StackedWindow);
    book_info->setWindowFlags(book_info->windowFlags()|Qt::Window);
    book_info->show();
}

void HomeScreen::openFile(QString fname)    {
    if(!searchMode) {
    qDebug() << "Opening this file:"<<*rootdir+fname;
    //emit requestOpenFile(*rootdir+fname);
    Path=*rootdir+fname;

    book_list = new Booklist(engine,Path,this);
    //book_list->setAttribute(setOrientation(ScreenOrientationLockLandscape));
    book_list->setAttribute(Qt::WA_Maemo5StackedWindow);
    book_list->setWindowFlags(book_list->windowFlags() | Qt::Window);
    book_list->show();
    }
    else    {
        QString filename,isbn;
        QRegExp exp("\\({1,1}[0-9]{13,13}\\){1,1}$");
        int pos=fname.indexOf(exp,0);
        QString match = fname.mid(pos+1,13);
        isbn=match; //isbn
        qDebug() << "open search result:" << isbn;
        //exp = QRegExp("\\[{1,1}\\w+\\]{1,1}");
        pos=fname.indexOf("]")-1;
        match=fname.mid(1,pos);
        filename=match;
        qDebug() << filename;
        //emit requestShowBook(*rootdir+filename,isbn);
        Path=*rootdir+filename;
        xml_engine = new Xfile();
        isbn_no=isbn;
        data=xml_engine->getbookinfo(Path,isbn);
        delete(xml_engine);
        fetcher = new Isbn();
        image_failed=false;
        connect(fetcher,SIGNAL(img_error()),this,SLOT(setImageFailed2()));
        connect(fetcher,SIGNAL(load_complete()),this,SLOT(displayInfoFromFile()));
        fetcher->getimage(data.at(4));
//        loading = new LoaderWidget(this);
//        //loading->setAttribute(setOrientation(ScreenOrientationLockLandscape));
//        loading->setAttribute(Qt::WA_DeleteOnClose);
//        loading->setAttribute(Qt::WA_Maemo5StackedWindow);
//        loading->setWindowFlags(loading->windowFlags()|Qt::Window);
//        loading->show();
        loading = new QProgressDialog("Fetching cover image...","Cancel",0,0,this);
        loading->setAutoClose(true);
        loading->setWindowTitle("Please wait");
        connect(loading,SIGNAL(canceled()),this,SLOT(cancelFetchImage()));
        loading->show();
    }
}

void HomeScreen::cancelFetchImage() {
    fetcher->deleteLater();
    image_failed=true;
    displayInfoFromFile();
}

void HomeScreen::setImageFailed2()    {
    fetcher->deleteLater();
    image_failed=true;
    //displayInfoFromFile();
}

void HomeScreen::displayInfoFromFile()    {
    //loading->close();
    //delete(loading);
    if(!image_failed) fetcher->deleteLater();
    if(!image_failed)
        cover=QImage("/home/user/isbn-book.jpg");
    else
        cover=QImage(":/leather-book-preview.png"); //Default book image

    loading->reset();
    qDebug()<< data ;
    book_info = new BookInfoWid(cover,isbn_no,data.at(0),data.at(1),data.at(2),data.at(3),this);
    //book_info->setAttribute(setOrientation(ScreenOrientationLockLandscape));
    book_info->setAttribute(Qt::WA_Maemo5StackedWindow);
    book_info->setWindowFlags(book_info->windowFlags() | Qt::Window);
    book_info->show();

}
void HomeScreen::openOthers()   {
    qDebug() << "Opening this file:others";
    //emit requestOpenFile(*rootdir+QString("others.xml"));
    openFile(tr("others.xml"));
}

void HomeScreen::performDelete()    {
    if(currentFiles.length()==0)    {
        err_d->showMessage(tr("Please select a file!!"));
    }
    else    {
    if(confirm_dialog->exec())  {
    QString name;
    foreach(name,currentFiles)  {
        //Delete that particular book from tumul class
        //Generate keywords from name
        //For each keyword delete entry from index

        if(searchMode)  {
            QString fname,isbn;
            QRegExp exp("\\({1,1}[0-9]{13,13}\\){1,1}$");
            int pos=name.indexOf(exp,0);
            QString match = name.mid(pos+1,13);
            isbn=match; //isbn
            //exp = QRegExp("\\[\\w+\\]");
            pos=name.indexOf("]")-1;
            match=name.mid(1,pos);
            fname=match;
            Xfile *xmleng = new Xfile();
            bool rval=xmleng->deletexml(*rootdir+fname,isbn);
            if(!rval)   {
                err_d->showMessage(tr("Delete failed! Either file corrupt or disk write-protected."));
                xmleng->deleteLater();
                return;
            }
            engine->removeByISBN(isbn);
            delete(xmleng);
        }
        else    {
            if(name=="others.xml")  {
                err_d->showMessage(tr("You cannot delete the default file others.xml"));
            }
            else    {
                QFile fil(*rootdir+name);
                bool rval=fil.remove();
                if(!rval)   {
                    err_d->showMessage(tr("Delete failed! Disk write protected or unavailable."));
                    return;
                }
                engine->removeByName(name);
            }
        }
        resultNames.removeAll(name);
    }
    if(searchMode)
        middle->showSearchResults(resultNames);
    else    {
        middle->populateList();
        currentFiles = QStringList("others.xml");
    }

    engine->saveIndex();
}
}
    if(searchMode) top->giveFocus();
}

void HomeScreen::sendRefresh()  {
    if(!searchMode)
        middle->populateList();
    top->giveFocus();
}

void HomeScreen::menuTriggered(QAction *action) {

    if(action->text() == "About")  {
        about_d->show();
    }
}
