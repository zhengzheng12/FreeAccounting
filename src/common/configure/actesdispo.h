#ifndef ACTESDISPO_H
#define ACTESDISPO_H

#include <QtCore>
#include <QtGui>
#include <QtSql>

#include "ui_actesdispodialog.h"
class actesdispo:public QWidget,public Ui::ActesdispoDialog
{
    Q_OBJECT

    public:
        actesdispo(QWidget * parent);
        ~actesdispo();
        QSqlDatabase m_db;
    protected slots :
        void enregistreacte();
        void add();
        void deleteact();
        void on_totalValueEdit_textChanged(const QString & text);
        void fillLabelsAndCombo(const QString & act);
        void fillactsComboBox(const QString & actsComboText);
        QString getcodenamebytablenumber();
        QString getfieldsfromtablenumber();
    private:
        void filltypecombobox();
        bool insertintable(int tablenumber=0,const QString & act = QString(),const QString & description = QString(),const QString & type = QString(),
                                           const QString & valeurtotale = QString(),const QString & date = QString());
;
        QString nameofcode(const QString & table);
        QStringList m_listNGAP;
        QMap <int,QStringList> m_mapNGAP;
        QHash<int,QString> m_hashtypetable;
        QHash<QString,QString> m_hashtablename;
        QString m_reimbursment_AMO;
};



#endif
