import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Dialogs
import PropertyMP3
import "components"

ApplicationWindow {
    id: window
    visible: true
    width: 1000
    height: 760
    minimumWidth: 720
    minimumHeight: 600
    title: "PropertyMP3"
    color: theme.background
    font.family: theme.fontFamily

    Theme { id: theme }

    // ---------------------------------------------------------------------
    // File pickers
    // ---------------------------------------------------------------------
    FileDialog {
        id: openMp3Dialog
        title: "Open MP3"
        nameFilters: ["MP3 files (*.mp3)", "All files (*)"]
        onAccepted: backend.loadFile(selectedFile.toString())
    }

    FileDialog {
        id: coverDialog
        title: "Choose cover image"
        nameFilters: ["Images (*.jpg *.jpeg *.png)", "All files (*)"]
        onAccepted: backend.setCoverArt(selectedFile.toString())
    }

    // ---------------------------------------------------------------------
    // Backend events
    // ---------------------------------------------------------------------
    Connections {
        target: backend
        function onFileLoaded() {
            populateFields();
            entrance.restart();
        }
        function onSaved() {
            // Reflect any rename back into the field.
            fileNameField.set(backend.fileName);
            saveButton.showSuccess();
        }
    }

    // Copy backend values into the editor tiles (after a file loads).
    function populateFields() {
        fileNameField.set(backend.fileName);
        titleField.set(backend.title);
        artistField.set(backend.artist);
        albumField.set(backend.album);
        albumArtistField.set(backend.albumArtist);
        composerField.set(backend.composer);
        yearField.set(backend.year);
        genreField.set(backend.genre);
        trackField.set(backend.trackNumber);
        discField.set(backend.discNumber);
        commentField.set(backend.comment);
    }

    // Push the tile values back into the backend before saving.
    function commitFields() {
        backend.fileName = fileNameField.text;
        backend.title = titleField.text;
        backend.artist = artistField.text;
        backend.album = albumField.text;
        backend.albumArtist = albumArtistField.text;
        backend.composer = composerField.text;
        backend.year = yearField.text;
        backend.genre = genreField.text;
        backend.trackNumber = trackField.text;
        backend.discNumber = discField.text;
        backend.comment = commentField.text;
    }

    function infoLine() {
        if (backend.bitrate <= 0)
            return "";
        var ch = backend.channels === 1 ? "Mono"
               : backend.channels === 2 ? "Stereo"
               : backend.channels > 0 ? backend.channels + " ch" : "";
        return [backend.bitrate + " kbps", backend.sampleRate + " Hz", ch,
                backend.duration, backend.fileSize].filter(function (s) { return s.length > 0; })
               .join("   ·   ");
    }

    // ---------------------------------------------------------------------
    // Window-wide drop target for MP3 files. Declared first so it sits below
    // the content; the album-art drop area (on top) handles image drops.
    // ---------------------------------------------------------------------
    DropArea {
        id: mp3Drop
        anchors.fill: parent
        property bool highlight: false

        onEntered: function (drag) {
            highlight = drag.hasUrls && backend.isMp3(drag.urls[0].toString());
            if (!highlight)
                drag.accepted = false;
        }
        onExited: highlight = false
        onDropped: function (drop) {
            highlight = false;
            if (drop.hasUrls && backend.isMp3(drop.urls[0].toString()))
                backend.loadFile(drop.urls[0].toString());
        }
    }

    // ---------------------------------------------------------------------
    // Page layout
    // ---------------------------------------------------------------------
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 28
        spacing: 20

        // ----- Header -----
        RowLayout {
            Layout.fillWidth: true
            spacing: 14

            Rectangle {
                width: 34; height: 34; radius: 17
                color: theme.accent
                Text {
                    anchors.centerIn: parent
                    text: "♪"
                    color: theme.textOnAccent
                    font.pixelSize: 20
                    font.bold: true
                }
            }

            ColumnLayout {
                spacing: 0
                Text {
                    text: "PropertyMP3"
                    color: theme.textPrimary
                    font.family: theme.fontFamily
                    font.pixelSize: 22
                    font.bold: true
                }
                Text {
                    text: "Edit a song's details with ease"
                    color: theme.textSecondary
                    font.family: theme.fontFamily
                    font.pixelSize: 13
                }
            }

            Item { Layout.fillWidth: true }

            AccentButton {
                text: backend.hasFile ? "Open another…" : "Open MP3"
                baseColor: backend.hasFile ? theme.cardHover : theme.accent
                textColor: backend.hasFile ? theme.textPrimary : theme.textOnAccent
                onClicked: openMp3Dialog.open()
            }
        }

        // ----- Empty state -----
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: !backend.hasFile

            Card {
                anchors.fill: parent
                color: theme.card

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 16
                    width: Math.min(420, parent.width - 80)

                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: "♪"
                        color: theme.textSecondary
                        font.pixelSize: 64
                    }
                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: "Drop an MP3 here"
                        color: theme.textPrimary
                        font.family: theme.fontFamily
                        font.pixelSize: 20
                        font.bold: true
                    }
                    Text {
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.WordWrap
                        text: "…or use the Open button to choose a file, then edit its name, title, artist, artwork and more."
                        color: theme.textSecondary
                        font.family: theme.fontFamily
                        font.pixelSize: 14
                    }
                    AccentButton {
                        Layout.alignment: Qt.AlignHCenter
                        text: "Open MP3"
                        onClicked: openMp3Dialog.open()
                    }
                }
            }
        }

        // ----- Editor: scrollable column of tiles (fades + slides in) -----
        ScrollView {
            id: contentScroll
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: backend.hasFile
            clip: true
            contentWidth: availableWidth

            ColumnLayout {
                id: page
                width: contentScroll.availableWidth
                spacing: 16

                opacity: 0
                property real slideY: 0
                transform: Translate { y: page.slideY }

                ParallelAnimation {
                    id: entrance
                    NumberAnimation { target: page; property: "opacity"; from: 0; to: 1; duration: 420; easing.type: Easing.OutCubic }
                    NumberAnimation { target: page; property: "slideY"; from: 26; to: 0; duration: 420; easing.type: Easing.OutCubic }
                }

                // --- Top: artwork + identity fields ---
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 18

                    AlbumArtView {
                        id: albumArt
                        Layout.preferredWidth: 200
                        Layout.preferredHeight: 200
                        Layout.alignment: Qt.AlignTop
                        source: backend.coverArtSource
                        onClicked: coverDialog.open()
                        onImageDropped: function (url) { backend.setCoverArt(url); }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignTop
                        spacing: 12

                        EditField { id: fileNameField; Layout.fillWidth: true; label: "FILE NAME"; placeholder: "song.mp3" }
                        EditField { id: titleField;    Layout.fillWidth: true; label: "TITLE";     placeholder: "Song title" }
                        EditField { id: artistField;   Layout.fillWidth: true; label: "ARTIST";    placeholder: "Performing artist" }
                    }
                }

                // --- Remaining fields as a responsive grid of tiles ---
                GridLayout {
                    id: grid
                    Layout.fillWidth: true
                    columns: width > 540 ? 2 : 1
                    columnSpacing: 16
                    rowSpacing: 12

                    EditField { id: albumField;       Layout.fillWidth: true; label: "ALBUM";        placeholder: "Album name" }
                    EditField { id: albumArtistField; Layout.fillWidth: true; label: "ALBUM ARTIST"; placeholder: "Album artist" }
                    EditField { id: composerField;    Layout.fillWidth: true; label: "COMPOSER / AUTHOR"; placeholder: "Writer / composer" }
                    EditField { id: genreField;       Layout.fillWidth: true; label: "GENRE";        placeholder: "Genre" }
                    EditField { id: yearField;        Layout.fillWidth: true; label: "YEAR";         placeholder: "2024"; inputMethodHints: Qt.ImhDigitsOnly }
                    EditField { id: trackField;       Layout.fillWidth: true; label: "TRACK #";      placeholder: "1"; inputMethodHints: Qt.ImhDigitsOnly }
                    EditField { id: discField;        Layout.fillWidth: true; label: "DISC #";       placeholder: "1"; inputMethodHints: Qt.ImhDigitsOnly }
                }

                EditField {
                    id: commentField
                    Layout.fillWidth: true
                    label: "COMMENT"
                    placeholder: "Notes…"
                    multiline: true
                }

                // --- Compact, secondary file info ---
                Text {
                    Layout.fillWidth: true
                    Layout.topMargin: 2
                    text: infoLine()
                    color: Qt.darker(theme.textSecondary, 1.25)
                    font.family: theme.fontFamily
                    font.pixelSize: 12
                    elide: Text.ElideRight
                }
            }
        }

        // ----- Footer: status + save -----
        RowLayout {
            Layout.fillWidth: true
            visible: backend.hasFile
            spacing: 16

            Text {
                id: statusText
                Layout.fillWidth: true
                font.family: theme.fontFamily
                font.pixelSize: 14
                elide: Text.ElideRight
                text: backend.statusMessage.length > 0 ? backend.statusMessage
                                                       : (backend.modified ? "Unsaved changes" : "")
                color: backend.status === MetadataController.Error ? theme.danger
                     : backend.status === MetadataController.Success ? theme.accentBright
                     : theme.textSecondary
                opacity: text.length > 0 ? 1 : 0
                Behavior on opacity { NumberAnimation { duration: 200 } }
            }

            SaveButton {
                id: saveButton
                label: "Save"
                onClicked: {
                    commitFields();
                    backend.save();
                }
            }
        }
    }

    // ----- Window-wide MP3 drag highlight -----
    Rectangle {
        anchors.fill: parent
        anchors.margins: 6
        radius: theme.radiusLarge
        color: "transparent"
        border.width: 3
        border.color: theme.accent
        opacity: mp3Drop.highlight ? 1 : 0
        Behavior on opacity { NumberAnimation { duration: 150 } }
    }
}
