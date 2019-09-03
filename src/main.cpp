/*
 *	Meteo/src/main.cpp
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Mesures.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Mesures mesure;
    QQmlApplicationEngine engine;
    
    engine.rootContext()->setContextProperty("mesure", &mesure);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));


    return app.exec();
}
