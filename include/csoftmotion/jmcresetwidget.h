#ifndef JMCRESETWIDGET_H
#define JMCRESETWIDGET_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"
#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif
namespace Ui {
class jmcResetWidget;
}

class jmcResetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit jmcResetWidget(QWidget *parent = nullptr);
    ~jmcResetWidget();
    int init(QString fucname , JMC_Reset *func);
private:
    Ui::jmcResetWidget *ui;
};

#endif // JMCRESETWIDGET_H
