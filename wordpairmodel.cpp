#include <wordpairmodel.h>
#include <QVariant>
#include <QtMath>

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
    return qMax(m_database.numberOfWords()+1, 10);
}

QVariant WordPairModel::data(const QModelIndex &index, int role) const
{
    if (index.column() < 1) {
        if (index.row() < m_database.numberOfWords()) {
            if (LocalTextRole == role)
                return QVariant::fromValue(m_database.getWord(index.row(), WordDatabase::LocalWord));
            else if (ForeignTextRole == role)
                return QVariant::fromValue(m_database.getWord(index.row(), WordDatabase::ForeignWord));
        } else {
            if (LocalTextRole == role)
                return QVariant::fromValue(QString("Suomalainen sana..."));
            else if (ForeignTextRole == role)
                return QVariant::fromValue(QString("Vieraskielinen sana"));
        }
    }
    return QVariant();
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
