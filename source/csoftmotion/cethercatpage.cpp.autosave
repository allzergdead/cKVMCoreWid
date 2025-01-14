#include "include/csoftmotion/cethercatpage.h"
#include "ui_cethercatpage.h"

#include <QVector>

#include "include/cwidget/cresdock.h"

cEtherCATPage::cEtherCATPage(QWidget *parent) :
    cBasePage(parent),
    ui(new Ui::cEtherCATPage)
{
    ui->setupUi(this);
    //ui->ETCTab->setTabsClosable(true);

    // 启用滚动功能
    //ui->ETCTab->tabBar()->setUsesScrollButtons(true); // 启用滚动按钮

    tabWidInertScroll(ui->ETCTab);

}

cEtherCATPage::~cEtherCATPage()
{

    delete ui;
}
int cEtherCATPage::init(QString name, void* arg)
{



    if(etcmem != nullptr){
        try{
            cBaseVar *var = nullptr;

            var =newCVar(&test,name + ".test",C_OUTPUT,0,"xxx");

            var =newCVar(&etcmem->ecNo,name + ".ecNo",C_OUTPUT,0,"主站编号");
            var = newCVar(&etcmem->pdoSize,name + ".pdoSize",C_OUTPUT,0,"从站总数");
            var = newCVar(&etcmem->axis_Num,name + ".axis_Num",C_OUTPUT,0,"轴总数");
            var = newCVar(&etcmem->etc_state,name + ".etc_state",C_OUTPUT,0,"主站状态");
            var = newCVar(&etcmem->cycle,name + ".cycle",C_OUTPUT,0,"EtherCAT周期");
            var = newCVar(&etcmem->etc_task_counter,name + ".etc_task_counter",C_OUTPUT,0,"主站循环次数统计");

            var = newCVar(&etcmem->task_info.cpu,name + ".task_info.cpu",C_OUTPUT,0,"EtherCAT绑定核心");
            var = newCVar(&etcmem->task_info.clear,name + ".task_info.clear",C_INPUT,0,"清空计数");
            var = newCVar(&etcmem->task_info.task_cost,name + ".task_info.task_cost",C_OUTPUT,0,"最新执行耗时");
            var = newCVar(&etcmem->task_info.task_period,name + ".task_info.task_period",C_OUTPUT,0,"最新周期");
            var = newCVar(&etcmem->task_info.task_countor,name + ".task_info.task_countor",C_OUTPUT,0,"周期数统计");
            var = newCVar(&etcmem->task_info.task_cost_avg,name + ".task_info.task_cost_avg",C_OUTPUT,0,"平均耗时");
            var = newCVar(&etcmem->task_info.task_cost_max,name + ".task_info.task_cost_max",C_OUTPUT,0,"最大耗时");
            var = newCVar(&etcmem->task_info.task_cost_min,name + ".task_info.task_cost_min",C_OUTPUT,0,"最小耗时");
            var = newCVar(&etcmem->task_info.task_cost_sum,name + ".task_info.task_cost_sum",C_OUTPUT,0,"总耗时时间");
            var = newCVar(&etcmem->task_info.task_period_avg,name + ".task_info.task_period_avg",C_OUTPUT,0,"平均周期");
            var = newCVar(&etcmem->task_info.task_period_max,name + ".task_info.task_period_max",C_OUTPUT,0,"最大周期");
            var = newCVar(&etcmem->task_info.task_period_min,name + ".task_info.task_period_min",C_OUTPUT,0,"最小周期");
            var = newCVar(&etcmem->task_info.task_period_sum,name + ".task_info.task_period_sum",C_OUTPUT,0,"总周期时间");




            ui->ecNo->setVar(name + ".ecNo");
            ui->pdoSize->setVar(name + ".pdoSize");
            ui->axis_Num->setVar(name + ".axis_Num");
            ui->etc_state->setVar(name + ".etc_state");
            ui->cycle->setVar(name + ".cycle");
            ui->etc_task_counter->setVar(name + ".etc_task_counter");

            ui->cpu->setVar(name + ".task_info.cpu");
            ui->clear->setVar(name + ".task_info.clear");
            //ui->clear->setVar(name + ".test");
            ui->clear->setBtn();
            ui->task_cost->setVar(name + ".task_info.task_cost");
            ui->task_period->setVar(name + ".task_info.task_period");
            ui->task_countor->setVar(name + ".task_info.task_countor");
            ui->task_cost_avg->setVar(name + ".task_info.task_cost_avg");
            ui->task_cost_max->setVar(name + ".task_info.task_cost_max");
            ui->task_cost_min->setVar(name + ".task_info.task_cost_min");
            ui->task_cost_sum->setVar(name + ".task_info.task_cost_sum");
            ui->task_period_avg->setVar(name + ".task_info.task_period_avg");
            ui->task_period_max->setVar(name + ".task_info.task_period_max");
            ui->task_period_min->setVar(name + ".task_info.task_period_min");
            ui->task_period_sum->setVar(name + ".task_info.task_period_sum");
        }catch(QString error){

        }

    }


    return 0;
}



