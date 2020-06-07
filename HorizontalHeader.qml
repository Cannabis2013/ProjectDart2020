import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Row
{
    id: body

    Layout.row: 0
    Layout.column: 1

    property color backgroundColor: "transparent"
    onBackgroundColorChanged: cellBody.color = backgroundColor

    property color color: "black"
    onColorChanged: cellBodyText.color = color

    property int cellWidth: 25
    onCellWidthChanged: cellBody.width = cellWidth

    property int cellHeight: 25
    onCellHeightChanged: cellBody.height = cellHeight

    property int borderWidth: 0
    onBorderWidthChanged: {
        cellBody.bottomBorderWidth = borderWidth
        cellBody.rightBorderWidth = borderWidth
    }

    property color borderColor : "black"
    onBorderColorChanged: cellBody.border.color = borderColor

    property int model: 0
    onModelChanged: horizontalHeaderRepeater.model = model

    function dataCount()
    {
        return horizontalHeaderRepeater.count;
    }

    function setData(i, value)
    {
        horizontalHeaderRepeater.itemAt(i).children[4].text = value;
    }

    function setCellWidth(i, width)
    {
        horizontalHeaderRepeater.itemAt(i).width = width;
    }

    Repeater
    {
        id: horizontalHeaderRepeater
        model: body.model

        MyRectangle {
            id: cellBody
            
            width: body.cellWidth
            height: body.height

            rightBorderWidth: body.borderWidth
            bottomBorderWidth: body.borderWidth

            borderColor: body.borderColor

            color: body.backgroundColor

            Text {
                id: cellBodyText

                color: body.color

                font.pointSize: 12

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                
                anchors.fill: parent
            }
        }
        
    }
}
