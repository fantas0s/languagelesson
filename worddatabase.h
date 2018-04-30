#ifndef WORDDATABASE_H
#define WORDDATABASE_H
#include <QString>
#include <QPair>
#include <QVector>
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

class WordDatabase : public QObject {
public:
    typedef enum {
        LocalWord = 0,
        ForeignWord
    } WordType;
    typedef QPair<QString, QString> RowItem;

    static QObject* getDatabaseInstance(QQmlEngine* engine, QJSEngine* scriptEngine);
    int numberOfWords() const;
    QString getWord(int index, WordType type) const;
    void setWord(int index, WordType type, QString text);
signals:
    void itemModified(int index);
    void itemAdded(int index);
    void itemRemoved(int index);
private:
    Q_OBJECT
    WordDatabase(QObject* parent = Q_NULLPTR);
    static WordDatabase* m_instance;
    QVector<RowItem> m_wordList;
};
#endif // WORDDATABASE_H
