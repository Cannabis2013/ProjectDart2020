import QtQuick 2.0
/*
  Interface that provides a basis for any implementations of virtual keyboards.
  */
Rectangle {
    color: "transparent"
    anchors.fill: parent

    signal keyClicked(int val, int modifierCode)
    signal internalHotKeyClicked(int value)
    signal internalKeyClicked(int value)
    signal sendInput(int value, int keyCode)
    signal enableKeyPad(bool enable)
}
