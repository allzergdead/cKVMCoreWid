#include "ctoolswid.h"
#include "ui_ctoolswid.h"
#include "include/cwidget/cresdock.h"

#include <QMessageBox>


#include "include/csoftmotion/cethercatpage.h"

#include "include/csoftmotion/caxispage.h"
cToolsWid::cToolsWid(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cToolsWid)
{
    ui->setupUi(this);
    cResDock *resDoc = new cResDock();

    pageCreater creater;
    creater.func = cEtherCATPage::getNewPage;
    creater.resName = "EtherCAT";
    resDoc->regPageCreater(creater);


    creater.func = cAxisPage::getNewPage;
    creater.resName = "Axis";
    resDoc->regPageCreater(creater);


//    QJsonObject obj =  resDoc->getBaseObj();
//    resDoc->addNode(obj, nullptr);
//    if(resDoc->resHash.find("EtherCAT")  != resDoc->resHash.end()){
//        resDoc->resHash["EtherCAT"].page->init("EtherCAT" , nullptr);
//    }


    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea , resDoc);

    resDoc->defaultStart();


    ui->mainTab->setTabsClosable(true);

    // 启用滚动功能
    ui->mainTab->tabBar()->setUsesScrollButtons(true); // 启用滚动按钮

    //resDoc->

    // 处理关闭按钮点击事件
    QObject::connect(ui->mainTab, &QTabWidget::tabCloseRequested, [&](int index) {
        ui->mainTab->removeTab(index);
        return;
        int ret = QMessageBox::question(
            this,
            "关闭标签页",
            QString("确定要关闭标签页 '%1' 吗？").arg(ui->mainTab->tabText(index)),
            QMessageBox::Yes | QMessageBox::No);

        if (ret == QMessageBox::Yes) {
            ui->mainTab->removeTab(index); // 移除对应索引的标签页
        }
    });

    connect(resDoc,&cResDock::showNewPage,this,&cToolsWid::showPage);


    connect(ui->showVarList,&QAction::triggered,&varList,&cVarList::show);
}
void cToolsWid::showPage(cBasePage *page)
{
    if(page == nullptr){
        return;
    }
    QStringList nameList = page->name.split(".");
    ui->mainTab->addTab((QWidget *)page,nameList.last());
    ui->mainTab->setCurrentWidget((QWidget *)page);
}
cToolsWid::~cToolsWid()
{
    delete ui;
}

