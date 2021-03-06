#ifndef RECETTESTRIEES_H
#define RECETTESTRIEES_H
#include "../etatstries/etatstries.h"
#include "../etatstries/etatsconstants.h"
#include <common/constants.h>
#include <common/icore.h>
#include <QtGui>
#include <QtCore>

class recettestriees : public QObject{
  Q_OBJECT
  public :

    recettestriees();
    ~recettestriees();
    etatstries *w;
    void execRec();
    QWidget * widgetrectrie();
  private :
    QString m_appelsqlchamps        ;// champs appeles
    QString m_parametrestableformat ;// largeur des champs de la table
    QString m_tablesql              ;//table appelee
    int m_nombrechamps              ;//champs a concatener avant especes pour ecrire les mois.
    QHash<int,QString> m_itemspourcombobox ;
    
};

#endif
