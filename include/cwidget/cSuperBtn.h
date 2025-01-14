#pragma once

#include <QWidget>
#include <QPushButton>
#include <QMutex>
#include "ui_cSuperBtn.h"
#include "../carguments/cBaseVar.h"
#include "../taskmanager/taskmanger.h"

//#include "cKeyBoard.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class cSuperBtnClass; };
QT_END_NAMESPACE

enum forceBtnType{
    SHOW_AUTO,
    SHOW_BTN,
    SHOW_EDIT
};

enum forcePressType{
    PRESS_NOT_RESET,
    PRESS_RESET
};

class cSuperBtn : public QPushButton
{
	Q_OBJECT

public:
	cSuperBtn(QWidget *parent = nullptr);
	~cSuperBtn();

	QString name;
    QString showStr = "";
	int setVar(QString varname);
    int setBtn();
    int setBtnType(forcePressType type);
    int setEdit();
    int setAuto();
	//static int checkShow();
	static QMutex btnMtx;
	static QHash<cSuperBtn*, cSuperBtn*> cBtnHash;
	static TaskManger taskPool;
	static bool inited;
	static QVector<cSuperBtn*> cBtnVec;

	static void* whoShow(void* arg);

	static QDialog *keyBoard;
	static QDialog *varConf;
	static QWidget *varList;

	QString oldStylesheet = "";

	static QDialog* connectDialog;
	static QString getName();

signals:
	void updateSign();
public slots:
	void updateSlot();
	void inoputSlot();
    void btnPressSlot();
    void btnReleaseSlot();
	void CreatMenu(const QPoint&);
	void varConfShow();
	void showVarList();
	
private:
	Ui::cSuperBtnClass *ui;


    forceBtnType showType = forceBtnType::SHOW_AUTO;
    forcePressType pressType  = forcePressType::PRESS_NOT_RESET;
};
