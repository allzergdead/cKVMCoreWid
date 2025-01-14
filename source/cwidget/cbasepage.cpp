#include "include/cwidget/cbasepage.h"
#include "ui_cbasepage.h"


cBasePage::cBasePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cBasePage)
{
    ui->setupUi(this);

    // 使用 QScrollArea 包裹内容
    scrollArea = new QScrollArea();
    //scrollArea->setWidget(this);
    //scrollArea->setWidgetResizable(true); // 自动调整内容大小
}

cBasePage::~cBasePage()
{
    delete ui;
}
int cBasePage::init(QString name, void* arg)
{
    return 0;
}



int cBasePage::conf(QString name,QJsonObject confObj)
{
    // 这里先直接读取EtherCAT0接口，后续支持多接口再改



    return 0;
}


int cBasePage::beforDB()
{
     return 0;
}
int cBasePage::afterDB()
{
     return 0;
}

int cBasePage::beforDelete()
{
     return 0;
}

int cBasePage::mkIfNoDir(QString path)
{
    QDir dir(path);
    if (!dir.exists()) {
        bool ok = dir.mkpath(path);
        if (ok) {
             return 0;
        } else {
            cBaseVar::insertLog(-99,u8"路径管理",u8"路径 " + path + u8" 创建失败");
            return -1;
        }
    } else {
           return 0;
    }
}
int cBasePage::mkIfNoFile(QString path)
{
    QFile file(path);

    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly)) {

            file.close();
            return 0;
        } else {
            cBaseVar::insertLog(-99,u8"路径管理",u8"文件 " + path + u8" 创建失败");
            return -1;
        }
    } else {
        return 0;
    }
}
int cBasePage::getQJsonObjFromFile(QString filePath , QJsonArray *obj)
{
    QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            //qDebug() << "无法打开文件：" << filePath << file.errorString();
            cBaseVar::insertLog(-99,u8"JSON解析器",u8"无法打开文件： " + filePath + u8" " + file.errorString());
            return -1;
        }

        // 读取文件所有内容
        QByteArray fileData = file.readAll();
        file.close();

        // 使用 QJsonDocument 进行解析
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            //qDebug() << "JSON 解析失败：" << parseError.errorString();
            cBaseVar::insertLog(-99,u8"JSON解析器",u8"解析 " + filePath + u8"失败 " + parseError.errorString());
            return -2;
        }

        // 判断是否为 JSON 对象
        if (!jsonDoc.isArray()) {
            //qDebug() << "当前 JSON 不是对象结构";
            cBaseVar::insertLog(-99,u8"JSON解析器",u8"当前 JSON 不是对象结构  " + filePath);
            return -3;
        }

        // 获取顶层对象
        *obj = jsonDoc.array();


        return 0;
}
void  cBasePage::tabWidInertScroll(QTabWidget *tab)
{
    struct scorInfoP{
        QScrollArea *scor = nullptr;
        QString name = "";
    };
    QVector<scorInfoP> scorVec;
    for(int i = 0; i < tab->count();i++){
        scorInfoP scorInfo;
        scorInfo.scor = new QScrollArea();
        scorInfo.name = tab->tabText(i);


        // 获取原页面内容
        QWidget *originalPage = tab->widget(i);

        // 设置固定大小，确保内容超出可见区域
        originalPage->setMinimumSize(originalPage->size().width() + 900, originalPage->size().height() + 200); // 强制内容比 QScrollArea 大
        scorInfo.scor->setWidget(originalPage);

        scorInfo.scor->setWidgetResizable(true); // 自动调整大小
        scorInfo.scor->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scorInfo.scor->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        tab->removeTab(i);
        tab->insertTab(i,scorInfo.scor,scorInfo.name);

    }
}
