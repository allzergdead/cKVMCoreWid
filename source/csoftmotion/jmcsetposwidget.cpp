#include "include/csoftmotion/jmcsetposwidget.h"
#include "ui_jmcsetposwidget.h"

jmcSetPosWidget::jmcSetPosWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jmcSetPosWidget)
{
    ui->setupUi(this);
}

jmcSetPosWidget::~jmcSetPosWidget()
{
    delete ui;
}
int jmcSetPosWidget::init(QString fucname , JMC_SetPos *func)
{
    //    JMC_Stop stop;
    cBaseVar *var = nullptr;
    var = newCVar(&func->fPos  ,fucname + ".fPos",C_INPUT,0," 目标位置");
    var = newCVar(&func->Execute  ,fucname + ".Execute",C_INPUT,0," 触发信号");
    var = newCVar(&func->busy  ,fucname + ".busy",C_OUTPUT,0," 忙信号");
    var = newCVar(&func->done  ,fucname + ".done",C_OUTPUT,0," 完成信号");
    var = newCVar(&func->error  ,fucname + ".error",C_OUTPUT,0," 错误信号");
    var = newCVar(&func->state  ,fucname + ".state",C_OUTPUT,0," 状态步");
    var = newCVar(&func->aborted  ,fucname + ".aborted",C_OUTPUT,0," 打断信号");
    var = newCVar(&func->errorCode  ,fucname + ".errorCode",C_OUTPUT,0," 错误码");



    ui->fPos->setVar(fucname + ".fPos");
    ui->Execute->setVar(fucname + ".Execute");
    ui->busy->setVar(fucname + ".busy");
    ui->done->setVar(fucname + ".done");
    ui->error->setVar(fucname + ".error");
    ui->aborted->setVar(fucname + ".aborted");
    ui->errorCode->setVar(fucname + ".errorCode");
    return 0;
}
