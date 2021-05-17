import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Column
{
    id: verticalHeaderBody
    signal clearData()
    onClearData: verticalHeaderRepeater.model = 0
    property color backgroundColor: "transparent"
    onBackgroundColorChanged: cellBody.color = backgroundColor
    property int fontSize: 12
    onFontSizeChanged: cellBodyText.font.pointSize = verticalHeaderBody.fontSize
    property color fontColor: "black"
    onFontColorChanged: cellBodyText.color = fontColor
    property int cellWidth: 125
    onCellWidthChanged: {
        cellBody.width = cellWidth
        if(cellWidth > width)
            width = cellWidth
    }

    property int cellHeight: 25
    onCellHeightChanged: cellBody.height = cellHeight

    property int borderWidth: 0
    onBorderWidthChanged: cellBody.border.width = borderWidth

    property color borderColor : "black"
    onBorderColorChanged: cellBody.border.color = borderColor

    property int model: 0
    onModelChanged: verticalHeaderRepeater.model = model

    function dataCount()
    {
        return verticalHeaderRepeater.count;
    }

    function setData(i, value)
    {
        verticalHeaderRepeater.itemAt(i).children[4].text = value;
    }

    function setRowHeight(r,h)
    {
        verticalHeaderRepeater.itemAt(r).height = h;
    }

    Repeater
    {
        id: verticalHeaderRepeater
        model: verticalHeaderBody.model

        MyRectangle {
            id: cellBody

            width: verticalHeaderBody.width
            height: verticalHeaderBody.cellHeight

            rightBorderWidth: verticalHeaderBody.borderWidth
            bottomBorderWidth: verticalHeaderBody.borderWidth

            borderColor: verticalHeaderBody.borderColor
            color: backgroundColor
            Text {
                id: cellBodyText
                color: verticalHeaderBody.fontColor
                text: "Column text"
                font.pointSize: verticalHeaderBody.fontSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }
        
    }
}
