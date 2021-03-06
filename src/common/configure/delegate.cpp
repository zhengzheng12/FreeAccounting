#include "delegate.h"
#include "tablesdiagrams.h"
#include "diversblob.h"
#include <common/constants.h>
#include <common/configure/iotools.h>

#include <QComboBox>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

using namespace Common;
using namespace Constants;
using namespace SitesDiagrams;
using namespace PayeursDiagrams;
using namespace DiversBlobs;
using namespace Tokens;
using namespace FacturationSpace;


ComboDelegate::ComboDelegate(QObject * parent, const QString & table)
 {
     Q_UNUSED(parent);
     m_table = table;
}

ComboDelegate::~ComboDelegate(){}

QSize ComboDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                              const QModelIndex & index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(40,50);
}

QWidget *ComboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
   if ( index.column() == PayeursDiagrams::DIVERS_PAYEURS || index.column() == SitesDiagrams::DIVERS)
    {
   	  QComboBox * combo = new QComboBox(parent);
    	  return combo;
        }
   return QStyledItemDelegate::createEditor(parent, option, index);
}

void ComboDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     QComboBox * combo = static_cast<QComboBox*>(editor);
     combo->setEditable(true);
     QModelIndex indexin = index;
     QHash<QString,QString> hashOfTokensInBlob = diversblobsList(m_table,indexin);
     QHash<QString,QString>::iterator it;
     if (index.column() == PayeursDiagrams::DIVERS_PAYEURS)
     {
         for (it = hashOfTokensInBlob.begin(); it != hashOfTokensInBlob.end(); ++it)
         {
             QString item = it.key()+":"+it.value();
             combo->addItem(item);
             }
         }
}
 
void ComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
     enum {KEYNAME=0,VALUE};
     QComboBox * combo = static_cast<QComboBox*>(editor);
     TokensClass tk;
     QString text = combo->currentText();
     QStringList listtext;
     listtext = text.split(":");
     QString keyName;
     QString value;
     if (listtext.size()>1)
     {
           keyName = listtext[KEYNAME];
           value = listtext[VALUE];
         }
      QString tokenbegin = tk.hashTokensNames().key(keyName);
      QString tokenend = tk.hashTokensForBlobs().value(tk.hashTokensNames().key(keyName));
      QString realvalue = tokenbegin+value+tokenend;
      QString olddata = model->data(index,Qt::DisplayRole).toString();
      tokenbegin.replace("[","\\[");
      tokenbegin.replace("]","\\]");
      tokenend.replace("[","\\[");
      tokenend.replace("]","\\]");
      QRegExp olditemexpr = QRegExp(tokenbegin+"\\w+"+tokenend);
      olddata.replace(olditemexpr,realvalue);
      QString totalvalue = olddata;
      model->setData(index, totalvalue, Qt::EditRole);
}

//////////////////////////////////////////////////////////
///////////////statut de paiement//////////////////////
////////////////////////////////////////////////////

ComboStatutPaymentDelegate::ComboStatutPaymentDelegate(QObject * parent)
 {
     Q_UNUSED(parent);
}

ComboStatutPaymentDelegate::~ComboStatutPaymentDelegate(){}

QSize ComboStatutPaymentDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                              const QModelIndex & index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(40,50);
}

QWidget *ComboStatutPaymentDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox * combo = new QComboBox(parent);
    return combo;

}

void ComboStatutPaymentDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     Q_UNUSED(index);
     QComboBox * combo = static_cast<QComboBox*>(editor);
     combo->setEditable(true);
     combo->addItem(tr(NO_VALIDATED));
     combo->addItem(tr(VALIDATED));
     combo->addItem(tr(RECORDED));
}
 
void ComboStatutPaymentDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
     enum {KEYNAME=0,VALUE};
     QComboBox * combo = static_cast<QComboBox*>(editor);
     QString text = combo->currentText();
     model->setData(index, text, Qt::EditRole);
}
 
 //////////////////////////////////////////////////////////
 //////////////DATE EDIT//////////////
 //////////////////////////////////////////
 
 DateDelegate::DateDelegate(QObject * parent)
 {
     Q_UNUSED(parent);
 }

