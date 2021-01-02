import QtQuick 2.0

Rectangle{
    color: "transparent"
    clip: true
    signal valueChanged(var val)
    property var currentValue
    property int currentIndex: -1
    property int fontSize: 12
}
