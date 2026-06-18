import QtQuick

/*
 * Save button that morphs into a circular green checkmark on success and then
 * smoothly returns to its normal pill shape.
 *
 * Call showSuccess() after a successful save (driven from Main.qml).
 */
Item {
    id: root

    property string label: "Save"
    signal clicked()

    // "normal" -> pill with text, "success" -> green circle with a checkmark.
    property bool success: false

    implicitWidth: 200
    implicitHeight: 48

    function showSuccess() {
        success = true;
        revertTimer.restart();
    }

    Timer {
        id: revertTimer
        interval: 1500
        onTriggered: root.success = false
    }

    Rectangle {
        id: pill
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        height: root.height
        width: root.success ? root.height : root.width
        radius: height / 2
        color: root.success ? theme.accent
                            : (tap.pressed ? Qt.darker(theme.accent, 1.12)
                                           : (hover.hovered ? theme.accentBright : theme.accent))

        Behavior on width { NumberAnimation { duration: 360; easing.type: Easing.InOutQuad } }
        Behavior on color { ColorAnimation { duration: 140; easing.type: Easing.InOutQuad } }

        scale: (!root.success && tap.pressed) ? 0.98
                                              : ((!root.success && hover.hovered) ? 1.03 : 1.0)
        Behavior on scale { NumberAnimation { duration: 140; easing.type: Easing.OutCubic } }

        // Text label
        Text {
            anchors.centerIn: parent
            text: root.label
            color: theme.textOnAccent
            font.family: theme.fontFamily
            font.pixelSize: 15
            font.bold: true
            opacity: root.success ? 0 : 1
            Behavior on opacity { NumberAnimation { duration: 160 } }
        }

        // Checkmark (drawn on a canvas so it animates in cleanly)
        Canvas {
            id: check
            anchors.centerIn: parent
            width: 22
            height: 22
            opacity: root.success ? 1 : 0
            Behavior on opacity { NumberAnimation { duration: 200; easing.type: Easing.OutCubic } }

            onPaint: {
                const ctx = getContext("2d");
                ctx.reset();
                ctx.strokeStyle = theme.textOnAccent;
                ctx.lineWidth = 3;
                ctx.lineCap = "round";
                ctx.lineJoin = "round";
                ctx.beginPath();
                ctx.moveTo(width * 0.18, height * 0.52);
                ctx.lineTo(width * 0.42, height * 0.74);
                ctx.lineTo(width * 0.84, height * 0.28);
                ctx.stroke();
            }
        }

        HoverHandler { id: hover }
        TapHandler {
            id: tap
            enabled: !root.success
            onTapped: root.clicked()
        }
    }

    Theme { id: theme }
}
