#include "include/cwidget/cSuperBtn.h"
#include "include/cwidget/cKeyBoard.h"
#include "include/cwidget/cVarList.h"

#include <QMenu>
#include <QInputDialog>
#include <QFileDialog>
#include <QTimer>
#include "include/cwidget/cVarConf.h"
#include "include/cwidget/cConnectDialog.h"

#pragma execution_character_set("utf-8")

QMutex cSuperBtn::btnMtx;
QHash<cSuperBtn*, cSuperBtn*> cSuperBtn::cBtnHash;
TaskManger cSuperBtn::taskPool;
bool cSuperBtn::inited = false;;
QVector<cSuperBtn*> cSuperBtn::cBtnVec;
QDialog* cSuperBtn::keyBoard = nullptr;
QDialog* cSuperBtn::varConf = nullptr;
QWidget* cSuperBtn::varList = nullptr;
QDialog* cSuperBtn::connectDialog = nullptr;

QString normalStyle = R"(
                      /* 1. 普通（未按下、未悬停）状态 */
                      QPushButton {
                          background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                                      stop:0 #4d4d4d,
                                                      stop:1 #5e5e5e);
                          border: 2px solid #666666;
                          border-radius: 10px;
                          padding: 2px 2px;
                          color: #ffffff;
                          font-size: 16px;
                          text-align: center;
                          box-shadow: 0 4px 8px rgba(0,0,0,0.25);
                      }

                      /* 2. 悬停（鼠标移到按钮上）状态 */
                      QPushButton:hover {
                          /* 可以让颜色稍微亮一点，或者修改边框颜色以示区分 */
                          background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                                      stop:0 #5e5e5e,
                                                      stop:1 #707070); /* 比原来更亮一些 */
                          border: 2px solid #888888; /* 边框颜色更亮，突出被选中感 */
                          box-shadow: 0 4px 8px rgba(0, 0, 0, 0.35); /* 阴影稍微加重或调整 */
                      }

                      /* 3. 按下（鼠标左键点下但未松开）状态 */
                      QPushButton:pressed {
                          /* 颜色加深，或者让高光更明显。也可反转渐变，让上面更暗一些 */
                          background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                                      stop:0 #3c3c3c,
                                                      stop:1 #4d4d4d);
                          border: 2px solid #444444; /* 压下时边框再深一些 */
                          box-shadow: inset 0 2px 5px rgba(0,0,0,0.5); /* 可使用内阴影表现凹下感 */
                      }

                      /* 4. 如果需要禁用状态（可选） */
                      QPushButton:disabled {
                          background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                                      stop:0 #bbbbbb,
                                                      stop:1 #cccccc);
                          color: #666666;
                          border: 2px solid #aaaaaa;
                          box-shadow: none; /* 禁用状态通常去掉阴影 */
                      }

)";
QString pressedStyle = R"(
                       /* 1. 普通（未按下、未悬停）状态 */
                       QPushButton {
                           background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                                       stop:0 #2f8f2f,   /* 相对亮些 */
                                                       stop:1 #4cae4c); /* 绿色渐变 */
                           border: 2px solid #256f25;   /* 较深绿色边框 */
                           color: #ffffff;              /* 白色文字 */
                           box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2); /* 外部阴影，略微立体感 */
                           border-radius: 10px;
                           padding: 4px 8px;
                           text-align: center;
                           font-size: 16px;
                       }

                       /* 2. 悬停（鼠标移到按钮上）状态 */
                       QPushButton:hover {
                           background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                                       stop:0 #3ba93b,
                                                       stop:1 #50c150);
                           border: 2px solid #228c22;  /* 边框稍微深些，做对比 */
                           box-shadow: 0 2px 6px rgba(0, 0, 0, 0.3); /* 阴影稍微加强 */
                       }

                       /* 3. 按下（鼠标左键按住但未松开）状态
                          使用你给出的内凹阴影等样式 */
                       QPushButton:pressed {
                           background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                                       stop:0 #297229,
                                                       stop:1 #3cb043); /* 绿色渐变背景 */
                           border: 2px solid #256f25;  /* 更深绿色边框 */
                           color: #ffffff;             /* 白色文字 */
                           box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3) inset; /* 内凹阴影 */
                           border-radius: 10px;
                           padding: 4px 8px;
                           text-align: center;
                           font-size: 16px;
                       }

                       /* 4. 禁用状态（可选） */
                       QPushButton:disabled {
                           background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                                       stop:0 #a8a8a8,
                                                       stop:1 #c2c2c2);
                           border: 2px solid #888888;
                           color: #666666;
                           box-shadow: none; /* 禁用状态通常去掉明显的阴影 */
                           cursor: not-allowed; /* 鼠标指针变成不可用状态 */
                       }
)";
QString disabledStyle = R"(
QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
    stop:0 #636363, stop:1 #747474); /* 更浅的灰色渐变背景 */
    border: 2px solid #7d7d7d; /* 浅灰色边框 */
    color: #aaaaaa; /* 更浅的灰色文本，增强对比度 */
    box-shadow: none; /* 去除阴影，表示不可操作 */
    border-radius: 10px; /* 圆角 */
	padding: 2px 2px; /* 适度内边距 */
	text-align: center; /* 文本居中 */
    font-size: 16px; /* 字体大小 */
}
)";
QString pressedDisabledStyle = R"(
QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
    stop:0 #297229, stop:1 #3cb043); /* 绿色背景的渐变与按下时一致 */
    border: 2px solid #555555; /* 较暗的灰色边框，表示不可操作 */
    color: #ffffff; /* 白色文本 */
    box-shadow: none; /* 去除阴影，强调不可操作状态 */
    border-radius: 10px; /* 圆角 */
	padding: 2px 2px; /* 适度内边距 */
	text-align: center; /* 文本居中 */
    font-size: 16px; /* 字体大小 */
}
)";
QString normalInputStyle = R"(
                           /* 1. 默认（未悬停、未按下）状态 */
                           QPushButton {
                               background-color: #333333; /* 暗灰色背景 */
                               border: 1px solid #555555; /* 较暗的灰色边框 */
                               border-radius: 6px; /* 柔和的圆角，类似输入框 */
                               padding: 2px 2px; /* 适度内边距 */
                               color: #cccccc; /* 浅灰色文本，增加可读性 */
                               font-size: 16px; /* 字体大小适中 */
                               text-align: left; /* 文本左对齐 */
                               box-shadow: 0 1px 3px rgba(0,0,0,0.1); /* 轻微外部阴影，增加层次感 */
                               transition: background-color 0.3s, border-color 0.3s, color 0.3s, box-shadow 0.3s; /* 平滑过渡效果 */
                           }

                           /* 2. 悬停（鼠标移到按钮上）状态 */
                           QPushButton:hover {
                               background-color: #444444; /* 背景颜色稍微变亮 */
                               border: 1px solid #777777; /* 边框颜色变亮 */
                               color: #ffffff; /* 文本颜色变为白色，增加对比 */
                               box-shadow: 0 2px 5px rgba(0,0,0,0.2); /* 阴影稍微加深，增强层次感 */
                           }

                           /* 3. 按下（鼠标左键按住但未松开）状态 */
                           QPushButton:pressed {
                               background-color: #2a2a2a; /* 背景颜色稍微变暗 */
                               border: 1px solid #444444; /* 边框颜色变暗 */
                               color: #dddddd; /* 文本颜色稍微变浅 */
                               box-shadow: inset 0 1px 3px rgba(0,0,0,0.3); /* 内凹阴影，模拟按下效果 */
                           }

                           /* 4. 禁用状态（可选） */
                           QPushButton:disabled {
                               background-color: #2e2e2e; /* 更暗的灰色背景 */
                               border: 1px solid #555555; /* 保持边框颜色 */
                               color: #888888; /* 灰色文本，表示不可用 */
                               box-shadow: none; /* 去除阴影 */
                               cursor: not-allowed; /* 鼠标指针变为不可用状态 */
                           }
)";

