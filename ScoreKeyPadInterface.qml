import QtQuick 2.0

Rectangle {
    color: "transparent"
    anchors.fill: parent
    // This is the signal that is exposed to the public
    signal sendInput(int value)
    signal keyClicked(int val)
    signal internalHotKeyClicked(int value)
    signal internalKeyClicked(int value)
    signal enableKeyPad(bool enable)
}
