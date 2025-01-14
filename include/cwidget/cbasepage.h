#ifndef CBASEPAGE_H
#define CBASEPAGE_H

#include <QWidget>
#include "include/cwidget/cVarList.h"
#include <QScrollArea>
#include <QTabWidget>
#include <QTimer>
namespace Ui {
class cBasePage;
}

class cBasePage : public QWidget
{
    Q_OBJECT

public:
    explicit cBasePage(QWidget *parent = nullptr);
    ~cBasePage();
    QString name;
    void *resDock = nullptr;

    bool xStatic = false;

    bool needShow = true;
    virtual int conf(QString name,QJsonObject confObj);

    virtual int init(QString name,void *arg);

    virtual int beforDB();
    virtual int afterDB();

    virtual int beforDelete();

    QScrollArea *scrollArea;

    static void  tabWidInertScroll(QTabWidget *tab);


    static int mkIfNoDir(QString path);
    static int mkIfNoFile(QString path);
    static int getQJsonObjFromFile(QString filePath , QJsonArray *obj);
private:
    Ui::cBasePage *ui;
};

#endif // CBASEPAGE_H
