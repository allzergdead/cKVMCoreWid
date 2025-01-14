#ifndef CTOOLSWID_H
#define CTOOLSWID_H

#include <QMainWindow>
#include "include/cwidget/cresdock.h"
#include "include/cwidget/cVarList.h"
QT_BEGIN_NAMESPACE
namespace Ui { class cToolsWid; }
QT_END_NAMESPACE

class cToolsWid : public QMainWindow
{
    Q_OBJECT

public:
    cToolsWid(QWidget *parent = nullptr);
    cVarList varList;
    ~cToolsWid();
public slots:
    void showPage(cBasePage *page);
private:
    Ui::cToolsWid *ui;
};
#endif // CTOOLSWID_H
