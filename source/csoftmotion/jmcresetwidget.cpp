#include "include/csoftmotion/jmcresetwidget.h"
#include "ui_jmcresetwidget.h"

jmcResetWidget::jmcResetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jmcResetWidget)
{
    ui->setupUi(this);
}

jmcResetWidget::~jmcResetWidget()
{
    delete ui;
}
int jmcResetWidget::init(QString fucname , JMC_Reset *func)
{
    //    JMC_Stop stop;
    cBaseVar *var = nullptr;
    var = newCVar(&func->Execute  ,fucname + ".Execute",C_INPUT,0," 触发信号");
    var = newCVar(&func->busy  ,fucname + ".busy",C_OUTPUT,0," 忙信号");
    var = newCVar(&func->done  ,fucname + ".done",C_OUTPUT,0," 完成信号");
    var = newCVar(&func->error  ,fucname + ".error",C_OUTPUT,0," 错误信号");
    var = newCVar(&func->state  ,fucname + ".state",C_OUTPUT,0," 状态步");
    var = newCVar(&func->aborted  ,fucname + ".aborted",C_OUTPUT,0," 打断信号");
    var = newCVar(&func->errorCode  ,fucname + ".errorCode",C_OUTPUT,0," 错误码");



    ui->Execute->setVar(fucname + ".Execute");
    ui->busy->setVar(fucname + ".busy");
    ui->done->setVar(fucname + ".done");
    ui->error->setVar(fucname + ".error");
    ui->aborted->setVar(fucname + ".aborted");
    ui->errorCode->setVar(fucname + ".errorCode");
    return 0;
}
