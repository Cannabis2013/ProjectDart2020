import QtQuick 2.0
pragma Singleton

QtObject {
    // Header fillmodes values
    readonly property int numericFill: 0x1
    readonly property int fixedFill: 0x2
    // Tablehint values
    readonly property int singleThrowInput: 0x4
    readonly property int multiThrowInput: 0x8
}
