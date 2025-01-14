#ifndef JMCMOVEABSWDIGET_H
#define JMCMOVEABSWDIGET_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"
#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif
namespace Ui {
class jmcMoveAbsWdiget;
}

class jmcMoveAbsWdiget : public QWidget
{
    Q_OBJECT

public:
    explicit jmcMoveAbsWdiget(QWidget *parent = nullptr);
    ~jmcMoveAbsWdiget();
    int init(QString fucname , JMC_MoveAbs *func);
private:
    Ui::jmcMoveAbsWdiget *ui;
};

#endif // JMCMOVEABSWDIGET_H
