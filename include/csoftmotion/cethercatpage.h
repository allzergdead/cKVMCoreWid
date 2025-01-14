#ifndef CETHERCATPAGE_H
#define CETHERCATPAGE_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"
#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif
namespace Ui {
class cEtherCATPage;
}

class cEtherCATPage : public cBasePage
{
    Q_OBJECT

public:
    explicit cEtherCATPage(QWidget *parent = nullptr);
    ~cEtherCATPage();

    virtual int conf(QString name,QJsonObject confObj);

    virtual int init(QString name,void *arg);

    virtual int beforDB();
    virtual int afterDB();

    virtual int beforDelete();

    cec_shm_pdo *etcmem = nullptr;

    static cBasePage *getNewPage();

    int test = 1;
#ifdef __linux
    cec_shm_pdo *getEtcPtr();
    cec_shm_pdo *getEtcPtr(int i);
#elif
#endif

private:
    Ui::cEtherCATPage *ui;
};

#endif // CETHERCATPAGE_H
