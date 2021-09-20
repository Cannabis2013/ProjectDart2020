import QtQuick 2.0
/*
  Interface that provides a basis for any implementations of virtual keyboards.
  */
Rectangle {
    color: "transparent"
    // This is the signal that is exposed to the public
    signal sendInput(int value, int keyCode)
    signal keyClicked(int val, int modifierCode)
    signal internalHotKeyClicked(int value)
    signal internalKeyClicked(int value)
    signal enableKeyPad(bool enable)
}