QString disabledInputStyle = R"(
QPushButton {
    background-color: #2e2e2e; /* 更暗的灰色背景，模拟不可输入的输入框 */
    border: 1px solid #4d4d4d; /* 与背景协调的边框颜色 */
	padding: 2px 2px; /* 适度内边距 */
    color: #999999; /* 更淡的灰色文本，降低视觉焦点 */
    border-radius: 6px; /* 保持圆角一致 */
    text-align: left; /* 文本左对齐 */
    font-size: 16px; /* 维持一致的字体大小 */
    box-shadow: none; /* 去除阴影，强调不可用状态的平面感 */
}
)";

QString menuStyle = R"(
QMenu {
    background-color: #3a3a3a; /* 暗色背景 */
    color: #eeeeee; /* 浅灰色文字，提高可读性 */
    border: 1px solid #505050; /* 边框颜色与背景协调 */
    font-size: 14px; /* 适中的字体大小，保持风格一致性 */

}

QMenu::item {
    background-color: transparent; /* 默认背景透明 */
    padding: 5px 20px; /* 菜单项内边距，足够空间确保可读性 */
}

QMenu::item:selected {
    background-color: #4b4b4b; /* 选中项背景颜色稍亮，提高区分度 */
    color: #ffffff; /* 选中项的文字为白色，增加对比 */
}

