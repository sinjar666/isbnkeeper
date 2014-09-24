#ifndef ISBN_H
#define ISBN_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QWebFrame>
#include <QWebPage>
#include <QWebElementCollection>
#include <QWebElement>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QWebView>


class Isbn : public QObject{
    Q_OBJECT
    QString filepath;
    QWebPage *page;
    QNetworkAccessManager *manager;
    QNetworkRequest *req;
    QString name,publisher,author,review,img_url;
public:

    typedef enum    {
        ISBN_NO_ERROR = 0,
        ISBN_INVALID = 1,
        ISBN_NOTFOUND = 2
    } ErrorCodes;

    explicit Isbn(QObject *parent = 0);
    ~Isbn();
    void openwebpage(QString no);
    QString getname();
    QString getauthor();
    QString getpublisher();
    QString getreview();
    QString getUrl();
    void getimage(QString url);

    void setinaccessible();
    ErrorCodes getError();

private:
    ErrorCodes err;
signals:
    void img_error();
    void load_complete();
public slots:
    void result();
    void reply(QNetworkReply *rep);
};

#endif // ISBN_H
