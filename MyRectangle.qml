import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import ApplicationInterface 1.0

Rectangle{

    property int borderWidth: 0
    onBorderWidthChanged: {
        topBorder.height = borderWidth
        rightBorder.width = borderWidth
        bottomBorder.height = borderWidth
        leftBorder.width = borderWidth
    }

    property color borderColor: "black"
    onBorderColorChanged: {
        topBorder.color = borderColor
        rightBorder.color = borderColor
        bottomBorder.color = borderColor
        leftBorder.color = borderColor
    }

    property int topBorderWidth: 0
    property int rightBorderWidth: 0
    property int bottomBorderWidth: 0
    property int leftBorderWidth: 0

    onTopBorderWidthChanged: topBorder.height = topBorderWidth
    onRightBorderWidthChanged: rightBorder.width = rightBorderWidth
    onBottomBorderWidthChanged: bottomBorder.height= bottomBorderWidth
    onLeftBorderWidthChanged: leftBorder.width = leftBorderWidth

    property color topBorderColor: "black"
    property color rightBorderColor: "black"
    property color bottomBorderColor: "black"
    property color leftBorderColor: "black"

    onTopBorderColorChanged: topBorder.color = topBorderColor
    onRightBorderColorChanged: rightBorder.color = rightBorderColor
    onBottomBorderColorChanged: bottomBorder.color = bottomBorderColor
    onLeftBorderColorChanged: leftBorder.color = leftBorderColor

    color: "transparent"
    
    Rectangle{
        id: topBorder

        anchors.top: parent.top

        height: borderWidth
        width: parent.width
        
        color: "black"
    }
    Rectangle{
        id: rightBorder

        anchors.right: parent.right

        height: parent.height
        width: borderWidth

        color: "black"
    }
    Rectangle{
        id: bottomBorder

        anchors.bottom: parent.bottom

        height: borderWidth
        width: parent.width

        color: "black"
    }
    Rectangle{
        id: leftBorder

        anchors.left: parent.left

        height: parent.height
        width: borderWidth

        color: "black"
    }
}