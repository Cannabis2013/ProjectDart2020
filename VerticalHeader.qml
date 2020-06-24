import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Column
{
    id: body

    property color backgroundColor: "transparent"
    onBackgroundColorChanged: cellBody.color = backgroundColor

    property color color: "black"
    onColorChanged: cellBodyText.color = color
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
        model: body.model

        MyRectangle {
            id: cellBody

            width: body.width
            height: body.cellHeight

            rightBorderWidth: body.borderWidth
            bottomBorderWidth: body.borderWidth

            borderColor: body.borderColor

            color: backgroundColor
            
            Text {
                id: cellBodyText

                color: body.color
                
                text: "Column text"

                font.pointSize: 12
                
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                
                anchors.fill: parent
            }
        }
        
    }
}
