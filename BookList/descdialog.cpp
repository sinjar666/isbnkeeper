#include "descdialog.h"

Descdialog::Descdialog(QString path, QWidget *parent) :
    QDialog(parent)
{
    filepath=path;
    setModal(false);
    data=new Xfile();
	desc_text=new QTextEdit();
    desc_text->setReadOnly(true);
    lay = new QHBoxLayout(this);
    lay->addWidget(desc_text);
    QString desc;
    desc=data->getdescription(filepath);
    QString detail="No details found";
    if(desc=="")
        desc_text->setText(detail);
    else
        desc_text->setText(desc);
}

