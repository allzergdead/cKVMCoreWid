#include "include/cwidget/cmainpage.h"
#include "ui_cmainpage.h"

cMainPage::cMainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cMainPage)
{
    ui->setupUi(this);
}

cMainPage::~cMainPage()
{
    delete ui;
}
