#include "MetadataController.h"
#include "CoverImageProvider.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QLocale>
#include <QUrl>

// TagLib
#include <taglib/attachedpictureframe.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/textidentificationframe.h>
#include <taglib/tpicturetype.h>
#include <taglib/tstring.h>

namespace {

// ---- String conversion helpers between Qt and TagLib (both UTF-8) ----------
TagLib::String toTagString(const QString &s)
{
    return TagLib::String(s.toUtf8().constData(), TagLib::String::UTF8);
}

QString fromTagString(const TagLib::String &s)
{
    return QString::fromStdString(s.to8Bit(/*unicode=*/true));
}

// Reads a single text-identification frame (e.g. TPE2, TPOS) as a QString.
QString readTextFrame(TagLib::ID3v2::Tag *tag, const char *frameId)
{
    const TagLib::ID3v2::FrameList &frames = tag->frameList(frameId);
    if (frames.isEmpty())
        return {};
    return fromTagString(frames.front()->toString());
}

// Creates/replaces a UTF-8 text-identification frame. An empty value removes it.
void writeTextFrame(TagLib::ID3v2::Tag *tag, const char *frameId, const QString &value)
{
    const TagLib::ByteVector id(frameId);
    tag->removeFrames(id);

    if (value.trimmed().isEmpty())
        return;

    auto *frame = new TagLib::ID3v2::TextIdentificationFrame(id, TagLib::String::UTF8);
    frame->setText(toTagString(value));
    tag->addFrame(frame);
}

// Picks the front-cover APIC frame if present, otherwise the first picture.
TagLib::ID3v2::AttachedPictureFrame *findCoverFrame(TagLib::ID3v2::Tag *tag)
{
    const TagLib::ID3v2::FrameList &frames = tag->frameList("APIC");
    if (frames.isEmpty())
        return nullptr;

    TagLib::ID3v2::AttachedPictureFrame *fallback = nullptr;
    for (auto *frame : frames) {
        auto *pic = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frame);
        if (!fallback)
            fallback = pic;
        if (pic->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover)
            return pic;
    }
    return fallback;
}

QString humanFileSize(qint64 bytes)
{
    return QLocale().formattedDataSize(bytes, 2, QLocale::DataSizeTraditionalFormat);
}

// Strips characters that are illegal in file names on common platforms.
QString sanitizeFileName(const QString &name)
{
    QString out = name.trimmed();
    const QString illegal = QStringLiteral("/\\:*?\"<>|");
    for (const QChar &ch : illegal)
        out.remove(ch);
    return out;
}

QString formatDuration(int seconds)
{
    const int h = seconds / 3600;
    const int m = (seconds % 3600) / 60;
    const int s = seconds % 60;
    if (h > 0)
        return QStringLiteral("%1:%2:%3").arg(h).arg(m, 2, 10, QLatin1Char('0')).arg(s, 2, 10, QLatin1Char('0'));
    return QStringLiteral("%1:%2").arg(m).arg(s, 2, 10, QLatin1Char('0'));
}

} // namespace

MetadataController::MetadataController(QObject *parent)
    : QObject(parent)
    , m_provider(new CoverImageProvider)
{
}

// ---------------------------------------------------------------------------
// Loading
// ---------------------------------------------------------------------------
bool MetadataController::loadFile(const QString &fileOrUrl)
{
    const QString path = toLocalPath(fileOrUrl);
    const QFileInfo info(path);

    if (!info.exists() || !info.isFile()) {
        setStatus(Status::Error, tr("File not found: %1").arg(path));
        return false;
    }
    if (info.suffix().compare(QStringLiteral("mp3"), Qt::CaseInsensitive) != 0) {
        setStatus(Status::Error, tr("Not an MP3 file: %1").arg(info.fileName()));
        return false;
    }

    TagLib::MPEG::File file(QFile::encodeName(path).constData(), /*readProperties=*/true);
    if (!file.isValid()) {
        setStatus(Status::Error, tr("Could not read MP3 file."));
        return false;
    }

    TagLib::ID3v2::Tag *tag = file.ID3v2Tag(/*create=*/true);

    m_filePath = path;
    m_fileName = info.fileName();

    // Generic fields available through the common Tag interface.
    m_title = fromTagString(tag->title());
    m_artist = fromTagString(tag->artist());
    m_album = fromTagString(tag->album());
    m_genre = fromTagString(tag->genre());
    m_comment = fromTagString(tag->comment());
    m_year = tag->year() > 0 ? QString::number(tag->year()) : QString();
    m_trackNumber = tag->track() > 0 ? QString::number(tag->track()) : QString();

    // ID3v2-specific frames not covered by the generic interface.
    m_albumArtist = readTextFrame(tag, "TPE2");
    m_composer = readTextFrame(tag, "TCOM");
    m_discNumber = readTextFrame(tag, "TPOS");

    // Audio properties.
    if (TagLib::AudioProperties *props = file.audioProperties()) {
        m_bitrate = props->bitrate();
        m_sampleRate = props->sampleRate();
        m_channels = props->channels();
        m_duration = formatDuration(props->lengthInSeconds());
    } else {
        m_bitrate = m_sampleRate = m_channels = 0;
        m_duration = QStringLiteral("0:00");
    }
    m_fileSize = humanFileSize(info.size());

    // Embedded cover art.
    QImage cover;
    if (TagLib::ID3v2::AttachedPictureFrame *pic = findCoverFrame(tag)) {
        const TagLib::ByteVector data = pic->picture();
        cover.loadFromData(reinterpret_cast<const uchar *>(data.data()),
                           static_cast<int>(data.size()));
    }
    // A freshly loaded file starts "clean": we won't rewrite APIC unless the
    // user actually changes the art.
    m_coverDirty = false;
    m_coverData.clear();
    m_coverMime.clear();
    applyCoverImage(cover);

    m_modified = false;
    emit modifiedChanged();

    // Notify every field changed at once so QML re-reads all bindings.
    emit fileChanged();
    emit fileNameChanged();
    emit titleChanged();
    emit artistChanged();
    emit albumChanged();
    emit albumArtistChanged();
    emit composerChanged();
    emit yearChanged();
    emit genreChanged();
    emit trackNumberChanged();
    emit discNumberChanged();
    emit commentChanged();

    setStatus(Status::Idle, QString());
    emit fileLoaded();
    return true;
}

