#pragma once

#include <QByteArray>
#include <QObject>
#include <QString>

class CoverImageProvider;

/*
 * MetadataController is the bridge between the QML UI and the TagLib library.
 *
 * It exposes the editable ID3v2 fields as writable Q_PROPERTYs, the read-only
 * audio/file information as read-only properties, and the embedded album art
 * through an image provider (see coverArtSource). loadFile() reads tags from
 * disk; save() writes them back as ID3v2.4.
 */
class MetadataController : public QObject
{
    Q_OBJECT

    // ----- File / status -----------------------------------------------------
    Q_PROPERTY(bool hasFile READ hasFile NOTIFY fileChanged)
    Q_PROPERTY(QString filePath READ filePath NOTIFY fileChanged)
    Q_PROPERTY(bool modified READ modified NOTIFY modifiedChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusChanged)

    // ----- Editable tag fields ----------------------------------------------
    // fileName is editable: changing it renames the file on disk when saving.
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged)
    Q_PROPERTY(QString albumArtist READ albumArtist WRITE setAlbumArtist NOTIFY albumArtistChanged)
    Q_PROPERTY(QString composer READ composer WRITE setComposer NOTIFY composerChanged)
    Q_PROPERTY(QString year READ year WRITE setYear NOTIFY yearChanged)
    Q_PROPERTY(QString genre READ genre WRITE setGenre NOTIFY genreChanged)
    Q_PROPERTY(QString trackNumber READ trackNumber WRITE setTrackNumber NOTIFY trackNumberChanged)
    Q_PROPERTY(QString discNumber READ discNumber WRITE setDiscNumber NOTIFY discNumberChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)

    // ----- Album art ---------------------------------------------------------
    Q_PROPERTY(QString coverArtSource READ coverArtSource NOTIFY coverArtChanged)
    Q_PROPERTY(bool hasCoverArt READ hasCoverArt NOTIFY coverArtChanged)

    // ----- Read-only audio / file info --------------------------------------
    Q_PROPERTY(int bitrate READ bitrate NOTIFY fileChanged)
    Q_PROPERTY(int sampleRate READ sampleRate NOTIFY fileChanged)
    Q_PROPERTY(int channels READ channels NOTIFY fileChanged)
    Q_PROPERTY(QString duration READ duration NOTIFY fileChanged)
    Q_PROPERTY(QString fileSize READ fileSize NOTIFY fileChanged)

public:
    // Unscoped so the values are usable from QML as MetadataController.Idle, etc.
    enum Status {
        Idle,
        Success,
        Error
    };
    Q_ENUM(Status)

    explicit MetadataController(QObject *parent = nullptr);

    // Hands the (heap-allocated) image provider to the caller. Ownership is
    // expected to transfer to the QQmlEngine via addImageProvider(); the
    // controller keeps a non-owning pointer so it can update the picture.
    CoverImageProvider *imageProvider() const { return m_provider; }

    // ----- Invokable API used from QML --------------------------------------
    Q_INVOKABLE bool loadFile(const QString &fileOrUrl);
    Q_INVOKABLE bool save();
    Q_INVOKABLE bool setCoverArt(const QString &imageFileOrUrl);
    Q_INVOKABLE void removeCoverArt();

    // Helpers QML uses to validate drag-and-drop payloads.
    Q_INVOKABLE bool isMp3(const QString &fileOrUrl) const;
    Q_INVOKABLE bool isImage(const QString &fileOrUrl) const;

    // ----- Property getters --------------------------------------------------
    bool hasFile() const { return !m_filePath.isEmpty(); }
    QString filePath() const { return m_filePath; }
    QString fileName() const { return m_fileName; }
    bool modified() const { return m_modified; }
    Status status() const { return m_status; }
    QString statusMessage() const { return m_statusMessage; }

    QString title() const { return m_title; }
    QString artist() const { return m_artist; }
    QString album() const { return m_album; }
    QString albumArtist() const { return m_albumArtist; }
    QString composer() const { return m_composer; }
    QString year() const { return m_year; }
    QString genre() const { return m_genre; }
    QString trackNumber() const { return m_trackNumber; }
    QString discNumber() const { return m_discNumber; }
    QString comment() const { return m_comment; }

    QString coverArtSource() const { return m_coverArtSource; }
    bool hasCoverArt() const { return m_hasCoverArt; }

    int bitrate() const { return m_bitrate; }
    int sampleRate() const { return m_sampleRate; }
    int channels() const { return m_channels; }
    QString duration() const { return m_duration; }
    QString fileSize() const { return m_fileSize; }

    // ----- Property setters --------------------------------------------------
    void setFileName(const QString &v);
    void setTitle(const QString &v);
    void setArtist(const QString &v);
    void setAlbum(const QString &v);
    void setAlbumArtist(const QString &v);
    void setComposer(const QString &v);
    void setYear(const QString &v);
    void setGenre(const QString &v);
    void setTrackNumber(const QString &v);
    void setDiscNumber(const QString &v);
    void setComment(const QString &v);

signals:
    void fileChanged();
    void modifiedChanged();
    void statusChanged();

    void fileNameChanged();
    void titleChanged();
    void artistChanged();
    void albumChanged();
    void albumArtistChanged();
    void composerChanged();
    void yearChanged();
    void genreChanged();
    void trackNumberChanged();
    void discNumberChanged();
    void commentChanged();

    void coverArtChanged();

    // Fired after loadFile() succeeds so the UI can run its entrance animation
    // and copy values into the editor fields.
    void fileLoaded();
    // Fired after a save attempt finishes.
    void saved();
    void saveError(const QString &message);

private:
    // Converts a "file://" URL (as delivered by FileDialog / drag-and-drop) or
    // a plain path into a local filesystem path.
    QString toLocalPath(const QString &fileOrUrl) const;
    bool renameOnDiskIfNeeded();
    void applyCoverImage(const class QImage &image);
    void setStatus(Status status, const QString &message);
    void markModified();

    CoverImageProvider *m_provider = nullptr;

    QString m_filePath;
    QString m_fileName;     // editable; renamed on disk during save() if changed
    bool m_modified = false;
    Status m_status = Status::Idle;
    QString m_statusMessage;

    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_albumArtist;
    QString m_composer;
    QString m_year;
    QString m_genre;
    QString m_trackNumber;
    QString m_discNumber;
    QString m_comment;

    // Album art display state + the raw bytes to embed on save.
    QString m_coverArtSource;
    bool m_hasCoverArt = false;
    int m_coverGeneration = 0;
    bool m_coverDirty = false;       // true once the user replaced/removed art
    QByteArray m_coverData;          // bytes to write into the APIC frame
    QString m_coverMime;             // "image/jpeg" or "image/png"

    int m_bitrate = 0;
    int m_sampleRate = 0;
    int m_channels = 0;
    QString m_duration;
    QString m_fileSize;
};
