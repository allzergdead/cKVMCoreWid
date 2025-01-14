#ifndef CRESDOCK_H
#define CRESDOCK_H

#include <QDockWidget>

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QHash>
#include "cbasepage.h"

namespace Ui {
class cResDock;
}
struct pageCreater
{
    cBasePage* (*func)() = nullptr;
    QString resName = u8"";

};
struct pageInfo
{
    cBasePage* page = nullptr;
    QString name = "";
    QJsonObject jsobj;
    void *initArg = nullptr;
    QString icon ;
};
class cResDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit cResDock(QWidget *parent = nullptr);
    ~cResDock();
    //QJsonObject getBaseObj();
    QJsonObject getResObj(QString name , QString icon , QString pageclass);
    //QJsonObject getResObj(QString name , QString icon , QString pageclass,bool notSave);
    //void addNode(const QJsonObject& nodeData, QTreeWidgetItem* parentItem, QTreeWidget* treeWidget);
    //void addNode(const QJsonObject& nodeData, QTreeWidgetItem* parentItem);

    //int readConfig();
    //int insertPage(QString fullname , QString icon ,QString pageclass);


    int defaultStart();

    int defaultCreatPage(QJsonArray resAry);


    int defaultConfPages(QJsonArray resAry);

    int defaultinitVars();


    int insertPage(QString name , QString icon , QString pageclass , void *arg);


    static QHash<QString, pageCreater> pageCreat;
    static int regPageCreater(pageCreater creater);
    static int regPageCreater(cBasePage* (*func)()  , QString resName);
    static QString getIconPath(QString name);
    static QHash<QString ,pageInfo> resHash;
    static QVector<QString> pageVec;
    
    //启动流程设计
    int initReadConf();

    int initBaseTree();
    
    int runInit();
    
    int gerDB();
    

    int resStartError();


    QJsonArray resAry;
    //int insertTree();
public slots:
    void treeClicked();
signals:
    void showNewPage(cBasePage *page);
private:
    Ui::cResDock *ui;
};







#endif // CRESDOCK_H
