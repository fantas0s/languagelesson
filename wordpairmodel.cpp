#include <wordpairmodel.h>
#include <QVariant>
#include <QtMath>

#define NUMBER_OF_WORDS_ALWAYS_IN_LIST  10

WordPairModel::WordPairModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_database = qobject_cast<WordDatabase*>(WordDatabase::getDatabaseInstance(Q_NULLPTR, Q_NULLPTR));
    Q_ASSERT(m_database);
    connect(m_database, SIGNAL(itemAdded(int)), this, SLOT(databaseItemAdded(int)));
    connect(m_database, SIGNAL(itemModified(int)), this, SLOT(databaseItemModified(int)));
    connect(m_database, SIGNAL(itemRemoved(int)), this, SLOT(databaseItemRemoved(int)));
}

QHash<int, QByteArray> WordPairModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[LocalTextRole] = "localText";
    roles[ForeignTextRole] = "foreignText";
    return roles;
}

int WordPairModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return qMax(m_database->numberOfWords()+1, NUMBER_OF_WORDS_ALWAYS_IN_LIST);
}

QVariant WordPairModel::data(const QModelIndex &index, int role) const
{
    if (index.column() < 1) {
        if (index.row() < m_database->numberOfWords()) {
            if (LocalTextRole == role)
                return QVariant::fromValue(m_database->getWord(index.row(), WordDatabase::LocalWord));
            else if (ForeignTextRole == role)
                return QVariant::fromValue(m_database->getWord(index.row(), WordDatabase::ForeignWord));
        } else {
            if (LocalTextRole == role)
                return QVariant::fromValue(QString("Suomalainen sana..."));
            else if (ForeignTextRole == role)
                return QVariant::fromValue(QString("Vieraskielinen sana..."));
        }
    }
    return QVariant();
}

void WordPairModel::databaseItemModified(int modifiedIndex)
{
    beginMoveRows(QModelIndex(), modifiedIndex, modifiedIndex, QModelIndex(), modifiedIndex);
    endMoveRows();
}

void WordPairModel::databaseItemRemoved(int oldIndex)
{
    if (m_database->numberOfWords() <= NUMBER_OF_WORDS_ALWAYS_IN_LIST) {
        // Deleting might introduce new fake items. Reset to get proper list length.
        beginResetModel();
        endResetModel();
    } else {
        beginRemoveRows(QModelIndex(), oldIndex, oldIndex);
        endRemoveRows();
    }
}

void WordPairModel::databaseItemAdded(int newIndex)
{
    if (m_database->numberOfWords() <= NUMBER_OF_WORDS_ALWAYS_IN_LIST) {
        // Adding might take place from middle of list. Reset to get proper ordering.
        beginResetModel();
        endResetModel();
    } else {
        beginInsertRows(QModelIndex(), newIndex, newIndex);
        endInsertRows();
    }
}
