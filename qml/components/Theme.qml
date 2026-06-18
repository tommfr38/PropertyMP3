import QtQuick

// Central palette + metrics for the Spotify-inspired dark theme.
// Instantiated locally in components that need it: `Theme { id: theme }`.
QtObject {
    readonly property color background:   "#121212"
    readonly property color card:         "#181818"
    readonly property color cardHover:    "#282828"
    readonly property color field:        "#2A2A2A"
    readonly property color fieldBorder:  "#3E3E3E"

    readonly property color accent:       "#1DB954"
    readonly property color accentBright: "#1ED760"

    readonly property color textPrimary:   "#FFFFFF"
    readonly property color textSecondary: "#B3B3B3"
    readonly property color textOnAccent:  "#000000"
    readonly property color danger:        "#F0626E"

    readonly property int radius:      10
    readonly property int radiusLarge: 12

    // Falls back to the Qt default automatically if Inter is not installed.
    readonly property string fontFamily: "Inter"
}
