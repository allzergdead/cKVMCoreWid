#include "include/csoftmotion/jmcstopwidget.h"
#include "ui_jmcstopwidget.h"

jmcStopWidget::jmcStopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jmcStopWidget)
{
    ui->setupUi(this);
}


int jmcStopWidget::init(QString fucname , JMC_Stop *func)
{
    //    JMC_Stop stop;
    cBaseVar *var = nullptr;
    var = newCVar(&func->fDec  ,fucname + ".fDec",C_INPUT,0," 减速度");
    var = newCVar(&func->fJerk  ,fucname + ".fJerk",C_INPUT,0," 减减速度");
    var = newCVar(&func->Execute  ,fucname + ".Execute",C_INPUT,0," 触发信号");
    var = newCVar(&func->busy  ,fucname + ".busy",C_OUTPUT,0," 忙信号");
    var = newCVar(&func->done  ,fucname + ".done",C_OUTPUT,0," 完成信号");
    var = newCVar(&func->error  ,fucname + ".error",C_OUTPUT,0," 错误信号");
    var = newCVar(&func->state  ,fucname + ".state",C_OUTPUT,0," 状态步");
    var = newCVar(&func->aborted  ,fucname + ".aborted",C_OUTPUT,0," 打断信号");
    var = newCVar(&func->errorCode  ,fucname + ".errorCode",C_OUTPUT,0," 错误码");



    ui->fDec->setVar(fucname + ".fDec");
    ui->fJerk->setVar(fucname + ".fJerk");
    ui->Execute->setVar(fucname + ".Execute");
    ui->busy->setVar(fucname + ".busy");
    ui->done->setVar(fucname + ".done");
    ui->error->setVar(fucname + ".error");
    ui->aborted->setVar(fucname + ".aborted");
    ui->errorCode->setVar(fucname + ".errorCode");
    return 0;
}

jmcStopWidget::~jmcStopWidget()
{
    delete ui;
}
