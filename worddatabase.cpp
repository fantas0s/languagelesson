#include "worddatabase.h"
#include <QStringList>

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

WordDatabase::WordDatabase()
{
    for (int idx=0 ; idx < foreignWords.length() ; ++idx) {
        RowItem newRow(localWords[idx], foreignWords[idx]);
        m_wordList.append(newRow);
    }
}

int WordDatabase::numberOfWords()
{
    return m_wordList.length();
}

QString WordDatabase::getWord(int index, WordType type)
{
    RowItem fetchedItem = m_wordList[index];
    if (type == LocalWord)
        return fetchedItem.first;
    else
        return fetchedItem.second;
}
