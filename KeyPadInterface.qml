import QtQuick 2.0
/*
  Interface that provides a basis for any implementations of virtual keyboards.
  */
Rectangle {
    signal keyClicked(int val, int modifierCode)
    signal internalKeyClicked(int value)
    signal sendInput(int value, int keyCode)
    property bool enableKeys: false
}
