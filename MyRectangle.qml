import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import ApplicationInterface 1.0

Rectangle{

    id: body

    property int borderWidth: 0

    // Only affects outer boundaries leaves middle border unaffected
    onBorderWidthChanged: {
        topBorder.height = borderWidth
        rightBorder.width = borderWidth
        bottomBorder.height = borderWidth
        leftBorder.width = borderWidth
    }

    property int topBorderWidth: 0
    property int rightBorderWidth: 0
    property int bottomBorderWidth: 0
    property int leftBorderWidth: 0
    property int middleBorderWidth: 0

    onTopBorderWidthChanged: topBorder.height = topBorderWidth
    onRightBorderWidthChanged: rightBorder.width = rightBorderWidth
    onBottomBorderWidthChanged: bottomBorder.height= bottomBorderWidth
    onLeftBorderWidthChanged: leftBorder.width = leftBorderWidth
    onMiddleBorderWidthChanged: middleBorder.width = middleBorderWidth

    property color borderColor: "black"
    property color topBorderColor: "black"
    property color rightBorderColor: "black"
    property color bottomBorderColor: "black"
    property color leftBorderColor: "black"
    property color middleBorderColor: "white"

    onBorderColorChanged: {
        topBorder.color = borderColor
        rightBorder.color = borderColor
        bottomBorder.color = borderColor
        leftBorder.color = borderColor
    }

    onTopBorderColorChanged: topBorder.color = topBorderColor
    onRightBorderColorChanged: rightBorder.color = rightBorderColor
    onBottomBorderColorChanged: bottomBorder.color = bottomBorderColor
    onLeftBorderColorChanged: leftBorder.color = leftBorderColor
    onMiddleBorderColorChanged: middleBorder.color = middleBorderColor

    color: "transparent"

    Rectangle{
        id: topBorder

        anchors.top: parent.top

        height: body.borderWidth
        width: parent.width
        
        color: "black"
    }
    Rectangle{
        id: rightBorder

        anchors.right: parent.right

        height: parent.height
        width: body.borderWidth

        color: "black"
    }
    Rectangle{
        id: bottomBorder

        anchors.bottom: parent.bottom

        height: body.borderWidth
        width: parent.width

        color: "black"
    }
    Rectangle{
        id: leftBorder

        anchors.left: parent.left

        height: parent.height
        width: body.borderWidth

        color: "black"
    }

    Rectangle{
        id: middleBorder

        anchors.verticalCenter: body.verticalCenter

        height: body.middleBorderWidth
        width: body.width

        color: "black"
    }
}
