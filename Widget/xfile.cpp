#include "xfile.h"

Xfile::Xfile(QString path, QObject *parent):
    QObject(parent)
{
    filepath=path;
}
bool Xfile::newfile(QString filepath1,QString name,QString details)
{
    QFile file(filepath1);
    if(!file.open(QIODevice::WriteOnly))
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
    QDomElement name1=XmlData.createElement(name);
    QDomElement detail=XmlData.createElement("details");
    QDomText test=XmlData.createTextNode(details);
    detail.appendChild(test);
    name1.appendChild(detail);
    QFile file1(filepath1);
    if(!file1.open(QIODevice::WriteOnly))
    {
        qDebug()<<"cant write the file";
        return false;
    }
    QTextStream out(&file1);
    out<<XmlData.toString();
    file.close();
    return true;
}
bool Xfile::addbook(QString filepath1,QString name_t, QString author, QString publisher, QString isbn_no,QString time1,QString date1)
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
        QDomElement tyme=XmlData.createElement("time");
        tex=XmlData.createTextNode(time1);
        tyme.appendChild(tex);
        isbn.appendChild(tyme);
        QDomElement date_t=XmlData.createElement("date");
        tex=XmlData.createTextNode(date1);
        date_t.appendChild(tex);
        isbn.appendChild(auth);
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
    QDomNode nod1;uint i=0;
    while(i<list.length())
    {
        nod1=list.item(i);
        QString name=nod1.firstChild().toElement().childNodes().item(0).nodeValue();
        all_value<<name;
        i++;
    }
    return all_value;
}
bool Xfile::deletexml(QString filepath1,QString name)
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
    while(i<list.length())
    {
        value=list.item(i);
        qDebug()<<value.toElement().tagName();
        QDomNode name2=value.firstChild();
        qDebug()<<name2.toElement().tagName();
        qDebug()<<name2.toElement().childNodes().item(0).nodeValue();
        if(name2.toElement().childNodes().item(0).nodeValue()==name)
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
