#include "worddatabase.h"
#include <QStringList>

WordDatabase* WordDatabase::m_instance = Q_NULLPTR;

QStringList localWords = {"Auto",
                          "Pallo",
                          "Puu",
                          "Juosta",
                          "Hyppiä",
                          "Lentää",
                          "Punainen",
                          "Iso",
                          "Mahtava",
                          "Juoksentelisinkohan?"};

QStringList foreignWords = {"Car",
                            "Ball",
                            "Tree",
                            "Run",
                            "Jump",
                            "Fly",
                            "Red",
                            "Big",
                            "Great",
                            "I wonder if I should run around aimlessly?"};

WordDatabase::WordDatabase(QObject *parent) :
    QObject(parent)
{
    for (int idx=0 ; idx < foreignWords.length() ; ++idx) {
        RowItem newRow(localWords[idx], foreignWords[idx]);
        m_wordList.append(newRow);
    }
}

QObject* WordDatabase::getDatabaseInstance(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    if (!m_instance)
        m_instance = new WordDatabase();
    return m_instance;
}

int WordDatabase::numberOfWords() const
{
    return m_wordList.length();
}

QString WordDatabase::getWord(int index, WordType type) const
{
    RowItem fetchedItem = m_wordList[index];
    if (type == LocalWord)
        return fetchedItem.first;
    else
        return fetchedItem.second;
}

void WordDatabase::setWord(int index, WordType type, QString text)
{
    if (m_wordList.length() > index) {
        RowItem fetchedItem = m_wordList[index];
        if (type == LocalWord)
            fetchedItem.first = text;
        else
            fetchedItem.second = text;
        if (fetchedItem.first.length() || fetchedItem.second.length()) {
            m_wordList[index] = fetchedItem;
            emit itemModified(index);
        } else {
            m_wordList.remove(index);
            emit itemRemoved(index);
        }
    } else {
        RowItem newItem;
        if (type == LocalWord)
            newItem.first = text;
        else
            newItem.second = text;
        m_wordList.append(newItem);
        emit itemAdded(m_wordList.length()-1);
    }
}
