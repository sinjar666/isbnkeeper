#include "isbn.h"

Isbn::Isbn(QObject *parent) :
    QObject(parent)
{
    //filepath=path;
    err = ISBN_NO_ERROR;
}

Isbn::~Isbn()   {

}

void Isbn::openwebpage(QString no)
{
    qDebug("working");
    QString web="http://isbn.net.in/";
    web.append(no);
    qDebug()<<web;
    page=new QWebPage();
    page->mainFrame()->load(QUrl(web));
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(result()));
}
void Isbn::result()
{
    qDebug("page load is complete");
    if(page->findText("Not Found"))
    {   qDebug("isbn not 13 digit");
        err=ISBN_INVALID;
        emit load_complete();
        return;
    }
    if(page->findText("Cannot find any details about this book."))
    {   qDebug("wrong isbn");
        err=ISBN_NOTFOUND;
        emit load_complete();
        return;
    }
    err=ISBN_NO_ERROR;
    QString find_div;
    QWebElementCollection collection;
    collection=page->mainFrame()->findAllElements("table");
    name=collection.at(0).attribute("class");
    //qDebug()<<name;

    QWebElement tbody=collection.at(0).firstChild();
    name=tbody.firstChild().firstChild().nextSibling().toPlainText();
    author=tbody.firstChild().nextSibling().firstChild().nextSibling().toPlainText();
    publisher=tbody.firstChild().nextSibling().nextSibling().firstChild().nextSibling().toPlainText();
    qDebug()<<name;
    qDebug()<<author;
    qDebug()<<publisher;

    collection=page->mainFrame()->findAllElements("div");
    foreach(tbody,collection)
    {
        if(tbody.hasAttribute("id"))
        {
            find_div=tbody.attribute("id");
            if(find_div=="editorial_review")
            {   //qDebug("here");
                review=tbody.toPlainText();
                //qDebug()<<review;
                break;
            }
        }
    }
    review.truncate(200);
    review=review.append("...");
    QString img_src;
    collection=page->mainFrame()->findAllElements("a");
    img_src=collection.at(0).firstChild().attribute("src");
    img_url=img_src;
    getimage(img_src);
}

QString Isbn::getUrl() {
    return img_url;
}

void Isbn::getimage(QString url)
{
    manager=new QNetworkAccessManager(this);
    req=new QNetworkRequest(QUrl(url));
    manager->get(*req);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(reply(QNetworkReply*)));
}
void Isbn::reply(QNetworkReply *rep)
{
    qDebug("donwload complete");
    if(rep->error())
    {
        emit img_error();
        emit load_complete();
        return;
    }
    QByteArray pic=rep->readAll();
    QFile file("/home/user/isbn-book.jpg");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(pic);
    file.close();
    //page->deleteLater();
    //if(req) delete(req);
    emit load_complete();
}
QString Isbn::getname()
{
    return name;
}
QString Isbn::getauthor()
{
    return author;
}
QString Isbn::getpublisher()
{
    return publisher;
}
QString Isbn::getreview()
{
    return review;
}
void Isbn::setinaccessible()    {
    manager->setNetworkAccessible(QNetworkAccessManager::NotAccessible);
}

Isbn::ErrorCodes Isbn::getError()   {
    return err;
}

