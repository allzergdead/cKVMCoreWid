#include "include/cwidget/cresdock.h"
#include "ui_cresdock.h"
#include <QHash>

// QT JSON
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

// QT SQL
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMutex>


#include <QTreeWidgetItem>
#include <QTreeWidget>


#include <QDir>
#include <QDebug>



#define ICON_PATH "/home/icon/"

QHash<QString, pageCreater> cResDock::pageCreat;
QHash<QString ,pageInfo> cResDock::resHash;
QVector<QString> cResDock::pageVec;

cResDock::cResDock(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::cResDock)
{
    ui->setupUi(this);
    //QJsonObject obj =  getBaseObj();
    //addNode(obj, nullptr , ui->resTree);
    ui->resTree->setHeaderHidden(true);

    connect(ui->resTree,&QTreeWidget::clicked,this,&cResDock::treeClicked);
}

cResDock::~cResDock()
{
    delete ui;
}


int cResDock::regPageCreater(pageCreater creater)
{
    if(pageCreat.find(creater.resName) != pageCreat.end()){
        cBaseVar::insertLog(-1,"资源管理器","资源类型 " + creater.resName + " 重复");
        return -1;
    }
    pageCreat.insert(creater.resName,creater);
    return 0;
}
int cResDock::regPageCreater(cBasePage* (*func)()  , QString resName)
{
    pageCreater creater;
    creater.func = func;
    creater.resName = resName;
    return regPageCreater(creater);
}


void cResDock::treeClicked()
{
    QString name = ui->resTree->currentItem()->data(2,2).toString();
    if(resHash.find(name) != resHash.end()){
        if(resHash[name].page != nullptr){
            cBasePage *page = (cBasePage *)resHash[name].page;

            if(page->needShow){
                emit showNewPage(resHash[name].page);
            }
        }
    }

    cBaseVar::insertLog(0,name,"click");
}

static QJsonArray getBaseResObj(cResDock *res)
{
    QJsonArray objAry;
    QJsonObject Hardware = res->getResObj(u8"Hardware",u8"/hardware.png",u8"");
    QJsonObject Cores = res->getResObj(u8"Hardware.Cores", u8"cpu.png", u8"");

    QJsonObject EtherCat = res->getResObj(u8"ETCMasters", u8"pciecard.png", u8"");
    QJsonObject EtherCat0 = res->getResObj(u8"ETCMasters.EtherCAT0", u8"ethercat.png", u8"EtherCAT");
    //QJsonObject Slaves = res->getResObj(u8"ETCMasters.EtherCAT0.Slaves", u8"slavepdo.png", u8"");
    //QJsonObject Axes = res->getResObj(u8"ETCMasters.EtherCAT0.Axes", u8"axis.png", u8"");

    QJsonObject Tasks = res->getResObj(u8"Tasks", u8"tasks.png", u8"");

    QJsonObject HMIPage = res->getResObj(u8"HMIPage", u8"iconfonticon-baobia_1.png", u8"");


    objAry.append(Hardware);
    objAry.append(Cores);
    objAry.append(EtherCat);
    objAry.append(EtherCat0);
    //objAry.append(Slaves);
    //objAry.append(Axes);
    objAry.append(Tasks);
    objAry.append(HMIPage);


    return objAry;

}


QTreeWidgetItem* getItemFromPath(QTreeWidget* treeWidget, const QString& path)
{
    // 如果传入的路径为空，直接返回 nullptr
    if (path.isEmpty())
    {
        return nullptr;
    }

    // 将路径通过 "." 分隔为若干层级
    QStringList pathList = path.split('.');

    // 找到首层节点（顶层节点）
    QTreeWidgetItem* currentItem = nullptr;
    bool found = false;
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* topLevelItem = treeWidget->topLevelItem(i);
        if (topLevelItem->text(0) == pathList[0])
        {
            currentItem = topLevelItem;
            found = true;
            break;
        }
    }

    // 如果顶层节点都没匹配到，直接返回 nullptr
    if (!found)
    {
        return nullptr;
    }

    // 从 pathList[1] 开始，逐层向下查找子节点
    for (int i = 1; i < pathList.size(); ++i)
    {
        bool childFound = false;
        for (int j = 0; j < currentItem->childCount(); ++j)
        {
            QTreeWidgetItem* child = currentItem->child(j);
            if (child->text(0) == pathList[i])
            {
                currentItem = child;
                childFound = true;
                break;
            }
        }

        // 如果在当前层级没有找到匹配的子节点，返回 nullptr
        if (!childFound)
        {
            return nullptr;
        }
    }

    // 如果能逐层找到，最终返回找到的节点指针
    return currentItem;
}



