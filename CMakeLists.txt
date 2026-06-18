cmake_minimum_required(VERSION 3.21)

project(PropertyMP3
    VERSION 1.0.0
    DESCRIPTION "Spotify-style MP3 metadata editor"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# ---------------------------------------------------------------------------
# Locate Qt 6. On macOS, point CMake at the Homebrew Qt prefix if the caller
# did not already supply CMAKE_PREFIX_PATH.
# ---------------------------------------------------------------------------
if(APPLE AND NOT DEFINED CMAKE_PREFIX_PATH)
    foreach(_qt_prefix "/opt/homebrew/opt/qt" "/opt/homebrew/opt/qt6" "/usr/local/opt/qt")
        if(EXISTS "${_qt_prefix}")
            list(APPEND CMAKE_PREFIX_PATH "${_qt_prefix}")
        endif()
    endforeach()
endif()

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

# Recent macOS SDKs ship an empty AGL.framework (its binary was removed), but
# Qt's WrapOpenGL still adds it to the link line, which breaks linking with
# "framework 'AGL' not found". Strip AGL out of the link interface if present.
if(APPLE AND TARGET WrapOpenGL::WrapOpenGL)
    get_target_property(_wrapgl_libs WrapOpenGL::WrapOpenGL INTERFACE_LINK_LIBRARIES)
    if(_wrapgl_libs)
        list(FILTER _wrapgl_libs EXCLUDE REGEX "AGL")
        set_property(TARGET WrapOpenGL::WrapOpenGL
                     PROPERTY INTERFACE_LINK_LIBRARIES ${_wrapgl_libs})
    endif()
endif()

# ---------------------------------------------------------------------------
# Locate TagLib. TagLib >= 2.0 ships a CMake config package exporting the
# TagLib::TagLib target. Older 1.x installs only provide pkg-config, so fall
# back to that and build an imported target from it.
# ---------------------------------------------------------------------------
find_package(TagLib QUIET CONFIG)
if(NOT TagLib_FOUND)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(TAGLIB IMPORTED_TARGET taglib)
    endif()
endif()
if(NOT TagLib_FOUND AND NOT TAGLIB_FOUND)
    message(FATAL_ERROR
        "TagLib was not found. Install it with one of:\n"
        "  macOS:          brew install taglib\n"
        "  Debian/Ubuntu:  sudo apt install libtag1-dev\n"
        "  Fedora:         sudo dnf install taglib-devel\n"
        "  Arch:           sudo pacman -S taglib\n"
        "  Windows/vcpkg:  vcpkg install taglib\n"
        "If installed in a non-standard location, pass -DCMAKE_PREFIX_PATH=<dir>.")
endif()

qt_standard_project_setup()

# ---------------------------------------------------------------------------
# Application icon.
#   macOS:   icons/PropertyMP3.icns  -> bundled into the .app
#   Windows: icons/PropertyMP3.ico   -> embedded in the .exe via icons/app.rc
# Both are optional: if the file is missing the app still builds with the
# default icon. Just drop the files in and re-run CMake.
# ---------------------------------------------------------------------------
set(MACOS_ICON   "${CMAKE_CURRENT_SOURCE_DIR}/icons/PropertyMP3.icns")
set(WINDOWS_ICON "${CMAKE_CURRENT_SOURCE_DIR}/icons/PropertyMP3.ico")
set(APP_ICON_SOURCES "")

if(APPLE AND EXISTS "${MACOS_ICON}")
    set(APP_ICON_SOURCES "${MACOS_ICON}")
    set_source_files_properties("${MACOS_ICON}" PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
elseif(WIN32 AND EXISTS "${WINDOWS_ICON}")
    set(APP_ICON_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/icons/app.rc")
endif()

qt_add_executable(PropertyMP3
    src/main.cpp
    src/MetadataController.cpp
    src/MetadataController.h
    src/CoverImageProvider.h
    resources.qrc
    ${APP_ICON_SOURCES}
)

target_link_libraries(PropertyMP3 PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2)

if(TagLib_FOUND)
    target_link_libraries(PropertyMP3 PRIVATE TagLib::TagLib)
else()
    target_link_libraries(PropertyMP3 PRIVATE PkgConfig::TAGLIB)
endif()

# Produce a proper GUI application (.app bundle on macOS, no console on Windows).
set_target_properties(PropertyMP3 PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_NAME "PropertyMP3"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.propertymp3.app"
    MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
    # Just the filename; the .icns is copied into the bundle's Resources above.
    MACOSX_BUNDLE_ICON_FILE "PropertyMP3.icns")

install(TARGETS PropertyMP3
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION bin)
