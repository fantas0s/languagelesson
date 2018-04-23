#ifndef WORDDATABASE_H
#define WORDDATABASE_H
#include <QString>
#include <QPair>
#include <QVector>

class WordDatabase {
public:
    typedef enum {
        LocalWord = 0,
        ForeignWord
    } WordType;
    typedef QPair<QString, QString> RowItem;

    WordDatabase();
    int numberOfWords();
    QString getWord(int index, WordType type);
private:
    QVector<RowItem> m_wordList;
};
#endif // WORDDATABASE_H
