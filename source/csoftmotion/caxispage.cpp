#include "include/csoftmotion/caxispage.h"
#include "ui_caxispage.h"


#include <QVector>

#include "include/cwidget/cresdock.h"

cAxisPage::cAxisPage(QWidget *parent) :
    cBasePage(parent),
    ui(new Ui::cAxisPage)
{
    ui->setupUi(this);

}

int cAxisPage::init(QString name, void* arg)
{
    axis = (axis_ref *)arg;
    if(axis == nullptr){
        return -1;
    }


    cBaseVar *var = nullptr;

    var = newCVar(&axis->axNo ,name + ".axNo",C_OUTPUT,0," ");
    var = newCVar(&axis->pdoNo ,name + ".pdoNo",C_OUTPUT,0," ");
    var = newCVar(&axis->state ,name + ".state",C_OUTPUT,0," ");
    var = newCVar(&axis->dinput ,name + ".dinput",C_OUTPUT,0," ");
    var = newCVar(&axis->xError ,name + ".xError",C_OUTPUT,0," ");
    var = newCVar(&axis->bindEtc ,name + ".bindEtc",C_OUTPUT,0," ");
    var = newCVar(&axis->fActAcc ,name + ".fActAcc",C_OUTPUT,0," ");
    var = newCVar(&axis->fActVel ,name + ".fActVel",C_OUTPUT,0," ");
    var = newCVar(&axis->fActPos ,name + ".fActPos",C_OUTPUT,0," ");
    var = newCVar(&axis->sActTorque ,name + ".sActTorque",C_OUTPUT,0," ");
    var = newCVar(&axis->fSetAcc ,name + ".fSetAcc",C_OUTPUT,0," ");
    var = newCVar(&axis->fSetVel ,name + ".fSetVel",C_OUTPUT,0," ");
    var = newCVar(&axis->fSetPos ,name + ".fSetPos",C_OUTPUT,0," ");
    var = newCVar(&axis->fSetTorque ,name + ".fSetTorque",C_OUTPUT,0," ");
    var = newCVar(&axis->errorcode ,name + ".errorcode",C_OUTPUT,0," ");
    var = newCVar(&axis->modes_of_operation_display ,name + ".modes_of_operation_display",C_OUTPUT,0," ");
    var = newCVar(&axis->following_error_actual_value ,name + ".following_error_actual_value",C_OUTPUT,0," ");
    var = newCVar(&axis->wCommunicationState ,name + ".wCommunicationState",C_OUTPUT,0," ");
    var = newCVar(&axis->digital_outputs ,name + ".digital_outputs",C_OUTPUT,0," ");
    var = newCVar(&axis->xCommunication ,name + ".xCommunication",C_OUTPUT,0," ");
    var = newCVar(&axis->fETC_CycleTime ,name + ".fETC_CycleTime",C_OUTPUT,0," ");
    var = newCVar(&axis->target_mode ,name + ".target_mode",C_OUTPUT,0," ");
    var = newCVar(&axis->syncState ,name + ".syncState",C_OUTPUT,0," ");
    var = newCVar(&axis->status_word ,name + ".status_word",C_OUTPUT,0," ");






//    JMC_Power power;
//    var = newCVar(&power.xPOn  ,name + ".power.xPOn",C_INPUT,0," ");
//    var = newCVar(&power.xDStart  ,name + ".power.xDStart",C_INPUT,0," ");
//    var = newCVar(&power.xInPower  ,name + ".power.xInPower",C_OUTPUT,0," ");
//    var = newCVar(&power.busy  ,name + ".power.busy",C_OUTPUT,0," ");
//    var = newCVar(&power.done  ,name + ".power.done",C_OUTPUT,0," ");
//    var = newCVar(&power.error  ,name + ".power.error",C_OUTPUT,0," ");
//    var = newCVar(&power.errorCode  ,name + ".power.errorCode",C_OUTPUT,0," ");
    ui->power->init(name + ".power",&power);
    //var = newCVar(&power.actNo  ,name + ".power.actNo",C_OUTPUT,0," ");
//    JMC_Stop stop;
//    var = newCVar(&stop.fDec  ,name + ".stop.fDec",C_INPUT,0," ");
//    var = newCVar(&stop.fJerk  ,name + ".stop.fJerk",C_INPUT,0," ");
//    var = newCVar(&stop.Execute  ,name + ".stop.Execute",C_INPUT,0," ");
//    var = newCVar(&stop.busy  ,name + ".stop.busy",C_OUTPUT,0," ");
//    var = newCVar(&stop.done  ,name + ".stop.done",C_OUTPUT,0," ");
//    var = newCVar(&stop.error  ,name + ".stop.error",C_OUTPUT,0," ");
//    var = newCVar(&stop.state  ,name + ".stop.state",C_OUTPUT,0," ");
//    var = newCVar(&stop.aborted  ,name + ".stop.aborted",C_OUTPUT,0," ");
//    var = newCVar(&stop.errorCode  ,name + ".stop.errorCode",C_OUTPUT,0," ");
    ui->jmcstop->init(name + ".stop",&stop);


//    JMC_JOG jog;
//    var = newCVar(&jog.fAcc  ,name + ".jog.fAcc",C_INPUT,0," ");
//    var = newCVar(&jog.fDec  ,name + ".jog.fDec",C_INPUT,0," ");
//    var = newCVar(&jog.fVel  ,name + ".jog.fVel",C_INPUT,0," ");
//    var = newCVar(&jog.fJerk  ,name + ".jog.fJerk",C_INPUT,0," ");
//    var = newCVar(&jog.negative  ,name + ".jog.negative",C_INPUT,0," ");
//    var = newCVar(&jog.positive  ,name + ".jog.positive",C_INPUT,0," ");
//    var = newCVar(&jog.busy  ,name + ".jog.busy",C_OUTPUT,0," ");
//    var = newCVar(&jog.done  ,name + ".jog.done",C_OUTPUT,0," ");
//    var = newCVar(&jog.error  ,name + ".jog.error",C_OUTPUT,0," ");
//    var = newCVar(&jog.state  ,name + ".jog.state",C_OUTPUT,0," ");
//    var = newCVar(&jog.aborted  ,name + ".jog.aborted",C_OUTPUT,0," ");
//    var = newCVar(&jog.errorCode  ,name + ".jog.errorCode",C_OUTPUT,0," ");
    ui->jog->init(name + ".jog",&jog);

//    JMC_Reset reset;
//    var = newCVar(&reset.Execute  ,name + ".reset.Execute",C_INPUT,0," ");
//    var = newCVar(&reset.busy  ,name + ".reset.busy",C_OUTPUT,0," ");
//    var = newCVar(&reset.done  ,name + ".reset.done",C_OUTPUT,0," ");
//    var = newCVar(&reset.error  ,name + ".reset.error",C_OUTPUT,0," ");
//    var = newCVar(&reset.state  ,name + ".reset.state",C_OUTPUT,0," ");
//    var = newCVar(&reset.errorCode  ,name + ".reset.errorCode",C_OUTPUT,0," ");
    ui->jmcreset->init(name + ".reset",&reset);



//    JMC_SetPos setpos;
//    var = newCVar(&setpos.fPos  ,name + ".setpos.fPos",C_INPUT,0," ");
//    var = newCVar(&setpos.Execute  ,name + ".setpos.Execute",C_INPUT,0," ");
//    var = newCVar(&setpos.busy  ,name + ".setpos.busy",C_OUTPUT,0," ");
//    var = newCVar(&setpos.done  ,name + ".setpos.done",C_OUTPUT,0," ");
//    var = newCVar(&setpos.error  ,name + ".setpos.error",C_OUTPUT,0," ");
//    var = newCVar(&setpos.state  ,name + ".setpos.state",C_OUTPUT,0," ");
//    var = newCVar(&setpos.aborted  ,name + ".setpos.aborted",C_OUTPUT,0," ");
//    var = newCVar(&setpos.errorCode  ,name + ".setpos.errorCode",C_OUTPUT,0," ");
    ui->jmcsetpos->init(name + ".setpos",&setpos);


//    JMC_MoveAbs moveabs;
//    var = newCVar(&moveabs.fPos  ,name + ".moveabs.fPos",C_INPUT,0," ");
//    var = newCVar(&moveabs.fAcc  ,name + ".moveabs.fAcc",C_INPUT,0," ");
//    var = newCVar(&moveabs.fDec  ,name + ".moveabs.fDec",C_INPUT,0," ");
//    var = newCVar(&moveabs.fPos  ,name + ".moveabs.fPos",C_INPUT,0," ");
//    var = newCVar(&moveabs.fVel  ,name + ".moveabs.fVel",C_INPUT,0," ");
//    var = newCVar(&moveabs.fJerk  ,name + ".moveabs.fJerk",C_INPUT,0," ");
//    var = newCVar(&moveabs.Execute  ,name + ".moveabs.Execute",C_INPUT,0," ");
//    var = newCVar(&moveabs.done  ,name + ".moveabs.done",C_OUTPUT,0," ");
//    var = newCVar(&moveabs.busy  ,name + ".moveabs.busy",C_OUTPUT,0," ");
//    var = newCVar(&moveabs.aborted  ,name + ".moveabs.aborted",C_OUTPUT,0," ");
//    var = newCVar(&moveabs.error  ,name + ".moveabs.error",C_OUTPUT,0," ");
//    var = newCVar(&moveabs.state  ,name + ".moveabs.state",C_OUTPUT,0," ");
//    var = newCVar(&moveabs.errorCode  ,name + ".moveabs.errorCode",C_OUTPUT,0," ");
    ui->moveabs->init(name + ".moveabs",&moveabs);

//    JMC_MoveVel movevel;
//    var = newCVar(&movevel.fAcc  ,name + ".movevel.fAcc",C_INPUT,0," ");
//    var = newCVar(&movevel.fDec  ,name + ".movevel.fDec",C_INPUT,0," ");
//    var = newCVar(&movevel.fVel  ,name + ".movevel.fVel",C_INPUT,0," ");
//    var = newCVar(&movevel.fJerk  ,name + ".movevel.fJerk",C_INPUT,0," ");
//    var = newCVar(&movevel.invel  ,name + ".movevel.invel",C_OUTPUT,0," ");
//    var = newCVar(&movevel.Execute  ,name + ".movevel.Execute",C_INPUT,0," ");
//    var = newCVar(&movevel.done  ,name + ".movevel.done",C_OUTPUT,0," ");
//    var = newCVar(&movevel.busy  ,name + ".movevel.busy",C_OUTPUT,0," ");
//    var = newCVar(&movevel.aborted  ,name + ".movevel.aborted",C_OUTPUT,0," ");
//    var = newCVar(&movevel.error  ,name + ".movevel.error",C_OUTPUT,0," ");
//    var = newCVar(&movevel.state  ,name + ".movevel.state",C_OUTPUT,0," ");
//    var = newCVar(&movevel.errorCode  ,name + ".movevel.errorCode",C_OUTPUT,0," ");
    ui->movevel->init(name + ".movevel",&movevel);

//    JMC_WTMC_TC wtmctc;
//    var = newCVar(&wtmctc.cmode  ,name + ".wtmctc.cmode",C_INPUT,0," ");
//    var = newCVar(&wtmctc.Execute  ,name + ".wtmctc.Execute",C_INPUT,0," ");
//    var = newCVar(&wtmctc.done  ,name + ".wtmctc.done",C_OUTPUT,0," ");
//    var = newCVar(&wtmctc.busy  ,name + ".wtmctc.busy",C_OUTPUT,0," ");
//    var = newCVar(&wtmctc.aborted  ,name + ".wtmctc.aborted",C_OUTPUT,0," ");
//    var = newCVar(&wtmctc.error  ,name + ".wtmctc.error",C_OUTPUT,0," ");
//    var = newCVar(&wtmctc.state  ,name + ".wtmctc.state",C_OUTPUT,0," ");
//    var = newCVar(&wtmctc.errorCode  ,name + ".wtmctc.errorCode",C_OUTPUT,0," ");
    ui->jmccc->init(name + ".wtmctc",&wtmctc);

//    JMC_Home_Drv homedrv;
//    var = newCVar(&homedrv.Execute  ,name + ".homedrv.Execute",C_INPUT,0," ");
//    var = newCVar(&homedrv.fTimeOut  ,name + ".homedrv.fTimeOut",C_INPUT,0," ");
//    var = newCVar(&homedrv.done  ,name + ".homedrv.done",C_OUTPUT,0," ");
//    var = newCVar(&homedrv.busy  ,name + ".homedrv.busy",C_OUTPUT,0," ");
//    var = newCVar(&homedrv.aborted  ,name + ".homedrv.aborted",C_OUTPUT,0," ");
//    var = newCVar(&homedrv.error  ,name + ".homedrv.error",C_OUTPUT,0," ");
//    var = newCVar(&homedrv.state  ,name + ".homedrv.state",C_OUTPUT,0," ");
//    var = newCVar(&homedrv.errorCode  ,name + ".homedrv.errorCode",C_OUTPUT,0," ");
    ui->jmchome->init(name + ".homedrv",&homedrv);


//    JMC_MoveReal movereal;
//    var = newCVar(&movereal.fAcc  ,name + ".movereal.fAcc",C_INPUT,0," ");
//    var = newCVar(&movereal.fDec  ,name + ".movereal.fDec",C_INPUT,0," ");
//    var = newCVar(&movereal.fPos  ,name + ".movereal.fPos",C_INPUT,0," ");
//    var = newCVar(&movereal.fVel  ,name + ".movereal.fVel",C_INPUT,0," ");
//    var = newCVar(&movereal.fJerk  ,name + ".movereal.fJerk",C_INPUT,0," ");
//    var = newCVar(&movereal.Execute  ,name + ".movereal.Execute",C_INPUT,0," ");
//    var = newCVar(&movereal.done  ,name + ".movereal.done",C_OUTPUT,0," ");
//    var = newCVar(&movereal.busy  ,name + ".movereal.busy",C_OUTPUT,0," ");
//    var = newCVar(&movereal.aborted  ,name + ".movereal.aborted",C_OUTPUT,0," ");
//    var = newCVar(&movereal.error  ,name + ".movereal.error",C_OUTPUT,0," ");
//    var = newCVar(&movereal.state  ,name + ".movereal.state",C_OUTPUT,0," ");
//    var = newCVar(&movereal.errorCode  ,name + ".movereal.errorCode",C_OUTPUT,0," ");


    _10msTimer.setInterval(10);
    connect(&_10msTimer,&QTimer::timeout,this,&cAxisPage::_10msSlots);
    _10msTimer.start();
    return 0;
}


void cAxisPage::_10msSlots()
{
    if(axis == nullptr){
        return;
    }
    power.call(axis);
    stop.call(axis);
    jog.call(axis);
    reset.call(axis);
    setpos.call(axis);
    moveabs.call(axis);
    movevel.call(axis);
    wtmctc.call(axis);
    homedrv.call(axis);
//    movereal.call(axis);
}
int cAxisPage::conf(QString name,QJsonObject confObj)
{
    return 0;
}


int cAxisPage::beforDB()
{
     return 0;
}
int cAxisPage::afterDB()
{
     return 0;
}

int cAxisPage::beforDelete()
{
     return 0;
}


cBasePage *cAxisPage::getNewPage()
{
    cAxisPage *page = new cAxisPage();
    return page;
}

cAxisPage::~cAxisPage()
{
    delete ui;
}