static QJsonArray resArtToTree(QTreeWidget *tree , QJsonArray resAry)
{
    int maxdotNum = 0;
    for(int it = 0;it < resAry.size() ; it++){
        QJsonObject obj = resAry.at(it).toObject();
        if(obj.contains("name")){
            QString name = obj["name"].toString();
            QStringList nameList = name.split(".");
            maxdotNum = std::max(maxdotNum,nameList.size());
            cBaseVar::insertLog(1,"resArtToTree" , "has res  " + name);
        }else{
            continue;
        }
    }
    QVector<QVector<int>> initLIst;
    initLIst.resize(maxdotNum);
    for(int it = 0;it < resAry.size() ; it++){
        QJsonObject obj = resAry.at(it).toObject();
        if(obj.contains("name")){
            QString name = obj["name"].toString();
            QStringList nameList = name.split(".");
            int dotNum = nameList.size() - 1;
            if(dotNum < initLIst.size()){
                initLIst[dotNum].append(it);
            }
        }else{
            continue;
        }
    }

    for(int i = 0 ; i < initLIst.size();i++){
        int maxSizei = initLIst.size();
        for(int j = 0 ; j < initLIst[i].size();j++){
            int maxSizej = initLIst.size();
            if(i == 0){
                QJsonObject  obj =  resAry[initLIst[i][j]].toObject();
                if(!obj.contains("name")){
                    continue;
                }else{
                    QString name = obj["name"].toString();
                    QString iconPath = obj["icon"].toString();
                    QTreeWidgetItem* item = new QTreeWidgetItem();
                    item->setText(0, name);
                    item->setIcon(0, QIcon(iconPath));

                    item->setData(2,2,name);

                    tree->addTopLevelItem(item);
                    cBaseVar::insertLog(1,"resArtToTree" , "insert " + name);
                }
            }else{
                QJsonObject  obj =  resAry[initLIst[i][j]].toObject();
                if(!obj.contains("name")){
                    continue;
                }
                QString name = obj["name"].toString();
                QString iconPath = obj["icon"].toString();
                QTreeWidgetItem* item = new QTreeWidgetItem();

                QStringList nameList = name.split(".");


                item->setText(0, nameList.last());
                item->setIcon(0, QIcon(iconPath));
                item->setData(2,2,name);
                nameList.removeLast();
                QString fathername = nameList.join(".");



                QTreeWidgetItem* father = getItemFromPath(tree , fathername);
                if(father != nullptr){
                    father->addChild(item);
                    cBaseVar::insertLog(1,"resArtToTree" , "insert " + name);
                }

            }
        }
    }
}

int cResDock::defaultStart()
{
    int ref = cBasePage::mkIfNoDir("data/configs");
    if(ref != 0){
        cBaseVar::insertLog(-1,u8"资源管理器",u8"无法创建资源配置文件，启动失败");
        resStartError();
        return -1;
    }
    ref = cBasePage::mkIfNoFile("data/configs/resdata.conf");
    if(ref != 0){
        cBaseVar::insertLog(-1,u8"资源管理器",u8"无法创建资源配置文件，启动失败");
        resStartError();
        return -1;
    }

    ref = cBasePage::getQJsonObjFromFile("data/configs/resdata.conf" , &resAry);
    if(ref == -1){

        cBaseVar::insertLog(-1,u8"资源管理器",u8"无法解析资源配置文件，启动失败");
        resStartError();
        return -1;
    }else if(ref == -2 || ref == -3){
        cBaseVar::insertLog(-1,u8"资源管理器",u8"资源配置文件为空或无法解析，生成默认资源");
        resAry = getBaseResObj(this);
    }

    defaultCreatPage(resAry);

    defaultConfPages(resAry);
    defaultinitVars();
    resArtToTree(ui->resTree , resAry);

    return 0;
}

int cResDock::insertPage(QString name , QString icon , QString pageclass , void *arg)
{
    QJsonObject obj;
    obj[u8"name"] = name;
    obj[u8"icon"] = ICON_PATH + icon;
    obj[u8"pageclass"] = pageclass;
    cBaseVar::insertLog(1,"insertPage" , "name :" + name);
    resAry.append(obj);


    if(pageCreat.find(pageclass) != pageCreat.end()){
        pageInfo tempPage;
        tempPage.name = name;
        tempPage.page = pageCreat[pageclass].func();
        tempPage.page->name = tempPage.name;
        if(tempPage.page == nullptr){
            tempPage.page = new cBasePage();
        }
        tempPage.page->resDock = this;
        tempPage.jsobj = obj;
        tempPage.initArg = arg;

        resHash.insert(name,tempPage);
        pageVec.append(name);
    }

    return 0;
}

