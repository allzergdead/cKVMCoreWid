#ifndef JMCSTOPWIDGET_H
#define JMCSTOPWIDGET_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"
#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif

namespace Ui {
class jmcStopWidget;
}

class jmcStopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit jmcStopWidget(QWidget *parent = nullptr);
    ~jmcStopWidget();
    int init(QString fucname , JMC_Stop *func);
private:
    Ui::jmcStopWidget *ui;
};

#endif // JMCSTOPWIDGET_H
