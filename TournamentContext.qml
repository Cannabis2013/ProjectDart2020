import QtQuick 2.0

pragma Singleton

QtObject {
    // Tournament related values
    readonly property int firstToPost: 0x1
    readonly property int circular: 0x2

    readonly property int pointMode: 0x5
    readonly property int scoreMode: 0x6
}
