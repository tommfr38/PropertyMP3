import QtQuick
import QtQuick.Controls.Basic

// Pill-shaped button that brightens and scales up slightly on hover.
Button {
    id: control

    property color baseColor: theme.accent
    property color textColor: theme.textOnAccent

    implicitHeight: 44
    leftPadding: 22
    rightPadding: 22
    font.family: theme.fontFamily
    font.pixelSize: 14
    font.bold: true

    scale: control.down ? 0.98 : (control.hovered ? 1.03 : 1.0)
    Behavior on scale {
        NumberAnimation { duration: 140; easing.type: Easing.OutCubic }
    }

    background: Rectangle {
        radius: height / 2
        color: control.down ? Qt.darker(control.baseColor, 1.12)
                             : (control.hovered ? theme.accentBright : control.baseColor)
        Behavior on color {
            ColorAnimation { duration: 140; easing.type: Easing.InOutQuad }
        }
    }

    contentItem: Text {
        text: control.text
        color: control.textColor
        font: control.font
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    Theme { id: theme }
}