int cResDock::defaultCreatPage(QJsonArray resAry)
{
    for(int it = 0;it < resAry.size() ; it++){
        QJsonObject obj = resAry.at(it).toObject();
        if(obj.contains("name")){
            QString name = obj["name"].toString();
            QString pageclass = obj["pageclass"].toString();
            if(pageCreat.find(pageclass) != pageCreat.end()){
                pageInfo tempPage;
                tempPage.name = name;
                tempPage.page = pageCreat[pageclass].func();
                tempPage.page->name = tempPage.name;
                if(tempPage.page == nullptr){
                    tempPage.page = new cBasePage();
                }
                tempPage.page->resDock = this;
                tempPage.jsobj = obj;
                resHash.insert(name,tempPage);
                pageVec.append(name);
            }
        }else{
            continue;
        }
    }


}
int cResDock::defaultConfPages(QJsonArray resAry)
{
    for(int i = 0 ; i < pageVec.size();i++){
        if(resHash.find(pageVec[i]) != resHash.end()){
            cBaseVar::insertLog(1,"defaultConfPages" , "has res  " + resHash[pageVec[i]].name);
            resHash[pageVec[i]].page->conf(pageVec[i],resHash[pageVec[i]].jsobj);
        }
    }

}
int cResDock::defaultinitVars()
{
    for(int i = 0 ; i < pageVec.size();i++){
        if(resHash.find(pageVec[i]) != resHash.end()){
            resHash[pageVec[i]].page->init(pageVec[i],resHash[pageVec[i]].initArg);
        }
    }
    return 0;
}
int cResDock::resStartError()
{
    return 0;
}


QJsonObject cResDock::getResObj(QString name, QString icon, QString pageclass)
{
    QJsonObject obj;
    if(resHash.find(name) != resHash.end()){
        return obj;
    }

    obj[u8"name"] = name;
    obj[u8"icon"] = ICON_PATH + icon;
    obj[u8"pageclass"] = pageclass;

    pageInfo tempPage;
    tempPage.page = nullptr;
    tempPage.name = name;
    if(pageCreat.find(pageclass) != pageCreat.end()){
        tempPage.page = pageCreat[pageclass].func();
        if(tempPage.page != nullptr){
            tempPage.page->resDock = this;
            tempPage.page->name = tempPage.name;
        }
    }else{
        tempPage.page = new cBasePage();
        if(tempPage.page != nullptr){
            tempPage.page->needShow = false;
            tempPage.page->resDock = this;
            tempPage.page->name = tempPage.name;
        }
    }
    resHash.insert(name,tempPage);

    return obj;
}
/*QJsonObject cResDock::getResObj(QString name , QString icon , QString pageclass,bool notSave)
{
    QJsonObject obj;
    if(resHash.find(name) != resHash.end()){
        return obj;
    }

    obj[u8"name"] = name;
    obj[u8"icon"] = ICON_PATH + icon;
    obj[u8"pageclass"] = pageclass;
    obj[u8"notSave"] = QString::number(notSave);
    pageInfo tempPage;
    tempPage.page = nullptr;
    tempPage.name = name;
    if(pageCreat.find(pageclass) != pageCreat.end()){
        tempPage.page = pageCreat[pageclass].func();
        if(tempPage.page != nullptr){
            tempPage.page->name = tempPage.name;
        }
    }
    resHash.insert(name,tempPage);

    return obj;
}
QString cResDock::getIconPath(QString name)
{
    return ICON_PATH + name;
}
QJsonObject cResDock::getBaseObj()
{
    QJsonObject obj;
    // Hardware;
    QJsonObject Hardware = getResObj(u8"Hardware",u8"/hardware.png",u8"");

    QJsonObject Cores = getResObj(u8"Cores", u8"cpu.png", u8"");

    QJsonObject EtherCat = getResObj(u8"EtherCAT", u8"ethercat.png", u8"EtherCAT");
    QJsonObject Slaves = getResObj(u8"Slaves", u8"slavepdo.png", u8"");
    QJsonObject Axes = getResObj(u8"Axes", u8"axis.png", u8"");


    Hardware[u8"Cores"] = Cores;

    EtherCat[u8"Slaves"] = Slaves;
    EtherCat[u8"Axes"] = Axes;

    Hardware[u8"EtherCAT"] = EtherCat;

    obj[u8"Hardware"] = Hardware;
    // Tasks
    QJsonObject Tasks = getResObj(u8"Tasks", u8"tasks.png", u8"");

    obj[u8"Tasks"] = Tasks;

    return obj;
}

void cResDock::addNode(const QJsonObject& nodeData, QTreeWidgetItem* parentItem)
{
    return addNode(nodeData, parentItem, ui->resTree);
}
void cResDock::addNode(const QJsonObject& nodeData, QTreeWidgetItem* parentItem, QTreeWidget* treeWidget) {

    for (const QString& key : nodeData.keys()) {
        const QJsonValue& value = nodeData[key];


        QString name = key;
        QString iconPath = value.toObject().contains("icon") ? value.toObject()["icon"].toString() : "";  // ´Ó×ÓÏî»ñÈ¡Í¼±êÂ·¾¶
        if (key == u8"name" || key == "icon" || key == "pageclass") {
            continue;
        }

        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, name);
        item->setIcon(0, QIcon(iconPath));


        if (parentItem) {
            parentItem->addChild(item);
        }
        else {

            treeWidget->addTopLevelItem(item);
        }


        if (value.isObject()) {
            addNode(value.toObject(), item, treeWidget);
        }
        else if (value.isArray()) {

            QJsonArray array = value.toArray();
            for (const QJsonValue& arrItem : array) {
                if (arrItem.isObject()) {
                    addNode(arrItem.toObject(), item, treeWidget);
                }
            }
        }
    }
}



*/









