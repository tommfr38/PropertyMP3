#pragma once

#include <QImage>
#include <QMutex>
#include <QMutexLocker>
#include <QQuickImageProvider>

/*
 * Serves the currently loaded album cover to QML via the "image://cover/<id>"
 * URL scheme. The <id> part is only used as a cache-buster: every time a new
 * cover is set the controller bumps a generation counter so the QML Image
 * re-requests the picture and the cross-fade animation can run.
 *
 * requestImage() may be invoked from Qt's image-loading thread, so access to
 * the backing QImage is guarded by a mutex.
 */
class CoverImageProvider : public QQuickImageProvider
{
public:
    CoverImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Image)
    {
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override
    {
        Q_UNUSED(id)
        QMutexLocker locker(&m_mutex);

        if (m_image.isNull())
            return {};

        if (size)
            *size = m_image.size();

        // Honour an explicit request size (e.g. Image.sourceSize) by scaling
        // down with smooth filtering; otherwise hand back the full image.
        if (requestedSize.width() > 0 && requestedSize.height() > 0)
            return m_image.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        return m_image;
    }

    void setImage(const QImage &image)
    {
        QMutexLocker locker(&m_mutex);
        m_image = image;
    }

private:
    QImage m_image;
    QMutex m_mutex;
};
