#include "include/csoftmotion/jmcpowerwidget.h"
#include "ui_jmcpowerwidget.h"

jmcPowerWidget::jmcPowerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jmcPowerWidget)
{
    ui->setupUi(this);
}


int jmcPowerWidget::init(QString fucname , JMC_Power *func)
{
    //    JMC_Power power;
    cBaseVar *var = nullptr;
    var = newCVar(&func->xPOn  ,fucname + ".xPOn",C_INPUT,0," 使能");
    var = newCVar(&func->xDStart  ,fucname + ".xDStart",C_INPUT,0," 允许运动");
    var = newCVar(&func->xInPower  ,fucname + ".xInPower",C_OUTPUT,0," 使能中");
    var = newCVar(&func->busy  ,fucname + ".busy",C_OUTPUT,0," 忙信号");
    var = newCVar(&func->done  ,fucname + ".done",C_OUTPUT,0," 完成信号");
    var = newCVar(&func->error  ,fucname + ".error",C_OUTPUT,0," 错误信号");
    var = newCVar(&func->errorCode  ,fucname + ".errorCode",C_OUTPUT,0," 错误码");


    ui->powerOn->setVar(fucname + ".xPOn");
    ui->drvStart->setVar(fucname + ".xDStart");
    ui->inPower->setVar(fucname + ".xInPower");
    return  0;
}


jmcPowerWidget::~jmcPowerWidget()
{
    delete ui;
}
