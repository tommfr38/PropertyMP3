/****************************************************************************
** Meta object code from reading C++ file 'MetadataController.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/MetadataController.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MetadataController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN18MetadataControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto MetadataController::qt_create_metaobjectdata<qt_meta_tag_ZN18MetadataControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MetadataController",
        "fileChanged",
        "",
        "modifiedChanged",
        "statusChanged",
        "fileNameChanged",
        "titleChanged",
        "artistChanged",
        "albumChanged",
        "albumArtistChanged",
        "composerChanged",
        "yearChanged",
        "genreChanged",
        "trackNumberChanged",
        "discNumberChanged",
        "commentChanged",
        "coverArtChanged",
        "fileLoaded",
        "saved",
        "saveError",
        "message",
        "loadFile",
        "fileOrUrl",
        "save",
        "setCoverArt",
        "imageFileOrUrl",
        "removeCoverArt",
        "isMp3",
        "isImage",
        "hasFile",
        "filePath",
        "modified",
        "status",
        "Status",
        "statusMessage",
        "fileName",
        "title",
        "artist",
        "album",
        "albumArtist",
        "composer",
        "year",
        "genre",
        "trackNumber",
        "discNumber",
        "comment",
        "coverArtSource",
        "hasCoverArt",
        "bitrate",
        "sampleRate",
        "channels",
        "duration",
        "fileSize",
        "Idle",
        "Success",
        "Error"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'fileChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'modifiedChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'statusChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fileNameChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'titleChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'artistChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'albumChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'albumArtistChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'composerChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'yearChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'genreChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'trackNumberChanged'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'discNumberChanged'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'commentChanged'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'coverArtChanged'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fileLoaded'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'saved'
        QtMocHelpers::SignalData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'saveError'
        QtMocHelpers::SignalData<void(const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 20 },
        }}),
        // Method 'loadFile'
        QtMocHelpers::MethodData<bool(const QString &)>(21, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 22 },
        }}),
        // Method 'save'
        QtMocHelpers::MethodData<bool()>(23, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'setCoverArt'
        QtMocHelpers::MethodData<bool(const QString &)>(24, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 25 },
        }}),
        // Method 'removeCoverArt'
        QtMocHelpers::MethodData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'isMp3'
        QtMocHelpers::MethodData<bool(const QString &) const>(27, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 22 },
        }}),
        // Method 'isImage'
        QtMocHelpers::MethodData<bool(const QString &) const>(28, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 22 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'hasFile'
        QtMocHelpers::PropertyData<bool>(29, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'filePath'
        QtMocHelpers::PropertyData<QString>(30, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'modified'
        QtMocHelpers::PropertyData<bool>(31, QMetaType::Bool, QMC::DefaultPropertyFlags, 1),
        // property 'status'
        QtMocHelpers::PropertyData<Status>(32, 0x80000000 | 33, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 2),
        // property 'statusMessage'
        QtMocHelpers::PropertyData<QString>(34, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'fileName'
        QtMocHelpers::PropertyData<QString>(35, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'title'
        QtMocHelpers::PropertyData<QString>(36, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'artist'
        QtMocHelpers::PropertyData<QString>(37, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'album'
        QtMocHelpers::PropertyData<QString>(38, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'albumArtist'
        QtMocHelpers::PropertyData<QString>(39, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
        // property 'composer'
        QtMocHelpers::PropertyData<QString>(40, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'year'
        QtMocHelpers::PropertyData<QString>(41, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
        // property 'genre'
        QtMocHelpers::PropertyData<QString>(42, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 10),
        // property 'trackNumber'
        QtMocHelpers::PropertyData<QString>(43, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'discNumber'
        QtMocHelpers::PropertyData<QString>(44, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'comment'
        QtMocHelpers::PropertyData<QString>(45, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 13),
        // property 'coverArtSource'
        QtMocHelpers::PropertyData<QString>(46, QMetaType::QString, QMC::DefaultPropertyFlags, 14),
        // property 'hasCoverArt'
        QtMocHelpers::PropertyData<bool>(47, QMetaType::Bool, QMC::DefaultPropertyFlags, 14),
        // property 'bitrate'
        QtMocHelpers::PropertyData<int>(48, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'sampleRate'
        QtMocHelpers::PropertyData<int>(49, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'channels'
        QtMocHelpers::PropertyData<int>(50, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'duration'
        QtMocHelpers::PropertyData<QString>(51, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'fileSize'
        QtMocHelpers::PropertyData<QString>(52, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Status'
        QtMocHelpers::EnumData<Status>(33, 33, QMC::EnumFlags{}).add({
            {   53, Status::Idle },
            {   54, Status::Success },
            {   55, Status::Error },
        }),
    };
    return QtMocHelpers::metaObjectData<MetadataController, qt_meta_tag_ZN18MetadataControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MetadataController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18MetadataControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18MetadataControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18MetadataControllerE_t>.metaTypes,
    nullptr
} };

void MetadataController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MetadataController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->fileChanged(); break;
        case 1: _t->modifiedChanged(); break;
        case 2: _t->statusChanged(); break;
        case 3: _t->fileNameChanged(); break;
        case 4: _t->titleChanged(); break;
        case 5: _t->artistChanged(); break;
        case 6: _t->albumChanged(); break;
        case 7: _t->albumArtistChanged(); break;
        case 8: _t->composerChanged(); break;
        case 9: _t->yearChanged(); break;
        case 10: _t->genreChanged(); break;
        case 11: _t->trackNumberChanged(); break;
        case 12: _t->discNumberChanged(); break;
        case 13: _t->commentChanged(); break;
        case 14: _t->coverArtChanged(); break;
        case 15: _t->fileLoaded(); break;
        case 16: _t->saved(); break;
        case 17: _t->saveError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: { bool _r = _t->loadFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: { bool _r = _t->setCoverArt((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->removeCoverArt(); break;
        case 22: { bool _r = _t->isMp3((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 23: { bool _r = _t->isImage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::fileChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::modifiedChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::statusChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::fileNameChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::titleChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::artistChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::albumChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::albumArtistChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::composerChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::yearChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::genreChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::trackNumberChanged, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::discNumberChanged, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::commentChanged, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::coverArtChanged, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::fileLoaded, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)()>(_a, &MetadataController::saved, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (MetadataController::*)(const QString & )>(_a, &MetadataController::saveError, 17))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->hasFile(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->filePath(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->modified(); break;
        case 3: *reinterpret_cast<Status*>(_v) = _t->status(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->statusMessage(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->fileName(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->title(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->artist(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->album(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->albumArtist(); break;
        case 10: *reinterpret_cast<QString*>(_v) = _t->composer(); break;
        case 11: *reinterpret_cast<QString*>(_v) = _t->year(); break;
        case 12: *reinterpret_cast<QString*>(_v) = _t->genre(); break;
        case 13: *reinterpret_cast<QString*>(_v) = _t->trackNumber(); break;
        case 14: *reinterpret_cast<QString*>(_v) = _t->discNumber(); break;
        case 15: *reinterpret_cast<QString*>(_v) = _t->comment(); break;
        case 16: *reinterpret_cast<QString*>(_v) = _t->coverArtSource(); break;
        case 17: *reinterpret_cast<bool*>(_v) = _t->hasCoverArt(); break;
        case 18: *reinterpret_cast<int*>(_v) = _t->bitrate(); break;
        case 19: *reinterpret_cast<int*>(_v) = _t->sampleRate(); break;
        case 20: *reinterpret_cast<int*>(_v) = _t->channels(); break;
        case 21: *reinterpret_cast<QString*>(_v) = _t->duration(); break;
        case 22: *reinterpret_cast<QString*>(_v) = _t->fileSize(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 5: _t->setFileName(*reinterpret_cast<QString*>(_v)); break;
        case 6: _t->setTitle(*reinterpret_cast<QString*>(_v)); break;
        case 7: _t->setArtist(*reinterpret_cast<QString*>(_v)); break;
        case 8: _t->setAlbum(*reinterpret_cast<QString*>(_v)); break;
        case 9: _t->setAlbumArtist(*reinterpret_cast<QString*>(_v)); break;
        case 10: _t->setComposer(*reinterpret_cast<QString*>(_v)); break;
        case 11: _t->setYear(*reinterpret_cast<QString*>(_v)); break;
        case 12: _t->setGenre(*reinterpret_cast<QString*>(_v)); break;
        case 13: _t->setTrackNumber(*reinterpret_cast<QString*>(_v)); break;
        case 14: _t->setDiscNumber(*reinterpret_cast<QString*>(_v)); break;
        case 15: _t->setComment(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *MetadataController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MetadataController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18MetadataControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MetadataController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 24;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void MetadataController::fileChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MetadataController::modifiedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MetadataController::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MetadataController::fileNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MetadataController::titleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MetadataController::artistChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MetadataController::albumChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MetadataController::albumArtistChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void MetadataController::composerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void MetadataController::yearChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void MetadataController::genreChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void MetadataController::trackNumberChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void MetadataController::discNumberChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void MetadataController::commentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void MetadataController::coverArtChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void MetadataController::fileLoaded()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void MetadataController::saved()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void MetadataController::saveError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 17, nullptr, _t1);
}
QT_WARNING_POP
