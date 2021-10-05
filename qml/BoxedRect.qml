import QtQuick 2.0
import QtQuick.Layouts 1.3

MyRectangle {
    property Item contentRect: Item{}
    onContentRectChanged: {
        layout.children[4] = contentRect;
        contentRect.Layout.fillWidth = true;
        contentRect.Layout.fillHeight = true;
    }

    property int padding: 0
    onPaddingChanged: {
        leftPadding.width = padding
        rightPadding.width = padding
        topPadding.height = padding
        bottomPadding.height = padding
    }
    property int paddingTop: 0
    onPaddingTopChanged: topPadding.height = paddingTop
    property int paddingLeft: 0
    onPaddingLeftChanged: leftPadding.width = paddingLeft
    property int paddingRight: 0
    onPaddingRightChanged: rightPadding.width = paddingRight
    property int paddingBottom: 0
    onPaddingBottomChanged: bottomPadding.height = paddingBottom
    GridLayout{
        id: layout
        anchors.fill: parent
        columns: 3
        rows: 3
        Rectangle
        {
            id: leftPadding
            Layout.column: 0
            Layout.row: 1
            width: 0
        }
        Rectangle{
            id: topPadding
            Layout.column: 0
            Layout.row: 0
            Layout.columnSpan: 3
            width: 0
        }
        Rectangle
        {
            id: rightPadding
            Layout.column: 2
            Layout.row: 1
            width: 0
        }
        Rectangle
        {
            id: bottomPadding
            Layout.column: 0
            Layout.row: 2
            Layout.columnSpan: 3
            width: 0
        }
        Item{
            id: bodyRect
        }
    }

}