// ---------------------------------------------------------------------------
// Saving (always written as ID3v2.4)
// ---------------------------------------------------------------------------
bool MetadataController::save()
{
    if (m_filePath.isEmpty()) {
        const QString msg = tr("No file is open.");
        setStatus(Status::Error, msg);
        emit saveError(msg);
        return false;
    }

    TagLib::MPEG::File file(QFile::encodeName(m_filePath).constData(), /*readProperties=*/false);
    if (!file.isValid()) {
        const QString msg = tr("Could not open file for writing.");
        setStatus(Status::Error, msg);
        emit saveError(msg);
        return false;
    }

    TagLib::ID3v2::Tag *tag = file.ID3v2Tag(/*create=*/true);

    tag->setTitle(toTagString(m_title));
    tag->setArtist(toTagString(m_artist));
    tag->setAlbum(toTagString(m_album));
    tag->setGenre(toTagString(m_genre));
    tag->setComment(toTagString(m_comment));
    tag->setYear(m_year.toUInt());     // 0 (empty/invalid) clears the frame
    tag->setTrack(m_trackNumber.toUInt());

    writeTextFrame(tag, "TPE2", m_albumArtist);
    writeTextFrame(tag, "TCOM", m_composer);
    writeTextFrame(tag, "TPOS", m_discNumber);

    // Only touch the picture frame if the user replaced or removed the art,
    // so we never re-encode existing artwork needlessly.
    if (m_coverDirty) {
        tag->removeFrames("APIC");
        if (!m_coverData.isEmpty()) {
            auto *pic = new TagLib::ID3v2::AttachedPictureFrame();
            pic->setMimeType(toTagString(m_coverMime));
            pic->setType(TagLib::ID3v2::AttachedPictureFrame::FrontCover);
            pic->setDescription("Cover");
            pic->setPicture(TagLib::ByteVector(m_coverData.constData(),
                                               static_cast<unsigned int>(m_coverData.size())));
            tag->addFrame(pic);
        }
    }

    const bool ok = file.save(TagLib::MPEG::File::ID3v2,
                              TagLib::File::StripOthers,
                              TagLib::ID3v2::v4);
    if (!ok) {
        const QString msg = tr("Failed to write tags to disk.");
        setStatus(Status::Error, msg);
        emit saveError(msg);
        return false;
    }

    // Tags are written; now rename the file on disk if the user changed its
    // name. Done last so the tagged content moves with the new name.
    if (!renameOnDiskIfNeeded()) {
        // Tags saved fine, but the rename failed (e.g. name already in use).
        const QString msg = tr("Tags saved, but the file could not be renamed "
                               "(is the name already in use?).");
        setStatus(Status::Error, msg);
        emit saveError(msg);
        return false;
    }

    m_coverDirty = false;
    m_modified = false;
    emit modifiedChanged();
    setStatus(Status::Success, tr("Saved successfully."));
    emit saved();
    return true;
}

// Renames the file on disk to m_fileName if it differs from the current name.
// Returns false only if a rename was attempted and failed.
bool MetadataController::renameOnDiskIfNeeded()
{
    const QFileInfo current(m_filePath);
    QString desired = sanitizeFileName(m_fileName);

    // Keep the .mp3 extension regardless of what the user typed.
    if (!desired.endsWith(QStringLiteral(".mp3"), Qt::CaseInsensitive))
        desired += QStringLiteral(".mp3");

    if (desired.isEmpty() || desired == QStringLiteral(".mp3"))
        return true; // nothing usable typed; leave the name as-is
    if (desired == current.fileName())
        return true; // unchanged

    const QString newPath = current.absoluteDir().filePath(desired);
    if (QFile::exists(newPath))
        return false;
    if (!QFile::rename(m_filePath, newPath))
        return false;

    m_filePath = newPath;
    m_fileName = desired;
    emit fileChanged();
    emit fileNameChanged();
    return true;
}

