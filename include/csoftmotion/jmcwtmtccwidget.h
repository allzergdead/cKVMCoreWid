#ifndef JMCWTMTCCWIDGET_H
#define JMCWTMTCCWIDGET_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"
#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif
namespace Ui {
class jmcWtmtCCWidget;
}

class jmcWtmtCCWidget : public QWidget
{
    Q_OBJECT

public:
    explicit jmcWtmtCCWidget(QWidget *parent = nullptr);
    ~jmcWtmtCCWidget();
    int init(QString fucname , JMC_WTMC_TC *func);
private:
    Ui::jmcWtmtCCWidget *ui;
};

#endif // JMCWTMTCCWIDGET_H
