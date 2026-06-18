import QtQuick
import QtQuick.Controls.Basic

/*
 * An editable "tile": a rounded card holding a label and a text input. The
 * whole tile lightens on hover and glows green while focused.
 *
 * `text` reflects whichever editor (single line / multiline) is active. Call
 * set(value) to populate it — this avoids two-way binding loops with the
 * backend.
 */
Item {
    id: root

    property string label: ""
    property string placeholder: ""
    property bool multiline: false
    property int inputMethodHints: Qt.ImhNone

    readonly property string text: multiline ? area.text : line.text
    function set(value) {
        line.text = value;
        area.text = value;
    }

    readonly property bool editorFocused: line.activeFocus || area.activeFocus

    implicitHeight: col.implicitHeight + 24
    implicitWidth: 200

    Rectangle {
        id: tile
        anchors.fill: parent
        radius: theme.radius
        color: root.editorFocused ? Qt.lighter(theme.card, 1.25)
                                  : (hover.hovered ? theme.cardHover : theme.card)
        border.width: root.editorFocused ? 2 : 1
        border.color: root.editorFocused ? theme.accent : "#2C2C2C"

        Behavior on color { ColorAnimation { duration: 160; easing.type: Easing.InOutQuad } }
        Behavior on border.color { ColorAnimation { duration: 160; easing.type: Easing.InOutQuad } }

        HoverHandler { id: hover }

        Column {
            id: col
            anchors.fill: parent
            anchors.margins: 12
            spacing: 5

            Text {
                text: root.label
                color: root.editorFocused ? theme.accent : theme.textSecondary
                font.family: theme.fontFamily
                font.pixelSize: 11
                font.bold: true
                font.letterSpacing: 0.5
                Behavior on color { ColorAnimation { duration: 160 } }
            }

            TextField {
                id: line
                visible: !root.multiline
                width: parent.width
                padding: 0
                color: theme.textPrimary
                placeholderText: root.placeholder
                placeholderTextColor: Qt.darker(theme.textSecondary, 1.2)
                selectionColor: theme.accent
                selectedTextColor: theme.textOnAccent
                font.family: theme.fontFamily
                font.pixelSize: 16
                inputMethodHints: root.inputMethodHints
                background: null
            }

            ScrollView {
                id: areaScroll
                visible: root.multiline
                width: parent.width
                height: 76
                clip: true

                TextArea {
                    id: area
                    padding: 0
                    color: theme.textPrimary
                    placeholderText: root.placeholder
                    placeholderTextColor: Qt.darker(theme.textSecondary, 1.2)
                    selectionColor: theme.accent
                    selectedTextColor: theme.textOnAccent
                    font.family: theme.fontFamily
                    font.pixelSize: 15
                    wrapMode: TextArea.Wrap
                    background: null
                }
            }
        }
    }

    Theme { id: theme }
}
