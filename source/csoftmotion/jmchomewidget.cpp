#include "include/csoftmotion/jmchomewidget.h"
#include "ui_jmchomewidget.h"

jmcHomeWidget::jmcHomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jmcHomeWidget)
{
    ui->setupUi(this);
}

jmcHomeWidget::~jmcHomeWidget()
{
    delete ui;
}
int jmcHomeWidget::init(QString fucname , JMC_Home_Drv *func)
{

    cBaseVar *var = nullptr;
//    JMC_JOG jog;
    var = newCVar(&func->Execute  ,fucname + ".Execute",C_INPUT,0," ");
    var = newCVar(&func->fTimeOut  ,fucname + ".fTimeOut",C_INPUT,0," ");
    var = newCVar(&func->busy  ,fucname + ".busy",C_OUTPUT,0," ");
    var = newCVar(&func->done  ,fucname + ".done",C_OUTPUT,0," ");
    var = newCVar(&func->error  ,fucname + ".error",C_OUTPUT,0," ");
    var = newCVar(&func->state  ,fucname + ".state",C_OUTPUT,0," ");
    var = newCVar(&func->aborted  ,fucname + ".aborted",C_OUTPUT,0," ");
    var = newCVar(&func->errorCode  ,fucname + ".errorCode",C_OUTPUT,0," ");

    ui->Execute->setVar(fucname + ".Execute");
    ui->fTimeOut->setVar(fucname + ".fTimeOut");
    ui->busy->setVar(fucname + ".busy");
    ui->done->setVar(fucname + ".done");
    ui->error->setVar(fucname + ".error");
    //ui->state->setVar(fucname + ".state");
    ui->aborted->setVar(fucname + ".aborted");
    ui->errorCode->setVar(fucname + ".errorCode");





    return 0;
}
