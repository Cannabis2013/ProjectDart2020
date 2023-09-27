import QtQuick 2.0

InteractiveObject {
        property string text: ""
        property double backgroundTransparency: 1
        property int fontSize: 12
        property color hoveredColor: "#04F72D"
        property color hoveredTextColor: textColor
        property color backgroundColor: "transparent"
        property color textColor: "black"
        property bool hoverEnabled: true
        property color pressedColor: backgroundColor
        property double pressedScale: 0.90
        property bool isCheckable: false
        property bool checked: false
        property color checkedBackgroundColor: backgroundColor
        property color checkedTextColor: "black"
        property double checkedScale: 1
        property bool enablePressAndHold: false
        property int buttonRadius: 0
        property url image: ""
        property int imageMargins: 0
        property int imageRotation: 0
        signal clicked
        signal pressAndHoldClicked
        signal enableButton(bool e)
        signal hoveredChanged(bool status)
        signal checkStateChanged(bool check)
}
