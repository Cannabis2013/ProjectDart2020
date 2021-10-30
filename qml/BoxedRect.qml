import QtQuick 2.0
import QtQuick.Layouts 1.3
MyRectangle {
    clip: true
    property Item contentRect: Item{}
    onContentRectChanged: {
        layout.children[4] = contentRect;
        contentRect.Layout.fillWidth = true;
        contentRect.Layout.fillHeight = true;
        contentRect.Layout.column = 1;
        contentRect.Layout.row = 1;
    }
    property int padding: 0
    onPaddingChanged: {
        setWidth(leftPadding,padding);
        setWidth(rightPadding,padding);
        setHeight(topPadding,padding);
        setHeight(bottomPadding,padding);
    }
    property int paddingTop: 0
    onPaddingTopChanged: setHeight(topPadding,paddingTop)
    property int paddingLeft: 0
    onPaddingLeftChanged: setWidth(leftPadding,paddingLeft)
    property int paddingRight: 0
    onPaddingRightChanged: setWidth(rightPadding,paddingRight)
    property int paddingBottom: 0
    onPaddingBottomChanged: setHeight(bottomPadding,paddingBottom)
    function setHeight(ref, height)
    {
        ref.Layout.minimumHeight = height;
        ref.Layout.maximumHeight = height;
    }
    function setWidth(ref, width)
    {
        ref.Layout.minimumWidth = width;
        ref.Layout.maximumWidth = width;
    }

    GridLayout{
        id: layout
        anchors.fill: parent
        columns: 3
        rows: 3
        Rectangle{
            id: topPadding
            Layout.column: 0
            Layout.row: 0
            Layout.columnSpan: 3
            Layout.minimumHeight: paddingTop
            Layout.maximumHeight: paddingTop
        }
        Rectangle
        {
            id: leftPadding
            Layout.column: 0
            Layout.row: 1
            width: paddingLeft
            Layout.minimumWidth: paddingLeft
            Layout.maximumWidth: paddingLeft
        }
        Rectangle
        {
            id: rightPadding
            Layout.column: 2
            Layout.row: 1
            Layout.minimumWidth: paddingRight
            Layout.maximumWidth: paddingRight
        }
        Rectangle
        {
            id: bottomPadding
            Layout.column: 0
            Layout.row: 2
            Layout.columnSpan: 3
            Layout.minimumHeight: paddingBottom
            Layout.maximumHeight: paddingBottom
        }
        Item{
            id: bodyRect
        }
    }
}