QMenu::item:disabled {
    color: #666666; /* 不可用项的文字颜色更暗，减少视觉焦点 */
}

QMenu::separator {
    height: 2px; /* 分隔线高度 */
    background: #505050; /* 分隔线颜色与边框相同 */
    margin-left: 10px; /* 分隔线左侧空间 */
    margin-right: 10px; /* 分隔线右侧空间 */
}
)";
cSuperBtn::cSuperBtn(QWidget* parent)
	: QPushButton(parent)
	, ui(new Ui::cSuperBtnClass())
{
	ui->setupUi(this);
	if (!inited) {
		taskPool.init(5);
		keyBoard = new cKeyBoard(nullptr);

        taskPool.addTask(whoShow, nullptr);
		inited = true;
		varConf = new cVarConf(nullptr);
		varList = new cVarList(nullptr);
	}
	btnMtx.lock();
	cBtnHash.insert(this, this);
	btnMtx.unlock();

	connect(this, &cSuperBtn::updateSign, this, &cSuperBtn::updateSlot, Qt::QueuedConnection);
    connect(this, &cSuperBtn::pressed, this, &cSuperBtn::btnPressSlot, Qt::QueuedConnection);
    connect(this, &cSuperBtn::released, this, &cSuperBtn::btnReleaseSlot, Qt::QueuedConnection);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(CreatMenu(const QPoint&)));
}
int cSuperBtn::setVar(QString varname)
{
	cBaseVar* var = cBaseVar::findNode(varname);
	if (var == nullptr) {
		return -1;
	}
	name = varname;
	setToolTip(var->info);
	return 0;
}
cSuperBtn::~cSuperBtn()
{
	btnMtx.lock();
	if (cBtnHash.find(this) != cBtnHash.end()) {
		cBtnHash.erase(cBtnHash.find(this));
	}
	btnMtx.unlock();
	delete ui;
}
void cSuperBtn::CreatMenu(const QPoint& pt) {
	QMenu menu(this);
	menu.setStyleSheet(menuStyle);
	menu.addAction(u8"变量配置", this, SLOT(varConfShow()));
	menu.addAction(u8"显示变量列表", this, SLOT(showVarList()));

	QPoint pt0(pt.x(), pt.y());
	menu.exec(QCursor::pos());
}
void cSuperBtn::varConfShow()
{
	cBaseVar* var = cBaseVar::findNode(name);
	if (var == nullptr) {
		return;
	}
	if (!var->checkLevel()) {
		return;
	}
	((cVarConf*)varConf)->show0(name);
}
void cSuperBtn::updateSlot()
{
	if (visibleRegion().isNull()) { return; }
	if (visibleRegion().isEmpty()) { return; }
    if (showStr == ""){
        showStr = this->text();
    }
	cBaseVar* var = cBaseVar::findNode(name);
	if (var == nullptr) {
		return;
	}
	bool check = var->checkLevel() && (var->dir == C_INPUT) && (!var->bind);
	bool ok = false;
    if (var->is<bool>() || (showType == forceBtnType::SHOW_BTN) ) {
		bool value = var->to<bool>(&ok);
        if(!ok){
            int intVale = var->toString().toInt();
            if(intVale == 0){
                value = false;
            }else{
                value = true;
            }
        }
		QString newStyle;
		if (check && !value) {
			newStyle = normalStyle;
		}
		if (check && value) {
			newStyle = pressedStyle;
		}
		if (!check && !value) {
			newStyle = disabledStyle;
		}
		if (!check && value) {
			newStyle = pressedDisabledStyle;
		}

		if (newStyle != oldStylesheet) {
			setStyleSheet(newStyle);
			oldStylesheet = newStyle;
		}
	}
	else {
		QString value = var->toString();
		QString newStyle;
		if (check) {
			newStyle = normalInputStyle;
		}
		else {
			newStyle = disabledInputStyle;
		}
		if (newStyle != oldStylesheet) {
			setStyleSheet(newStyle);
			oldStylesheet = newStyle;
		}
		setText(value);
	}
}
void cSuperBtn::inoputSlot()
{
	cBaseVar* var = cBaseVar::findNode(name);
	if (var == nullptr) {
		return;
	}
	bool check = var->checkLevel() && (var->dir == C_INPUT) && (!var->bind);
	if (!check) {
		return;
	}
	bool ok = false;
    inputTypeEnum type0 = var->getInputType();
    if (type0 == inputTypeEnum::C_BTN || (showType == forceBtnType::SHOW_BTN)) {
        if (var->is<bool>() ) {
			bool value = var->to<bool>(&ok);
			if (value) {
                var->byString(u8"0");
				var->varToDB();
			}
			else {
				var->byString(u8"1");
				var->varToDB();
			}
        }else {
			bool ok = false;
			QString value = var->toString();
			double valued = value.toDouble(&ok);
			if (ok) {
				if (valued == 0) {
					var->byString(u8"1");
					var->varToDB();
				}
				else {
					var->byString(u8"0");
					var->varToDB();
				}
			}
		}
	}
    else if (type0 == inputTypeEnum::C_KEYBOARD_DOT || type0 == inputTypeEnum::C_KEYBOARD_NO_DOT_SIGNED || type0 == inputTypeEnum::C_KEYBOARD_NO_DOT_UNSIGNED) {
		//keyBoard->show0(var);
		cKeyBoard* keyboard0 = (cKeyBoard*)keyBoard;
		keyboard0->show0(name);
	}
    else if (type0 == inputTypeEnum::C_USER_SET) {
		if (var->func->userSetInput != nullptr) {
			var->func->userSetInput(var);
		}
	}
    else if (type0 == inputTypeEnum::C_OPEN_FILE_DIR) {
		QString filePath = QFileDialog::getOpenFileName();
		if (filePath != "") {
			var->byString(filePath);
			var->varToDB();
		}
	}
    else if (type0 == inputTypeEnum::C_SAVE_FILE_DIR) {
		QString filePath = QFileDialog::getSaveFileName();
		if (filePath != "") {
			var->byString(filePath);
			var->varToDB();
		}
	}
    else if (type0 == inputTypeEnum::C_STRING_INPUT) {
		bool ok = false;;
		QString str = QInputDialog::getText(this, var->fullName, "", QLineEdit::Normal, var->toString(), &ok);
		if (ok) {
			var->byString(str);
			var->varToDB();
		}
	}
	else {
	}
}
void cSuperBtn::btnPressSlot()
{
    if(pressType == forcePressType::PRESS_NOT_RESET){
        return ;
    }
    cBaseVar* var = cBaseVar::findNode(name);
    if (var == nullptr) {
        return;
    }
    bool check = var->checkLevel() && (var->dir == C_INPUT) && (!var->bind);
    if (!check) {
        return;
    }
    bool ok = false;
    inputTypeEnum type0 = var->getInputType();
    if (type0 == inputTypeEnum::C_BTN || (showType == forceBtnType::SHOW_BTN)) {
        if (var->is<bool>() ) {
            bool value = var->to<bool>(&ok);
            if(pressType == forcePressType::PRESS_NOT_RESET){
                if (value) {
                    var->byString(u8"0");
                    var->varToDB();
                }
                else {
                    var->byString(u8"1");
                    var->varToDB();
                }
            }else{
                var->byString(u8"1");
                var->varToDB();
            }
        }else {
            bool ok = false;
            QString value = var->toString();
            double valued = value.toDouble(&ok);
            if (ok) {
                if(pressType == forcePressType::PRESS_NOT_RESET){
                    if (valued != 0) {
                        var->byString(u8"0");
                        var->varToDB();
                    }
                    else {
                        var->byString(u8"1");
                        var->varToDB();
                    }
                }else{
                    var->byString(u8"0");
                    var->varToDB();
                }
            }
        }
    }
    else if (type0 == inputTypeEnum::C_KEYBOARD_DOT || type0 == inputTypeEnum::C_KEYBOARD_NO_DOT_SIGNED || type0 == inputTypeEnum::C_KEYBOARD_NO_DOT_UNSIGNED) {
        //keyBoard->show0(var);
        cKeyBoard* keyboard0 = (cKeyBoard*)keyBoard;
        keyboard0->show0(name);
    }
    else if (type0 == inputTypeEnum::C_USER_SET) {
        if (var->func->userSetInput != nullptr) {
            var->func->userSetInput(var);
        }
    }
    else if (type0 == inputTypeEnum::C_OPEN_FILE_DIR) {
        QString filePath = QFileDialog::getOpenFileName();
        if (filePath != "") {
            var->byString(filePath);
            var->varToDB();
        }
    }
    else if (type0 == inputTypeEnum::C_SAVE_FILE_DIR) {
        QString filePath = QFileDialog::getSaveFileName();
        if (filePath != "") {
            var->byString(filePath);
            var->varToDB();
        }
    }
    else if (type0 == inputTypeEnum::C_STRING_INPUT) {
        bool ok = false;;
        QString str = QInputDialog::getText(this, var->fullName, "", QLineEdit::Normal, var->toString(), &ok);
        if (ok) {
            var->byString(str);
            var->varToDB();
        }
    }
    else {
    }
}
void cSuperBtn::btnReleaseSlot()
{
    cBaseVar* var = cBaseVar::findNode(name);
    if (var == nullptr) {
        return;
    }
    bool check = var->checkLevel() && (var->dir == C_INPUT) && (!var->bind);
    if (!check) {
        return;
    }
    bool ok = false;
    inputTypeEnum type0 = var->getInputType();
    if (type0 == inputTypeEnum::C_BTN || (showType == forceBtnType::SHOW_BTN)) {
        if (var->is<bool>() ) {
            bool value = var->to<bool>(&ok);
            if(pressType == forcePressType::PRESS_NOT_RESET){
                if (value) {
                    var->byString(u8"0");
                    var->varToDB();
                }
                else {
                    var->byString(u8"1");
                    var->varToDB();
                }
            }else{
                var->byString(u8"0");
                var->varToDB();
            }

        }else {
            bool ok = false;
            QString value = var->toString();
            double valued = value.toDouble(&ok);
            if(pressType == forcePressType::PRESS_NOT_RESET){
                if (ok) {
                    if(pressType == forcePressType::PRESS_NOT_RESET){
                        if (valued != 0) {
                            var->byString(u8"0");
                            var->varToDB();
                        }
                        else {
                            var->byString(u8"1");
                            var->varToDB();
                        }
                    }else{
                        var->byString(u8"0");
                        var->varToDB();
                    }
                }
            }
       }
    }
}
void* cSuperBtn::whoShow(void* arg)
{
	cSuperBtn* self = (cSuperBtn*)arg;
	while (true) {

		btnMtx.lock();
		cBtnVec.clear();
		auto it = cBtnHash.begin();
		for (it = cBtnHash.begin(); it != cBtnHash.end(); it++) {
			//if (self->visibleRegion().isNull()) { continue; }
			//if (self->visibleRegion().isEmpty()) { continue; }
			if (it.value()->visibleRegion().isNull()) { continue; }
			if (it.value()->visibleRegion().isEmpty()) { continue; }
			cBtnVec.append(it.value());
		}
		btnMtx.unlock();
		for (int i = 0; i < cBtnVec.size(); i++) {
			emit cBtnVec[i]->updateSign();
		}

        usleep(100 * 1000);
        //usleep(300 * 1000);
        //Sleep(300);
	}
}

int cSuperBtn::setBtn()
{
    showType = forceBtnType::SHOW_BTN;
}
int cSuperBtn::setEdit()
{
    showType = forceBtnType::SHOW_EDIT;
}
int cSuperBtn::setAuto()
{
    showType = forceBtnType::SHOW_AUTO;
}
int cSuperBtn::setBtnType(forcePressType type)
{
    pressType = type;
}
void cSuperBtn::showVarList()
{
	if (varList == nullptr) {
		return;
	}
	cVarList* list = (cVarList*)varList;
	list->hide();
	list->show();
}


QString cSuperBtn::getName()
{
	if (connectDialog == nullptr) {
		connectDialog = new cConnectDialog();
	}
	cConnectDialog* tempDialog = (cConnectDialog*)connectDialog;
	return tempDialog->getNameStr();
	//connectDialog->exec();

}