// ---------------------------------------------------------------------------
// Album art editing
// ---------------------------------------------------------------------------
bool MetadataController::setCoverArt(const QString &imageFileOrUrl)
{
    const QString path = toLocalPath(imageFileOrUrl);

    QFile imgFile(path);
    if (!imgFile.open(QIODevice::ReadOnly)) {
        setStatus(Status::Error, tr("Could not open image: %1").arg(path));
        return false;
    }
    const QByteArray bytes = imgFile.readAll();

    QImage image;
    if (!image.loadFromData(bytes)) {
        setStatus(Status::Error, tr("Unsupported or corrupt image file."));
        return false;
    }

    const QString suffix = QFileInfo(path).suffix().toLower();
    m_coverMime = (suffix == QStringLiteral("png")) ? QStringLiteral("image/png")
                                                    : QStringLiteral("image/jpeg");
    m_coverData = bytes;
    m_coverDirty = true;
    applyCoverImage(image);
    markModified();
    setStatus(Status::Idle, QString());
    return true;
}

void MetadataController::removeCoverArt()
{
    m_coverData.clear();
    m_coverMime.clear();
    m_coverDirty = true;
    applyCoverImage(QImage());
    markModified();
}

// ---------------------------------------------------------------------------
// Property setters
// ---------------------------------------------------------------------------
void MetadataController::setFileName(const QString &v)
{
    if (m_fileName == v) return;
    m_fileName = v;
    emit fileNameChanged();
    markModified();
}

void MetadataController::setTitle(const QString &v)
{
    if (m_title == v) return;
    m_title = v;
    emit titleChanged();
    markModified();
}

void MetadataController::setArtist(const QString &v)
{
    if (m_artist == v) return;
    m_artist = v;
    emit artistChanged();
    markModified();
}

void MetadataController::setAlbum(const QString &v)
{
    if (m_album == v) return;
    m_album = v;
    emit albumChanged();
    markModified();
}

void MetadataController::setAlbumArtist(const QString &v)
{
    if (m_albumArtist == v) return;
    m_albumArtist = v;
    emit albumArtistChanged();
    markModified();
}

void MetadataController::setComposer(const QString &v)
{
    if (m_composer == v) return;
    m_composer = v;
    emit composerChanged();
    markModified();
}

void MetadataController::setYear(const QString &v)
{
    if (m_year == v) return;
    m_year = v;
    emit yearChanged();
    markModified();
}

void MetadataController::setGenre(const QString &v)
{
    if (m_genre == v) return;
    m_genre = v;
    emit genreChanged();
    markModified();
}

void MetadataController::setTrackNumber(const QString &v)
{
    if (m_trackNumber == v) return;
    m_trackNumber = v;
    emit trackNumberChanged();
    markModified();
}

void MetadataController::setDiscNumber(const QString &v)
{
    if (m_discNumber == v) return;
    m_discNumber = v;
    emit discNumberChanged();
    markModified();
}

void MetadataController::setComment(const QString &v)
{
    if (m_comment == v) return;
    m_comment = v;
    emit commentChanged();
    markModified();
}

// ---------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------
bool MetadataController::isMp3(const QString &fileOrUrl) const
{
    return toLocalPath(fileOrUrl).endsWith(QStringLiteral(".mp3"), Qt::CaseInsensitive);
}

bool MetadataController::isImage(const QString &fileOrUrl) const
{
    const QString p = toLocalPath(fileOrUrl).toLower();
    return p.endsWith(QStringLiteral(".jpg")) || p.endsWith(QStringLiteral(".jpeg"))
            || p.endsWith(QStringLiteral(".png"));
}

QString MetadataController::toLocalPath(const QString &fileOrUrl) const
{
    if (fileOrUrl.startsWith(QStringLiteral("file:")))
        return QUrl(fileOrUrl).toLocalFile();
    const QUrl url(fileOrUrl);
    if (url.isLocalFile())
        return url.toLocalFile();
    return fileOrUrl;
}

void MetadataController::applyCoverImage(const QImage &image)
{
    m_provider->setImage(image);
    m_hasCoverArt = !image.isNull();
    ++m_coverGeneration;
    // A fresh URL (new generation id) forces QML to re-request the picture.
    m_coverArtSource = m_hasCoverArt
            ? QStringLiteral("image://cover/%1").arg(m_coverGeneration)
            : QString();
    emit coverArtChanged();
}

void MetadataController::setStatus(Status status, const QString &message)
{
    if (m_status == status && m_statusMessage == message)
        return;
    m_status = status;
    m_statusMessage = message;
    emit statusChanged();
}

void MetadataController::markModified()
{
    // Editing after a save/error returns the status to a neutral state.
    if (m_status != Status::Idle)
        setStatus(Status::Idle, QString());
    if (!m_modified) {
        m_modified = true;
        emit modifiedChanged();
    }
}
