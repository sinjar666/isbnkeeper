#include "xfile.h"

Xfile::Xfile(QObject *parent):
    QObject(parent)
{
    //filepath=path;
}
bool Xfile::newfile(QString filepath1,QString name,QString details)
{
    qDebug() << name;
    QFile file(filepath1);
//    if(!file.open(QIODevice::WriteOnly))
//    {
//        qDebug("file cannnot  be opened...");
//        return false;
//    }
    QDomDocument XmlData;
//    if(!XmlData.setContent(&file))
//    {
//        qDebug()<<"error in file";
//        return false;
//    }
//    file.close();
    QDomElement name1=XmlData.createElement(name);
    QDomElement detail=XmlData.createElement("details");
    QDomText test=XmlData.createTextNode(details);
    detail.appendChild(test);
    name1.appendChild(detail);
    QFile file1(filepath1);
    XmlData.appendChild(name1);
    if(!file1.open(QIODevice::WriteOnly))
    {
        qDebug()<<"cant write the file";
        return false;
    }
    QTextStream out(&file1);
    qDebug() << XmlData.toString();
    out<<XmlData.toString();
    file.close();
    return true;
}
bool Xfile::addbook(QString filepath1,QString name_t, QString author,
                    QString publisher, QString isbn_no,QString time1,
                    QString date1,QString summary_a,QString url_a)
{
    QFile file(filepath1);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug("file not found");
        return false;
    }
    QDomDocument XmlData;
    if(!XmlData.setContent(&file))
    {
        qDebug()<<"error in file";
        return false;
    }
    file.close();
    QDomElement name1=XmlData.firstChild().toElement();
    QDomNodeList list=name1.elementsByTagName("isbn");
    QDomNode value;int found=0;uint i=0;
    while(i<list.length())
    {
        value=list.item(i);
        QDomAttr attr=value.toElement().attributeNode("no");
        if(attr.value()==isbn_no)
        {
            found=1;
            break;
        }
        i++;
    }
    if(found!=1)
    {
        QDomElement isbn=XmlData.createElement("isbn");
        isbn.setAttribute("no",isbn_no);
        QDomElement Name=XmlData.createElement("name");
        QDomText tex=XmlData.createTextNode(name_t);
        Name.appendChild(tex);
        isbn.appendChild(Name);
        QDomElement auth=XmlData.createElement("author");
        tex=XmlData.createTextNode(author);
        auth.appendChild(tex);
        isbn.appendChild(auth);
        QDomElement pub=XmlData.createElement("publisher");
        tex=XmlData.createTextNode(publisher);
        pub.appendChild(tex);
        isbn.appendChild(pub);
        QDomElement summary=XmlData.createElement("summary");
        tex=XmlData.createTextNode(summary_a);
        summary.appendChild(tex);
        isbn.appendChild(summary);
        QDomElement img=XmlData.createElement("image");
        tex=XmlData.createTextNode(url_a);
        img.appendChild(tex);
        isbn.appendChild(img);
        QDomElement tyme=XmlData.createElement("time");
        tex=XmlData.createTextNode(time1);
        tyme.appendChild(tex);
        isbn.appendChild(tyme);
        QDomElement date_t=XmlData.createElement("date");
        tex=XmlData.createTextNode(date1);
        date_t.appendChild(tex);
        isbn.appendChild(date_t);
        name1.appendChild(isbn);
        //XmlData.appendChild(filename);
    }
    QFile file1(filepath1);
    if(!file1.open(QIODevice::WriteOnly))
    {    qDebug("file not found3");
        return false;
    }
    QTextStream out(&file1);
    out<<XmlData.toString();
    file1.close();
    return true;
}
QStringList Xfile::displayxml(QString filepath1)
{
    QFile file(filepath1);
    if(!file.open(QIODevice::ReadOnly))
    {    qDebug("file not found4");
        return QStringList();
    }
    QDomDocument XmlData;
    if(!XmlData.setContent(&file))
    {
        qDebug()<<"error in file";
        return QStringList();
    }
    file.close();
    QDomElement ele1=XmlData.firstChild().toElement();
    QStringList all_value;
    QDomNodeList list=ele1.childNodes();
    QDomNode nod1;uint i=1;
    while(i<list.length())
    {
        nod1=list.item(i);
        QString name=nod1.firstChild().toElement().childNodes().item(0).nodeValue() + " (" + nod1.toElement().attributeNode("no").value() +")";
        all_value<<name;
        i++;
    }
    return all_value;
}
bool Xfile::deletexml(QString filepath1,QString isbn_no)
{
    QFile file(filepath1);
    if(!file.open(QIODevice::ReadOnly))
    {    qDebug("file not found4");
        return false;
    }
    QDomDocument XmlData;
    if(!XmlData.setContent(&file))
    {
        qDebug()<<"error in file";
        return false;
    }
    file.close();
    QDomNode ele1=XmlData.firstChild();
    QDomNodeList list=ele1.childNodes();
    QDomNode value;uint i=0;
    QDomAttr attr;
    while(i<list.length())
    {
        value=list.item(i);
        qDebug()<<value.toElement().tagName();
        //QDomNode name2=value.firstChild();
        //qDebug()<<name2.toElement().tagName();
        //qDebug()<<name2.toElement().childNodes().item(0).nodeValue();
        attr=value.toElement().attributeNode("no");
        if(attr.value()==isbn_no)
        {
            ele1.removeChild(value);
            break;
        }
        i++;
    }
    QFile file1(filepath1);
    if(!file1.open(QIODevice::WriteOnly))
    {    qDebug("file not found3");
        return false;
    }
    QTextStream out(&file1);
    out<<XmlData.toString();
    file1.close();
    if(!XmlData.setContent(&file1))
    {
        qDebug()<<"error in file";
        return false;
    }
    value=XmlData.firstChild();

    if(!value.hasChildNodes())
    {
        file.remove(filepath1);
    }
    return true;
}
QStringList Xfile::getbookinfo(QString filepath1, QString isbn_no)
{
    QStringList list_a;
    QFile file(filepath1);
    if(!file.open(QIODevice::ReadOnly))
    {    qDebug("file not found4");
        return QStringList();
    }
    QDomDocument XmlData;
    if(!XmlData.setContent(&file))
    {
        qDebug()<<"error in file";
        return QStringList();
    }
    file.close();
    QDomNode ele1=XmlData.firstChild();
    QDomNodeList list=ele1.childNodes();
    QDomAttr attr;
    uint i=0;
    while(i<list.length())
    {
        QDomNode isbn_=list.at(i);
        attr=isbn_.toElement().attributeNode("no");
        if(attr.value()==isbn_no)
        {
            QString value=isbn_.firstChild().childNodes().item(0).nodeValue();
            list_a <<value;
            value=isbn_.firstChild().nextSibling().childNodes().item(0).nodeValue();
            list_a<<value;
            value=isbn_.firstChild().nextSibling().nextSibling().childNodes().item(0).nodeValue();
            list_a<<value;
            value=isbn_.firstChild().nextSibling().nextSibling().nextSibling().childNodes().item(0).nodeValue();
            list_a<<value;
            value=isbn_.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().childNodes().item(0).nodeValue();
            list_a<<value;
        }
        i++;
    }
    return list_a;
}
QString Xfile::getdescription(QString filepath1)
{
    QFile file(filepath1);
    if(!file.open(QIODevice::ReadOnly))
    {    qDebug("file not found4");
        return QString();
    }
    QDomDocument XmlData;
    if(!XmlData.setContent(&file))
    {
        qDebug()<<"error in file";
        return QString();
    }
    file.close();
    QDomNode ele1=XmlData.firstChild();
    QDomNodeList list=ele1.childNodes();
    QString desc=list.item(0).toElement().childNodes().item(0).nodeValue();
    return desc;
}
