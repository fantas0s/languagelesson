#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "wordpairmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<WordDatabase>("worddatabase", 1, 0, "WordDatabase", WordDatabase::getDatabaseInstance);
    qmlRegisterType<WordPairModel>("wordpairmodel", 1, 0, "WordPairModel");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
