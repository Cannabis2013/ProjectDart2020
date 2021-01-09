import QtQuick 2.0

Rectangle{
    color: "transparent"
    clip: true
    signal valueChanged(var val)
    signal setValue(var value)
    property var currentValue
    property int currentIndex: -1
    property int fontSize: 12

}
