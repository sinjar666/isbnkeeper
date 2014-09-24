#include "configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent)
{
    setModal(true);
    setWindowTitle(QString("Configure root directory"));
    fil = new QFile("/home/user/.isbnkeeper-config");
    if(!fil->open(QIODevice::ReadOnly)) {
        if(!fil->open(QIODevice::WriteOnly))
            qWarning("Unable to create config file");

    }
    QTextStream stream(fil);
    QString path;
    stream >> path;
    fil->close();
    path_e = new QLineEdit(path);
    path_e->setReadOnly(true);
    browse_b = new QPushButton(tr("Browse."));
    lay = new QHBoxLayout(this);
    lay->addWidget(path_e);
    lay->addWidget(browse_b);
    connect(browse_b,SIGNAL(clicked()),this,SLOT(chooseFile()));
}

void ConfigDialog::chooseFile() {
    QString path = QFileDialog::getExistingDirectory(this,tr("Choose a root directory"),path_e->text());
    if(!path.endsWith("/"))
        path+="/";
//    QProcess process;
//    if(path_e->text()!=path)  {
//        process.execute(QString("cp ")+path_e->text()+tr("*.xml ")+path);
//        process.execute(QString("mv ")+path_e->text()+tr("index ")+path);
//    }
    if(!fil->open(QIODevice::WriteOnly|QIODevice::Truncate))
            qWarning("Unable to update config file.");
        QTextStream stream(fil);
        stream << path;
        path_e->setText(path);
        fil->close();
        fil->setFileName(path+"tester");
        if(fil->open(QIODevice::WriteOnly)) {
            fil->remove();
            accept();
        }
        else
            reject();
}
