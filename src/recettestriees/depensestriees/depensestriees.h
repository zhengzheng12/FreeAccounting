#ifndef DEPENSESTRIEES_H
#define DEPENSESTRIEES_H
#include "../etatstries/etatstries.h"
#include "../etatstries/etatsconstants.h"
#include <common/constants.h>
#include <common/icore.h>
#include <QtGui>
#include <QtCore>
class depensestriees : public QObject{
  Q_OBJECT
  public :
    depensestriees();
    ~depensestriees();
    etatstries *w;
    void execRec();
    QWidget * widgetdeptrie();
  private :
    QString m_appelsqlchamps        ;// champs appeles
    QString m_parametrestableformat ;// largeur des champs de la table
    QString m_tablesql              ;//table appelee
    int     m_nombrechamps          ;//champs a concatener avant especes pour ecrire les mois.
    QHash<int,QString> m_itemspourcombobox ;

};
#endif
