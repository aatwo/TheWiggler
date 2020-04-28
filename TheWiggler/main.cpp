#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <memory>

#include <wiggledata.h>
#include <wigglecore.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qRegisterMetaType<uint64_t>("int64_t");
    qRegisterMetaType<WiggleData>("WiggleData");

    auto wiggleCore = std::make_unique<WiggleCore>();
    engine.rootContext()->setContextProperty("wiggleCore", wiggleCore.get());

    auto wiggleDataFactory = std::make_unique<WiggleDataFactory>();
    engine.rootContext()->setContextProperty("wiggleDataFactory", wiggleDataFactory.get());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