int cEtherCATPage::conf(QString name,QJsonObject confObj)
{
    // 这里由confObj来确认是第几个Etc口
    etcmem = getEtcPtr();
    if(resDock == nullptr){
        return 0;
    }

    //QJsonObject Slaves = res->getResObj(u8"ETCMasters.EtherCAT0.Slaves", u8"slavepdo.png", u8"");
    //QJsonObject Axes = res->getResObj(u8"ETCMasters.EtherCAT0.Axes", u8"axis.png", u8"");


    cResDock *fatherDock = (cResDock *)resDock;
    fatherDock->insertPage(name + ".Slaves",u8"slavepdo.png",u8"",nullptr);
    for(int i = 0 ; i < etcmem->pdo_Num;i++){
        QString pdoName = etcmem->pdoconf[i].slaveName;
        fatherDock->insertPage(name + ".Slaves." + pdoName,u8"slavepdo.png",u8"",&etcmem->pdoconf[i]);
    }
    fatherDock->insertPage(name + ".Axes",u8"axis.png",u8"",nullptr);
    for(int i = 0 ; i < etcmem->axis_Num;i++){
        QString pdoName = etcmem->axis[i].name;
        fatherDock->insertPage(name + ".Axes." + pdoName,u8"axis.png",u8"Axis",&etcmem->axis[i]);
    }



    return 0;
}


int cEtherCATPage::beforDB()
{
     return 0;
}
int cEtherCATPage::afterDB()
{
     return 0;
}

int cEtherCATPage::beforDelete()
{
     return 0;
}


cBasePage *cEtherCATPage::getNewPage()
{
    cEtherCATPage *page = new cEtherCATPage();
    return page;
}

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>
#include <malloc.h>

#ifdef __linux
#include <QProcess>
#include <QString>
#include <QDebug>
void executeCommand(QString cmdstr) {
    QProcess process;
    process.start(cmdstr); // 执行 Linux 命令
    process.waitForFinished(); // 等待命令执行完成
    QString output = process.readAllStandardOutput(); // 获取标准输出
    QString error = process.readAllStandardError();   // 获取错误输出

    qDebug() << "Command Output:" << output;
    qDebug() << "Command Error:" << error;
}
    cec_shm_pdo *cEtherCATPage::getEtcPtr()
    {
        int ETCfd = 0;
        std::stringstream path;
        //path << "/dev/shm/vm_shared/shared_memory";
         path << "/mnt/ramdisk/etc_read";
        ::close(ETCfd);
        ETCfd = open(path.str().c_str(), O_RDWR);
        //qDebug() << QString::fromStdString(path.str()) << "lsfd-"<< i << "="<< lsfd[i];
        if (ETCfd < 0){
            ::close(ETCfd);
            //executeCommand("sudo dd if=/dev/zero of=/dev/shm/etc_read bs=1M count=10");
            ETCfd = open("/dev/shm/etc_read", O_RDWR);
            if(ETCfd < 0){
                return nullptr;
            }

        }
        void *etcmem;
        etcmem = static_cast<void *>(mmap(NULL,ETC_SHM_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,ETCfd,0));
        if ((ulong)etcmem == 0xffffffffffffffff){
            ::close(ETCfd);
            return nullptr;
        }else{
            return (cec_shm_pdo *)etcmem;
        }
    }
    cec_shm_pdo *cEtherCATPage::getEtcPtr(int i)
    {
        int ETCfd = 0;
        std::stringstream path;
        //path << "/dev/shm/vm_shared/shared_memory";
         path << "/mnt/ramdisk/etc_read";
        ::close(ETCfd);
        ETCfd = open(path.str().c_str(), O_RDWR);
        //qDebug() << QString::fromStdString(path.str()) << "lsfd-"<< i << "="<< lsfd[i];
        if (ETCfd < 0){
            ::close(ETCfd);
            if(ETCfd < 0){
                return nullptr;
            }
            return nullptr;
        }
        void *etcmem;
        etcmem = static_cast<void *>(mmap(NULL,ETC_SHM_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,ETCfd,0));
        if ((ulong)etcmem == 0xffffffffffffffff){
            ::close(ETCfd);
            return nullptr;
        }else{
            return (cec_shm_pdo *)etcmem;
        }
    }

#elif
#endif


