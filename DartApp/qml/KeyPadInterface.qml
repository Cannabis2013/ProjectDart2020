import QtQuick 2.0

Rectangle {
    color: "transparent"
    signal sendInput(int value, int keyCode)
    signal keyClicked(int val, int modifierCode)
    signal internalHotKeyClicked(int value)
    signal internalKeyClicked(int value)
    signal enableKeyPad(bool enable)
}
