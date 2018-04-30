#ifndef WORDPAIRMODEL_H
#define WORDPAIRMODEL_H
#include <QAbstractListModel>
#include "worddatabase.h"

class WordPairModel : public QAbstractListModel
{
public:
    enum WordPairRole {
        LocalTextRole = Qt::UserRole,
        ForeignTextRole
    };

    explicit WordPairModel(QObject *parent = Q_NULLPTR);
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QHash<int, QByteArray> roleNames() const;
private slots:
    void databaseItemModified(int modifiedIndex);
    void databaseItemAdded(int newIndex);
private:
    Q_OBJECT
    WordDatabase m_database;
};
#endif // WORDPAIRMODEL_H
