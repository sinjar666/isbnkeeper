#include "newfiledialog.h"

NewFileDialog::NewFileDialog(QString arg,QWidget *parent) :
    QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose,true);
    rootdir = arg;
    name_l = new QLabel("Name:");
    details_l = new QLabel("Details:");
    name_e = new QLineEdit();
    details_e = new QTextEdit();
    save_b = new QPushButton("Save");
    blank_l = new QLabel();
    lay = new QGridLayout(this);
    lay->addWidget(name_l,0,0);
    lay->addWidget(name_e,0,1);
    lay->addWidget(details_l,1,0);
    lay->addWidget(details_e,1,1);
    lay->addWidget(save_b,1,2);
    lay->addItem(new QSpacerItem(lay->columnMinimumWidth(0),lay->rowMinimumHeight(0)),0,2);
    err_d = new ErrorFileDialog(this);
    ferr_d = new FileCreationErr(this);
    connect(save_b,SIGNAL(clicked()),this,SLOT(createFile()));
}

void NewFileDialog::createFile()    {
    QString path = rootdir+name_e->text()+".xml";
    qDebug() << path;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        if(!file.open(QIODevice::WriteOnly))    {
            qDebug() << "File creation error.";
            ferr_d->exec();
        }
        else    {
            Xfile *xmleng = new Xfile();
            xmleng->newfile(path,name_e->text(),details_e->toPlainText());
            close();
        }
    }
    else    {
        qDebug() << "File already exists.";
        err_d->exec();
    }

    /*Call Tumul's class*/


}
