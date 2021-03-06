#ifndef FACTUREMODEL_H
#define FACTUREMODEL_H

#include <QAbstractTableModel>
#include <QSqlError>
#include <QStringList>
#include <QVector>

class FactureModel : public QAbstractTableModel
{
    public:
         FactureModel(QObject * parent =0);
         ~FactureModel ();         
         int rowCount(const QModelIndex &parent = QModelIndex() ) const;
         int columnCount(const QModelIndex &parent = QModelIndex()) const;
         QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
         bool insertRows( int position, int count, const QModelIndex & parent = QModelIndex() );
         bool removeRows(int position, int count, const QModelIndex & parent = QModelIndex());
         bool submit();
         QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
         bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
         QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
         bool setHeaderData( int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole );
         QSqlError lastError();
         Qt::ItemFlags flags(const QModelIndex &index) const;

    private:
         QVector<QList<QVariant> > *m_listsOfValuesbyRows;
         QStringList m_headersRows;
         QStringList m_headersColumns;
         int m_rows ;
         bool m_test;
};  


#endif

