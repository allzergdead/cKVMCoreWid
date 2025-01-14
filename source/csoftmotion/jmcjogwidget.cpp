#include "include/csoftmotion/jmcjogwidget.h"
#include "ui_jmcjogwidget.h"

jmcJogWidget::jmcJogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jmcJogWidget)
{
    ui->setupUi(this);
}
int jmcJogWidget::init(QString fucname , JMC_JOG *func)
{

    cBaseVar *var = nullptr;
//    JMC_JOG jog;
    var = newCVar(&func->fAcc  ,fucname + ".fAcc",C_INPUT,0," ");
    var = newCVar(&func->fDec  ,fucname + ".fDec",C_INPUT,0," ");
    var = newCVar(&func->fVel  ,fucname + ".fVel",C_INPUT,0," ");
    var = newCVar(&func->fJerk  ,fucname + ".fJerk",C_INPUT,0," ");
    var = newCVar(&func->negative  ,fucname + ".negative",C_INPUT,0," ");
    var = newCVar(&func->positive  ,fucname + ".positive",C_INPUT,0," ");
    var = newCVar(&func->busy  ,fucname + ".busy",C_OUTPUT,0," ");
    var = newCVar(&func->done  ,fucname + ".done",C_OUTPUT,0," ");
    var = newCVar(&func->error  ,fucname + ".error",C_OUTPUT,0," ");
    var = newCVar(&func->state  ,fucname + ".state",C_OUTPUT,0," ");
    var = newCVar(&func->aborted  ,fucname + ".aborted",C_OUTPUT,0," ");
    var = newCVar(&func->errorCode  ,fucname + ".errorCode",C_OUTPUT,0," ");


    ui->fAcc->setVar(fucname + ".fAcc");
    ui->fDec->setVar(fucname + ".fDec");
    ui->fVel->setVar(fucname + ".fVel");
    ui->fJerk->setVar(fucname + ".fJerk");
    ui->negative->setVar(fucname + ".negative");
    ui->positive->setVar(fucname + ".positive");
    ui->busy->setVar(fucname + ".busy");
    ui->done->setVar(fucname + ".done");
    ui->error->setVar(fucname + ".error");
    //ui->state->setVar(fucname + ".state");
    ui->aborted->setVar(fucname + ".aborted");
    ui->errorCode->setVar(fucname + ".errorCode");

    return 0;
}
jmcJogWidget::~jmcJogWidget()
{
    delete ui;
}
