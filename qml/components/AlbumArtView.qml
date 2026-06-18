import QtQuick
import QtQuick.Effects

/*
 * Large, rounded album-art display.
 *
 *  - Rounded corners are produced by masking with a MultiEffect (QtQuick.Effects,
 *    a base Qt 6 module) rather than Qt5Compat.GraphicalEffects' OpacityMask, so
 *    the Windows build no longer needs the fragile Qt5Compat add-on.
 *  - Replacing the art cross-fades between two stacked Image layers.
 *  - The user can click the art or drop a JPG/PNG onto it to replace it.
 */
Item {
    id: root

    property url source: ""
    signal clicked()
    signal imageDropped(string url)

    // Which of the two layers is currently shown in front.
    property bool frontIsA: true

    onSourceChanged: _loadSource()

    function _loadSource() {
        if (source == "") {
            imgA.opacity = 0;
            imgB.opacity = 0;
            imgA.source = "";
            imgB.source = "";
            return;
        }
        // Load into the back layer; the cross-fade runs once it is ready.
        if (frontIsA)
            imgB.source = source;
        else
            imgA.source = source;
    }

    function _crossFadeTo(backIsA) {
        if (backIsA) {
            imgA.opacity = 1;
            imgB.opacity = 0;
            frontIsA = true;
        } else {
            imgB.opacity = 1;
            imgA.opacity = 0;
            frontIsA = false;
        }
    }

    // --- Masked, rounded artwork stack -------------------------------------
    Item {
        id: artStack
        anchors.fill: parent

        layer.enabled: true
        layer.effect: MultiEffect {
            maskEnabled: true
            maskSource: maskRect
        }

        Rectangle {
            anchors.fill: parent
            color: theme.field
        }

        Image {
            id: imgA
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            asynchronous: true
            cache: false
            opacity: 0
            onStatusChanged: if (status === Image.Ready && !root.frontIsA) root._crossFadeTo(true)
            Behavior on opacity { NumberAnimation { duration: 350; easing.type: Easing.InOutQuad } }
        }

        Image {
            id: imgB
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            asynchronous: true
            cache: false
            opacity: 0
            onStatusChanged: if (status === Image.Ready && root.frontIsA) root._crossFadeTo(false)
            Behavior on opacity { NumberAnimation { duration: 350; easing.type: Easing.InOutQuad } }
        }
    }

    // Mask defining the rounded shape (not drawn directly). MultiEffect.maskSource
    // requires a texture provider, so layer.enabled is set (unlike the old
    // OpacityMask, which accepted a plain invisible item).
    Rectangle {
        id: maskRect
        anchors.fill: parent
        radius: theme.radiusLarge
        visible: false
        layer.enabled: true
    }

    // --- Placeholder shown when there is no cover --------------------------
    Column {
        anchors.centerIn: parent
        spacing: 10
        opacity: root.source == "" ? 1 : 0
        visible: opacity > 0
        Behavior on opacity { NumberAnimation { duration: 250 } }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "♪"          // musical note
            color: theme.textSecondary
            font.pixelSize: 48
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Add cover art"
            color: theme.textSecondary
            font.family: theme.fontFamily
            font.pixelSize: 14
        }
    }

    // --- Hover overlay (click to change) -----------------------------------
    Rectangle {
        id: hoverOverlay
        anchors.fill: parent
        radius: theme.radiusLarge
        color: "#000000"
        opacity: (hover.hovered && root.source != "") ? 0.45 : 0.0
        Behavior on opacity { NumberAnimation { duration: 180 } }

        Text {
            anchors.centerIn: parent
            text: "Change cover"
            color: theme.textPrimary
            font.family: theme.fontFamily
            font.pixelSize: 14
            font.bold: true
            opacity: parent.opacity > 0 ? 1 : 0
        }
    }

    // --- Drag highlight ----------------------------------------------------
    Rectangle {
        anchors.fill: parent
        radius: theme.radiusLarge
        color: "transparent"
        border.width: 3
        border.color: theme.accent
        opacity: dropArea.highlight ? 1 : 0
        Behavior on opacity { NumberAnimation { duration: 150 } }
    }

    HoverHandler { id: hover }

    TapHandler {
        onTapped: root.clicked()
    }

    DropArea {
        id: dropArea
        anchors.fill: parent

        property bool highlight: false

        onEntered: function (drag) {
            highlight = drag.hasUrls && backend.isImage(drag.urls[0].toString());
            if (!highlight)
                drag.accepted = false;
        }
        onExited: highlight = false
        onDropped: function (drop) {
            highlight = false;
            if (drop.hasUrls && backend.isImage(drop.urls[0].toString()))
                root.imageDropped(drop.urls[0].toString());
        }
    }

    Theme { id: theme }
}
