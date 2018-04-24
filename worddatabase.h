#ifndef WORDDATABASE_H
#define WORDDATABASE_H
#include <QString>
#include <QPair>
#include <QVector>
#include <QObject>

class WordDatabase : public QObject {
public:
    typedef enum {
        LocalWord = 0,
        ForeignWord
    } WordType;
    typedef QPair<QString, QString> RowItem;

    WordDatabase();
    int numberOfWords() const;
    QString getWord(int index, WordType type) const;
    void setWord(int index, WordType type, QString text);
signals:
    void itemModified(int index);
    void itemAdded(int index);
private:
    Q_OBJECT
    QVector<RowItem> m_wordList;
};
#endif // WORDDATABASE_H
