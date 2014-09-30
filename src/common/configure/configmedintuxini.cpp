#include "configmedintuxini.h"
#include "medintux/constants_medintux.h"

#include <QSettings>
#include <QDir>
#include <QMessageBox>

using namespace ConstantsMedintuxSpace;

static inline QSettings * settings()
{
    QSettings * set = new QSettings(QDir::homePath()+"/.rapidcomptamednew/config_medintux.ini",QSettings::IniFormat);
    return set;
}

ConfigMedintuxIni::ConfigMedintuxIni(QWidget * parent)
{
    setupUi(this);
    settingWidgetDatas();
    connect(recordButton,SIGNAL(pressed()),this,SLOT(writeWidgetNewDatasInIniFile())); 
    connect(quitButton,SIGNAL(pressed()),this,SLOT(close()));    
}

ConfigMedintuxIni::~ConfigMedintuxIni(){}

void ConfigMedintuxIni::settingWidgetDatas()
{
    medintuxBaseEdit->setText(settings()->value(DRTUXBASE).toString());
    hostEdit->setText(settings()->value(DRTUX_HOST).toString());
    loginEdit->setText(settings()->value(DRTUX_LOGIN).toString());
    portEdit->setText(settings()->value(DRTUX_PORT).toString());
    passEdit->setText(settings()->value(DRTUX_PASSWORD).toString());
    driverEdit->setText(settings()->value(DRTUX_DRIVER).toString());
    medintuxTableIndexEdit->setText(settings()->value(DRTUX_INDEXNOMPRENOM).toString());
}

void ConfigMedintuxIni::writeWidgetNewDatasInIniFile()
{
    settings()->setValue(DRTUXBASE,medintuxBaseEdit->text()); 
    settings()->setValue(DRTUX_HOST,hostEdit->text());
    settings()->setValue(DRTUX_LOGIN,loginEdit->text());
    settings()->setValue(DRTUX_PORT,portEdit->text());
    settings()->setValue(DRTUX_PASSWORD,passEdit->text());
    settings()->setValue(DRTUX_DRIVER,driverEdit->text());
    settings()->setValue(DRTUX_INDEXNOMPRENOM,medintuxTableIndexEdit->text());
    QMessageBox::information(0,tr("Information"),tr("config_medintux a été renseigné."),QMessageBox::Ok);
}





