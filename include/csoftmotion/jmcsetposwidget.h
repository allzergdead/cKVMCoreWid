#ifndef JMCSETPOSWIDGET_H
#define JMCSETPOSWIDGET_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"
#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif
namespace Ui {
class jmcSetPosWidget;
}

class jmcSetPosWidget : public QWidget
{
    Q_OBJECT

public:
    explicit jmcSetPosWidget(QWidget *parent = nullptr);
    ~jmcSetPosWidget();
    int init(QString fucname , JMC_SetPos *func);
private:
    Ui::jmcSetPosWidget *ui;
};

#endif // JMCSETPOSWIDGET_H