DateDelegate::~DateDelegate(){}

QSize DateDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                              const QModelIndex & index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(40,25);
}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QDateEdit * dateEdit = new QDateEdit(parent);
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    return dateEdit;
}

 void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
 {
     QDateEdit * dateEdit = static_cast<QDateEdit*>(editor);
     QDate date;
     date = index.model()->data(index,Qt::DisplayRole).toDate();
     dateEdit->setDate(date);
}
 
 void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const
 {
     QDateEdit * dateEdit = static_cast<QDateEdit*>(editor);
     QString value = dateEdit->date().toString("yyyy-MM-dd");

     model->setData(index, value, Qt::EditRole);
 }
 
 /////////////////////////////////////////////////////////////////////////
 //////////FACTURATION DOUBLESPINBOX/////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
 
DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent)
     : QStyledItemDelegate(parent)
 {
 }

 QWidget *DoubleSpinBoxDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem &option,
     const QModelIndex &index) const
 {
     Q_UNUSED(option);
     Q_UNUSED(index);
     QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
     editor->setMinimum(0);
     editor->setMaximum(100000.00);
     return editor;
 }

 void DoubleSpinBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
     int modelrow = index.row();
     QString prestation = index.model()->data(index.model()->index(modelrow,PRESTATION)).toString();
     Iotools iotool;
     double value = iotool.getValueFromAct(prestation);
     QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
     spinBox->setValue(value);
 }

 void DoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
     QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
     spinBox->interpretText();
     int value = spinBox->value();
     model->setData(index, value, Qt::EditRole);
 }

 void DoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &index) const
 {
     Q_UNUSED(index);
     editor->setGeometry(option.rect);
 }
 
 ////////////////////////////////////////////////////////
 /////////////MODE PAIEMENTS///////////////////////////////
 ///////////////////////////////////////////////////////////
ComboPayDelegate::ComboPayDelegate(QObject * parent)
 {
     Q_UNUSED(parent);
     m_hash.insert(CASH,tr("Espèces"));
     m_hash.insert(CHECK,tr("Chèque"));
     m_hash.insert(CREDIT_CARD,"Carte bancaire");
     m_hash.insert(BANKING,"Virement");
     m_hash.insert(DU,"Dus");
     m_hash.insert(OTHER,"Autre");
}

ComboPayDelegate::~ComboPayDelegate(){}

QSize ComboPayDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                              const QModelIndex & index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(40,50);
}

QWidget *ComboPayDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox * combo = new QComboBox(parent);
    return combo;
}

void ComboPayDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     Q_UNUSED(index);
     QComboBox * combo = static_cast<QComboBox*>(editor);
     combo->setEditable(true);
     //QModelIndex indexin = index;
     QHash<int,QString>::const_iterator it;
     for (it = m_hash.begin(); it != m_hash.end(); ++it)
     {
         QString item = QString::number(it.key())+":"+it.value();
         combo->addItem(item);
         }
}
 
void ComboPayDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
     enum {KEYNAME=0,VALUE};
     QComboBox * combo = static_cast<QComboBox*>(editor);
     QString value = combo->currentText();
     QStringList listvalue = value.split(":");
     if (listvalue.size()>1)
     {
           value = listvalue[VALUE];
         }
     
     model->setData(index,value, Qt::EditRole);
}

////////////////////////////////////////////////////////////////////
//////////////////PRESTATION LINE EDIT//////////////////////////
///////////////////////////////////////////////////////////////

PrestationEdit::PrestationEdit(QObject *parent,QSqlDatabase db)
   : QStyledItemDelegate(parent)
{
    Q_UNUSED(parent);
    QSqlDatabase dbin = QSqlDatabase(db);
    m_f = new FindReceiptsValues(0,dbin);
}
 
PrestationEdit::~PrestationEdit(){}

