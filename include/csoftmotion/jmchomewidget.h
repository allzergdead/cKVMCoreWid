#ifndef JMCHOMEWIDGET_H
#define JMCHOMEWIDGET_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"
#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif
namespace Ui {
class jmcHomeWidget;
}

class jmcHomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit jmcHomeWidget(QWidget *parent = nullptr);
    ~jmcHomeWidget();
    int init(QString fucname , JMC_Home_Drv *func);
private:
    Ui::jmcHomeWidget *ui;
};

#endif // JMCHOMEWIDGET_H
