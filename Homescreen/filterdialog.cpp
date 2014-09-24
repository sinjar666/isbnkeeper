#include "filterdialog.h"

FilterDialog::FilterDialog(Engine *e, QWidget *parent) :
    QDialog(parent)
{
    obj=e;
    arg = e->getFilters();
    title_b = new QCheckBox("Title");
    author_b  = new QCheckBox("Author");
    pub_b = new QCheckBox("Publisher");

    if((arg & Engine::TITLE_F)>0)
        title_b->setChecked(true);
    if((arg & Engine::AUTHOR_F)>0)
        author_b->setChecked(true);
    if((arg & Engine::PUBLISHER_F)>0)
        pub_b->setChecked(true);

    lay = new QHBoxLayout(this);
    lay->addWidget(title_b);
    lay->addWidget(author_b);
    lay->addWidget(pub_b);
    connect(title_b,SIGNAL(stateChanged(int)),this,SLOT(titleChecked(int)));
    connect(author_b,SIGNAL(stateChanged(int)),this,SLOT(authorChecked(int)));
    connect(pub_b,SIGNAL(stateChanged(int)),this,SLOT(pubChecked(int)));
}

void FilterDialog::titleChecked(int state)    {
    obj->setFilter(Engine::TITLE_F,(state==Qt::Checked)?true:false);
}

void FilterDialog::authorChecked(int state)    {
    obj->setFilter(Engine::AUTHOR_F,(state==Qt::Checked?true:false));
}

void FilterDialog::pubChecked(int state)    {
    obj->setFilter(Engine::PUBLISHER_F,(state==Qt::Checked?true:false));
}
