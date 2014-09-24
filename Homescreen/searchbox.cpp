#include "searchbox.h"

SearchBox::SearchBox(QWidget *parent) :
    QWidget(parent)
{
    lay = new QHBoxLayout(this);
    icon = new QLabel();
    icon->setPixmap(QPixmap(tr(":/Homescreen/qml/Search-icon.png")).scaled(40,40));
    editor = new QLineEdit();
    editor->setFrame(false);
    setFocusProxy(editor);
    setFocusPolicy(Qt::StrongFocus);
    lay->addWidget(icon);
    lay->addWidget(editor);
    connect(editor,SIGNAL(textChanged(QString)),this,SLOT(sendText(QString)));
}

void SearchBox::sendText(QString text)  {
    emit keyPressed(text);
}
