import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
        id: myRectangleBody
        color: "transparent"
        property int borderWidth: 0
        onBorderWidthChanged: {
                topBorder.height = borderWidth
                rightBorder.width = borderWidth
                bottomBorder.height = borderWidth
                leftBorder.width = borderWidth
        }
        property int topBorderWidth: 0
        onTopBorderWidthChanged: topBorder.height = topBorderWidth
        property int rightBorderWidth: 0
        onRightBorderWidthChanged: rightBorder.width = rightBorderWidth
        property int bottomBorderWidth: 0
        onBottomBorderWidthChanged: bottomBorder.height = bottomBorderWidth
        property int leftBorderWidth: 0
        onLeftBorderWidthChanged: leftBorder.width = leftBorderWidth

        property color borderColor: "black"
        property color topBorderColor: "black"
        property color rightBorderColor: "black"
        property color bottomBorderColor: "black"
        property color leftBorderColor: "black"

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
        Rectangle {
                id: topBorder
                anchors.top: parent.top
                height: myRectangleBody.borderWidth
                width: parent.width
                color: "black"
        }
        Rectangle {
                id: rightBorder
                anchors.right: parent.right
                height: parent.height
                width: myRectangleBody.borderWidth
                color: "black"
        }
        Rectangle {
                id: bottomBorder
                anchors.bottom: parent.bottom
                height: myRectangleBody.borderWidth
                width: parent.width
                color: "black"
        }
        Rectangle {
                id: leftBorder
                anchors.left: parent.left
                height: parent.height
                width: myRectangleBody.borderWidth
                color: "black"
        }
}
