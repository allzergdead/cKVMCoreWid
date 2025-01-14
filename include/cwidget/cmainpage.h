#ifndef CMAINPAGE_H
#define CMAINPAGE_H

#include <QWidget>

namespace Ui {
class cMainPage;
}

class cMainPage : public QWidget
{
    Q_OBJECT

public:
    explicit cMainPage(QWidget *parent = nullptr);
    ~cMainPage();

private:
    Ui::cMainPage *ui;
};

#endif // CMAINPAGE_H
