#include "include/csoftmotion/jmcmoveabswdiget.h"
#include "ui_jmcmoveabswdiget.h"

jmcMoveAbsWdiget::jmcMoveAbsWdiget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jmcMoveAbsWdiget)
{
    ui->setupUi(this);
}

jmcMoveAbsWdiget::~jmcMoveAbsWdiget()
{
    delete ui;
}
int jmcMoveAbsWdiget::init(QString fucname , JMC_MoveAbs *func)
{

    cBaseVar *var = nullptr;
//    JMC_MoveAbs moveabs
    var = newCVar(&func->Execute  ,fucname + ".Execute",C_INPUT,0," ");
    var = newCVar(&func->fPos  ,fucname + ".fPos",C_INPUT,0," ");
    var = newCVar(&func->fAcc  ,fucname + ".fAcc",C_INPUT,0," ");
    var = newCVar(&func->fDec  ,fucname + ".fDec",C_INPUT,0," ");
    var = newCVar(&func->fVel  ,fucname + ".fVel",C_INPUT,0," ");
    var = newCVar(&func->fJerk  ,fucname + ".fJerk",C_INPUT,0," ");
    var = newCVar(&func->busy  ,fucname + ".busy",C_OUTPUT,0," ");
    var = newCVar(&func->done  ,fucname + ".done",C_OUTPUT,0," ");
    var = newCVar(&func->error  ,fucname + ".error",C_OUTPUT,0," ");
    var = newCVar(&func->state  ,fucname + ".state",C_OUTPUT,0," ");
    var = newCVar(&func->aborted  ,fucname + ".aborted",C_OUTPUT,0," ");
    var = newCVar(&func->errorCode  ,fucname + ".errorCode",C_OUTPUT,0," ");

    ui->Execute->setVar(fucname + ".Execute");
    ui->Execute->setBtnType(forcePressType::PRESS_RESET);
    ui->fPos->setVar(fucname + ".fPos");
    ui->fAcc->setVar(fucname + ".fAcc");
    ui->fDec->setVar(fucname + ".fDec");
    ui->fVel->setVar(fucname + ".fVel");
    ui->fJerk->setVar(fucname + ".fJerk");
    ui->busy->setVar(fucname + ".busy");
    ui->done->setVar(fucname + ".done");
    ui->error->setVar(fucname + ".error");
    //ui->state->setVar(fucname + ".state");
    ui->aborted->setVar(fucname + ".aborted");
    ui->errorCode->setVar(fucname + ".errorCode");

    return 0;
}
