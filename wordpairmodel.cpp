#include <wordpairmodel.h>
#include <QVariant>

WordPairModel::WordPairModel(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(&m_database, SIGNAL(itemAdded(int)), this, SLOT(databaseItemAdded(int)));
    connect(&m_database, SIGNAL(itemModified(int)), this, SLOT(databaseItemModified(int)));
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
    return m_database.numberOfWords();
}

QVariant WordPairModel::data(const QModelIndex &index, int role) const
{
    if ((index.row() < m_database.numberOfWords()) &&
        (index.column() < 1)) {
        if (LocalTextRole == role)
            return QVariant::fromValue(m_database.getWord(index.row(), WordDatabase::LocalWord));
        else if (ForeignTextRole == role)
            return QVariant::fromValue(m_database.getWord(index.row(), WordDatabase::ForeignWord));
        else if (Qt::DisplayRole == role)
            return QVariant::fromValue(m_database.getWord(index.row(), WordDatabase::LocalWord));
        else
            return QVariant();
    } else {
        return QVariant();
    }
}

bool WordPairModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (LocalTextRole == role) {
        m_database.setWord(index.row(), WordDatabase::LocalWord, value.toString());
        return true;
    } else if (ForeignTextRole == role) {
        m_database.setWord(index.row(), WordDatabase::ForeignWord, value.toString());
        return true;
    } else {
        return false;
    }
}

void WordPairModel::databaseItemModified(int modifiedIndex)
{
    beginMoveRows(QModelIndex(), modifiedIndex, modifiedIndex, QModelIndex(), modifiedIndex);
    endMoveRows();
}

void WordPairModel::databaseItemAdded(int newIndex)
{
    beginInsertRows(QModelIndex(), newIndex, newIndex);
    endInsertRows();
}
