import QtQuick
import QtQuick.Effects

/*
 * A rounded, elevated surface with a subtle drop shadow.
 *
 * The shadow is applied to a dedicated background rectangle (via a layer
 * effect) while child content is placed in a sibling item on top, so text and
 * controls stay crisp and are never rasterised by the effect.
 */
Item {
    id: root

    property color color: theme.card
    property color hoverColor: theme.cardHover
    property bool hoverable: false
    property real radius: theme.radiusLarge

    // Children declared inside a Card land in the content item above the shadow.
    default property alias content: contentItem.data

    readonly property bool hovered: hoverHandler.hovered

    Rectangle {
        id: background
        anchors.fill: parent
        radius: root.radius
        color: (root.hoverable && hoverHandler.hovered) ? root.hoverColor : root.color

        Behavior on color {
            ColorAnimation { duration: 180; easing.type: Easing.InOutQuad }
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowColor: "#66000000"
            shadowBlur: 0.45
            shadowVerticalOffset: 5
            autoPaddingEnabled: true
        }
    }

    HoverHandler { id: hoverHandler }

    Item {
        id: contentItem
        anchors.fill: parent
    }

    Theme { id: theme }
}
