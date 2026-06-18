# PropertyMP3

A desktop MP3 metadata editor with a Spotify-inspired dark UI. Edit the ID3
tags of your local MP3 files so they display correctly when added as **local
files** in Spotify.

Built with **C++17 + Qt 6 (QML)** for the interface and **TagLib** for reading
and writing ID3v2 tags.

## Features

- Open an MP3 via a file picker **or** by dragging it onto the window
- Edit **Title, Artist, Album, Album Artist, Year, Genre, Track #, Disc #** and **Comment**
- View, replace (click or drop a JPG/PNG) the embedded **album art**
- Read-only info panel: **bitrate, sample rate, channels, duration, file size, file name**
- Saves everything back as **ID3v2.4**
- Smooth 60 fps animations: load fade/slide-in, green focus glow on fields,
  hover scaling, album-art cross-fade, and a Save button that morphs into a
  checkmark on success

## Project layout

```
PropertyMP3/
├── CMakeLists.txt              # Finds Qt6 + TagLib, builds the app
├── resources.qrc              # Bundles the QML files into the binary
├── src/
│   ├── main.cpp               # App entry point, wiring
│   ├── MetadataController.*   # C++ backend: file + ID3 tag logic (TagLib)
│   └── CoverImageProvider.h   # Serves album art to QML
└── qml/
    ├── Main.qml               # Top-level window / layout
    └── components/            # Theme, Card, EditField, AlbumArtView, SaveButton, …
```

The C++ backend (`MetadataController`) is exposed to QML as the `backend`
context object; the UI lives entirely in the `.qml` files.

## Dependencies

- **CMake** ≥ 3.21
- **Qt 6** ≥ 6.5 (modules: Quick, Qml, QuickControls2, plus the
  `Qt5Compat.GraphicalEffects` and `QtQuick.Effects` QML modules — both ship
  with a standard Qt 6 install)
- **TagLib** ≥ 1.11 (TagLib 2.x recommended)
- A C++17 compiler

### Installing the dependencies

**macOS (Homebrew)**
```sh
brew install cmake qt taglib
```

**Debian / Ubuntu**
```sh
sudo apt install cmake build-essential qt6-base-dev qt6-declarative-dev \
                 qml6-module-qtquick-controls qml6-module-qtquick-dialogs \
                 qml6-module-qtquick-effects qml6-module-qt5compat-graphicaleffects \
                 libtag1-dev
```

**Fedora**
```sh
sudo dnf install cmake gcc-c++ qt6-qtbase-devel qt6-qtdeclarative-devel \
                 qt6-qt5compat taglib-devel
```

**Windows (vcpkg + Qt online installer)**
```sh
vcpkg install taglib
# Install Qt 6 via the official Qt online installer, then point CMake at both:
# -DCMAKE_PREFIX_PATH="C:/Qt/6.7.0/msvc2019_64;C:/path/to/vcpkg/installed/x64-windows"
```

## Build & run

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Run it:
#   macOS:        open build/PropertyMP3.app   (or ./build/PropertyMP3.app/Contents/MacOS/PropertyMP3)
#   Linux/Windows: ./build/PropertyMP3
```

If CMake cannot find Qt or TagLib (e.g. a non-standard install location), pass
their prefixes explicitly:

```sh
cmake -S . -B build -DCMAKE_PREFIX_PATH="/path/to/qt;/path/to/taglib"
```

## App icon

Drop your icon files into `icons/` (then re-run CMake):

- `icons/PropertyMP3.icns` — used for the macOS `.app` / Dock icon
- `icons/PropertyMP3.ico`  — embedded in the Windows `.exe`

Both are optional; without them the app uses the default icon. See
[`icons/README.md`](icons/README.md) for how to generate them.

## Building a Windows .exe

The code is fully cross-platform — the only OS-specific bit is a guarded macOS
linker workaround in `CMakeLists.txt`. To produce a `.exe` you build **on
Windows** (cross-compiling from macOS is not practical):

```bat
:: With Qt's MSVC kit + vcpkg providing TagLib
cmake -S . -B build -DCMAKE_PREFIX_PATH="C:/Qt/6.7.0/msvc2019_64;C:/vcpkg/installed/x64-windows"
cmake --build build --config Release

:: Bundle the Qt runtime DLLs + QML modules next to the exe so it runs standalone
C:\Qt\6.7.0\msvc2019_64\bin\windeployqt.exe --qmldir qml build\Release\PropertyMP3.exe
```

`WIN32_EXECUTABLE` is set, so the `.exe` launches as a GUI app with no console
window. On macOS, the equivalent bundling step is `macdeployqt PropertyMP3.app`.

## Notes

- Files are always written as **ID3v2.4** and other tag types (e.g. ID3v1) are
  stripped, which is the format Spotify reads most reliably.
- Album art is stored as a single **front-cover** APIC frame; existing artwork
  is only re-encoded if you actually change it.
