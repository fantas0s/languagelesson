#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "wordpairmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<WordPairModel>("wordpairmodel", 1, 0, "WordPairModel");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
