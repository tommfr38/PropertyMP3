#include "CoverImageProvider.h"
#include "MetadataController.h"

#include <QFileInfo>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName(QStringLiteral("PropertyMP3"));
    QGuiApplication::setOrganizationName(QStringLiteral("PropertyMP3"));
    QGuiApplication::setApplicationDisplayName(QStringLiteral("PropertyMP3"));

    // Use the Basic style so our custom Spotify-dark colours are not overridden
    // by a platform style.
    QQuickStyle::setStyle(QStringLiteral("Basic"));

    // Register the type only so its Status enum is reachable from QML
    // (MetadataController.Success / .Error); the instance itself is provided
    // through the "backend" context property below.
    qmlRegisterUncreatableType<MetadataController>(
        "PropertyMP3", 1, 0, "MetadataController",
        QStringLiteral("Use the 'backend' context property instead."));

    QQmlApplicationEngine engine;

    MetadataController controller;

    // The engine takes ownership of the image provider; the controller keeps a
    // non-owning pointer (see MetadataController::imageProvider) to update it.
    engine.addImageProvider(QStringLiteral("cover"), controller.imageProvider());
    engine.rootContext()->setContextProperty(QStringLiteral("backend"), &controller);

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // Allow opening a file passed on the command line (e.g. "Open with…" or
    // `PropertyMP3 song.mp3`).
    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        if (QFileInfo::exists(arg) && arg.endsWith(QStringLiteral(".mp3"), Qt::CaseInsensitive)) {
            controller.loadFile(arg);
            break;
        }
    }

    return app.exec();
}
