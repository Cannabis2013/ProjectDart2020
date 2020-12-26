import QtQuick 2.0

pragma Singleton

QtObject {
    // Tournament related values
    readonly property int firstToPost: 0x1
    readonly property int circular: 0x2
    // ScoreBoard related values
    readonly property int singleDimensional: 0x4
    readonly property int multiDimensional: 0x5
}
