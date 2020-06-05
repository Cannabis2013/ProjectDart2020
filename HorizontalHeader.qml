import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Row
{
    id: body

    Layout.row: 0
    Layout.column: 1

    property int cellWidth: 25
    onCellWidthChanged: cellBody.width = cellWidth

    property int model: 0
    onModelChanged: horizontalHeaderRepeater.model = model

    function dataCount()
    {
        return horizontalHeaderRepeater.count;
    }

    function setData(i, value)
    {
        horizontalHeaderRepeater.itemAt(i).children[0].text = value;
    }

    function setCellWidth(i, width)
    {
        horizontalHeaderRepeater.itemAt(i).width = width;
    }

    Repeater
    {
        id: horizontalHeaderRepeater
        model: body.model

        Rectangle {
            id: cellBody
            
            width: body.cellWidth
            height: 25
            
            color: "transparent"
            
            Text {
                id: headerCellText
                
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                
                anchors.fill: parent
            }
        }
        
    }
}
