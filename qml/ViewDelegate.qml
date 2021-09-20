import QtQuick 2.0
InteractiveObject {
    id: viewDelegate
    property int roundedCorners: 0
    property bool noDelayPressSelect: false
    property bool isCheckable: false
    property bool checked: false
    property color selectedColor: backgroundRect.color
    property color selectedTextColor: backgroundColor
    property double selectedSizeScale: 0.98
    property string title: ""
    property color labelBackgroundColor: "transparent"
    property color descriptionBackgroundColor : "transparent"
    property string description: ""
    property int titleFontSize: 10
    property int descriptionFontSize: 8
    property color titleFontColor: "black"
    property color descriptionFontColor: "white"
    property color imageBackgroundColor: "transparent"
    property color backgroundColor: "darkgray"
    onBackgroundColorChanged: backgroundRect.color = backgroundColor
    property double backgroundOpacity: 0.3
    onBackgroundOpacityChanged: backgroundRect.opacity = backgroundOpacity
    property bool enableHover: true
    property double hoveredSizeScale: 0.98
    property color hoveredColor: "transparent"
    property color hoveredTitleColor: titleFontColor
    property color hoveredDescriptionColor: descriptionFontColor
    property url logoUrl: ""
    property int radius: 5
    onRadiusChanged: maskRect.radius = radius
    Rectangle{
        id: backgroundRect
        anchors.fill: parent
        color: viewDelegate.backgroundColor
        opacity: viewDelegate.backgroundOpacity
        border.width: 1
        border.color: "black"
        radius: 5
    }
}
