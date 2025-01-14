#ifndef JMCPOWERWIDGET_H
#define JMCPOWERWIDGET_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"
#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif

namespace Ui {
class jmcPowerWidget;
}

class jmcPowerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit jmcPowerWidget(QWidget *parent = nullptr);
    ~jmcPowerWidget();
    int init(QString fucname , JMC_Power *func);
private:
    Ui::jmcPowerWidget *ui;
};

#endif // JMCPOWERWIDGET_H
