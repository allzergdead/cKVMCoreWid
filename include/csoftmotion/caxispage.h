#ifndef CAXISPAGE_H
#define CAXISPAGE_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"

#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif
namespace Ui {
class cAxisPage;
}

class cAxisPage : public cBasePage
{
    Q_OBJECT

public:
    explicit cAxisPage(QWidget *parent = nullptr);
    ~cAxisPage();
    virtual int conf(QString name,QJsonObject confObj);

    virtual int init(QString name,void *arg);

    virtual int beforDB();
    virtual int afterDB();

    virtual int beforDelete();

    static cBasePage *getNewPage();

    axis_ref *axis = nullptr;

    QTimer _10msTimer;


    JMC_Power power;
    JMC_Stop stop;
    JMC_JOG jog;
    JMC_Reset reset;
    JMC_SetPos setpos;
    JMC_MoveAbs moveabs;
    JMC_MoveVel movevel;
    JMC_WTMC_TC wtmctc;
    JMC_Home_Drv homedrv;
    JMC_MoveReal movereal;


#ifdef __linux

#elif
#endif
public slots:
    void _10msSlots();
signals:

private:
    Ui::cAxisPage *ui;





};

#endif // CAXISPAGE_H