QWidget *PrestationEdit::createEditor(QWidget *parent,
     const QStyleOptionViewItem & option,
     const QModelIndex &index) const
{
     Q_UNUSED(option);
     Q_UNUSED(index);
     QPushButton * editor = new QPushButton(parent);
     connect(editor,SIGNAL(pressed()),this,SLOT(showfindvalues()));
     return editor;
}

 void PrestationEdit::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
     QString value = index.model()->data(index, Qt::EditRole).toString();
     QPushButton *button = static_cast<QPushButton*>(editor);
     button->setEnabled(true);
     button->setText(value);
}

void PrestationEdit::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
     QPushButton *button = static_cast<QPushButton*>(editor);
     QString value = button->text();
     model->setData(index, value, Qt::EditRole);
 }

QSize PrestationEdit::sizeHint(const QStyleOptionViewItem &  option ,
                                   const QModelIndex & index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(40,50);
}

void PrestationEdit::showfindvalues()
{
    QHash<QString,QString> hashofvalues;
    if (m_f->exec()==QDialog::Accepted)
    {
        hashofvalues = m_f->getchosenValues();
        m_f->clear();
        }
     QStringList listvalues;
     listvalues = hashofvalues.keys();
     m_value = listvalues.join(",");
     QPushButton *button = new QPushButton;
     button = qobject_cast<QPushButton*>(sender());
     button->setText(m_value);
}

//users
ComboUsersDelegate::ComboUsersDelegate(QObject * parent,const QString & iduser, QSqlDatabase  db)
 {
     Q_UNUSED(parent);
     QSqlDatabase dbin = QSqlDatabase(db);
     m_mapUsers = getUsersFromDatabase(dbin,iduser);
}

ComboUsersDelegate::~ComboUsersDelegate(){}

QSize ComboUsersDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                              const QModelIndex & index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(40,50);
}

QWidget *ComboUsersDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox * combo = new QComboBox(parent);
    return combo;
}

void ComboUsersDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     Q_UNUSED(index);
     QComboBox * combo = static_cast<QComboBox*>(editor);
     QMapIterator<QString,QString> it(m_mapUsers);
     int row = 0;
     while (it.hasNext())
     {
         it.next();
         QString login = it.key();
         QString prat = it.value();
         combo->addItem(login);
         combo->setItemData(row,prat,Qt::ToolTipRole);
         ++row;
         }
}
 
void ComboUsersDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
     QComboBox * combo = static_cast<QComboBox*>(editor);
     QString login = combo->currentText();
     model->setData(index, login, Qt::EditRole);
}

QMap<QString,QString> ComboUsersDelegate::getUsersFromDatabase(QSqlDatabase & db,const QString & iduser)
{
    QMap<QString,QString> mapusers;
    enum{LOGIN=0,USERNAME};
    QString req = QString("select %1,%2 from %3").arg("login","nom_usr","utilisateurs");
    QString reqwhereid= req +  QString(" where %1 = '%2'").arg("id_usr",iduser);
    QSqlQuery qy(db);
    if (!qy.exec(reqwhereid))
    {
          qWarning() << __FILE__ << QString::number(__LINE__) << qy.lastError().text() ;
        }
    while (qy.next())
    {
        mapusers.insert(qy.value(LOGIN).toString(),qy.value(USERNAME).toString());
        }
    
    if (!qy.exec(req))
    {
          qWarning() << __FILE__ << QString::number(__LINE__) << qy.lastError().text() ;
        }
    while (qy.next())
    {
        QString login = qy.value(LOGIN).toString();
        QString prat = qy.value(USERNAME).toString();
        if (!mapusers.keys().contains(login))
        {
              mapusers.insert(login,prat);
            }
        
        }
    return mapusers;
}

////////////////////////////////////////////////////////////////////////
//////////////////names////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

ButtonPatientDelegate::ButtonPatientDelegate(QObject *parent,QSqlDatabase db,const QString & programname)
   : QStyledItemDelegate(parent)
{
    QSqlDatabase dbin = QSqlDatabase(db);
    m_nw = new NamesDialog(0,dbin,programname);
}
 
