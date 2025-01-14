#ifndef JMCMOVEVELWIDGET_H
#define JMCMOVEVELWIDGET_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"
#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif
namespace Ui {
class jmcMoveVelWidget;
}

class jmcMoveVelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit jmcMoveVelWidget(QWidget *parent = nullptr);
    ~jmcMoveVelWidget();
    int init(QString fucname , JMC_MoveVel *func);
private:
    Ui::jmcMoveVelWidget *ui;
};

#endif // JMCMOVEVELWIDGET_H
