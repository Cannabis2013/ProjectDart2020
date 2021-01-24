import QtQuick 2.0

pragma Singleton

QtObject {
    // Gamemode values
    readonly property int firstToPost: 0x1
    readonly property int circular: 0x2
    // Input mode values
    readonly property int pointMode: 0x5
    readonly property int scoreMode: 0x6
    // ??
    readonly property int numberPad: 0x7
    readonly property int hotPad: 0x8
    readonly property int modifierPad: 0x9
    readonly property int actionPad: 0xA
}
