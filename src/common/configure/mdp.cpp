#include "mdp.h"
#include <QDebug>


mdp::mdp(QWidget *parent):QDialog(parent)
{
    setupUi(this);
    qWarning() << __FILE__ << QString::number(__LINE__) << "get the mysql connection datas" ;
    userEdit->setText("root");
    hostEdit->setText("localhost");
    portEdit->setText("3306");
    passEdit   -> setFocus();
}

mdp::~mdp(){}

QString mdp::mdpLogin()
{
    return userEdit->text();
}
QString mdp::mdpPassword()
{
    return passEdit->text();
}
QString mdp::mdpHost()
{
    return hostEdit->text();
}

QString mdp::mdpPort()
{
    return portEdit->text();
}

void mdp::disableEdits()
{
    userEdit->setEnabled(false);
    hostEdit->setEnabled(false);
    portEdit->setEnabled(false);
}
