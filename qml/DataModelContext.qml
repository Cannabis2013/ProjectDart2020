import QtQuick 2.0
pragma Singleton

QtObject {
        // Header fillmodes values
        readonly property int numericFill: 0x1
        readonly property int fixedFill: 0x2
        readonly property int noFill: 0x3
        // Tablehint values
        readonly property int singleColumn: 0x4
        readonly property int multiColumn: 0x8
}