ButtonPatientDelegate::~ButtonPatientDelegate(){}

QWidget *ButtonPatientDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem & option,
     const QModelIndex & index) const
{
     Q_UNUSED(option);
     Q_UNUSED(index);
     QPushButton * editor = new QPushButton(parent);
     connect(editor,SIGNAL(pressed()),this,SLOT(shownameindex()));
     return editor;
}

 void ButtonPatientDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
     QString value = index.model()->data(index, Qt::EditRole).toString();
     QPushButton *button = static_cast<QPushButton*>(editor);
     button->setEnabled(true);
     button->setText(value);
}

void ButtonPatientDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
     QPushButton *button = static_cast<QPushButton*>(editor);
     QString value = button->text();
     model->setData(index, value, Qt::EditRole);
 }

QSize ButtonPatientDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                                   const QModelIndex & index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(40,50);
}

void ButtonPatientDelegate::shownameindex()
{
     QPushButton *button = new QPushButton;
     button = qobject_cast<QPushButton*>(sender());
     if (m_nw->exec()==QDialog::Accepted)
     {
           m_names = m_nw->getName();
           button->setText(m_names);
         }
}

//////////////////////////////////////////////////////////////////
/////////////////SITES////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

ComboSitesDelegate::ComboSitesDelegate(QObject * parent)
 {
     Q_UNUSED(parent);
     m_mapSites = getSitesFromDatabase();
}

ComboSitesDelegate::~ComboSitesDelegate(){}

QSize ComboSitesDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                              const QModelIndex & index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(40,50);
}

QWidget *ComboSitesDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox * combo = new QComboBox(parent);
    return combo;
}

void ComboSitesDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     Q_UNUSED(index);
     QComboBox * combo = static_cast<QComboBox*>(editor);
     combo->setEditable(true);
     //QModelIndex indexin = index;
     QMap<QString,QString>::const_iterator it;
     for (it = m_mapSites.begin(); it != m_mapSites.end(); ++it)
     {
         QString item = it.value();
         combo->addItem(item);
         }
}
 
void ComboSitesDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
     enum {KEYNAME=0,VALUE};
     QComboBox * combo = static_cast<QComboBox*>(editor);
     QString value = combo->currentText();     
     model->setData(index,value, Qt::EditRole);
}

QMap<QString,QString> ComboSitesDelegate::getSitesFromDatabase()
{
    QMap<QString,QString> map;
    Iotools iotool(this);
    map = iotool.getSitesFromDatabase();
    return map;
}

////////////////////////////////////////////////////////////
//////////////payeurs///////////////////////////////////////
//////////////////////////////////////////////////////////


ComboPayeursDelegate::ComboPayeursDelegate(QObject * parent)
 {
     Q_UNUSED(parent);
     m_mapPayeurs = getPayeursFromDatabase();
}

ComboPayeursDelegate::~ComboPayeursDelegate(){}

QSize ComboPayeursDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                              const QModelIndex & index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(40,50);
}

QWidget *ComboPayeursDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox * combo = new QComboBox(parent);
    combo->setEditable(true);
    combo->setInsertPolicy(QComboBox::InsertAtTop);
    return combo;
}

void ComboPayeursDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     Q_UNUSED(index);
     QComboBox * combo = static_cast<QComboBox*>(editor);
     QMap<QString,QString>::const_iterator it;
     for (it = m_mapPayeurs.begin(); it != m_mapPayeurs.end(); ++it)
     {
         QString item = it.value();
         combo->addItem(item);
         }
}
 
void ComboPayeursDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
     enum {KEYNAME=0,VALUE};
     QComboBox * combo = static_cast<QComboBox*>(editor);
     QString value = combo->currentText();     
     model->setData(index,value, Qt::EditRole);
}

QMap<QString,QString> ComboPayeursDelegate::getPayeursFromDatabase()
{
    QMap<QString,QString> map;
    Iotools iotool(this);
    map = iotool.getPayeursFromDatabase();
    return map;
}
