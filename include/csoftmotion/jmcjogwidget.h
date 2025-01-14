#ifndef JMCJOGWIDGET_H
#define JMCJOGWIDGET_H

#include <QWidget>
#include "include/cwidget/cbasepage.h"
#ifdef __linux
    #include "../ethercatmasterConsole/etcHeader/etcheader.h"
    #include "../ethercatmasterConsole/etcHeader/jmc_axis_cmd.h"
#elif
#endif
namespace Ui {
class jmcJogWidget;
}

class jmcJogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit jmcJogWidget(QWidget *parent = nullptr);
    ~jmcJogWidget();
    int init(QString fucname , JMC_JOG *func);
private:
    Ui::jmcJogWidget *ui;
};

#endif // JMCJOGWIDGET_H
