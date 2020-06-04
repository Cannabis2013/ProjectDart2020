import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Column
{
    id: body

    Layout.row: 1
    Layout.column: 0

    property int cellWidth: 25
    onCellWidthChanged: cell.width = cellWidth

    property int model: 0
    onModelChanged: verticalHeaderRepeater.model = model

    function dataCount()
    {
        return verticalHeaderRepeater.count;
    }

    function setData(i, value)
    {

        verticalHeaderRepeater.itemAt(i).children[0].text = value;
    }

    Repeater
    {
        id: verticalHeaderRepeater
        model: body.model
        Rectangle {
            id: cell
            width: body.cellWidth
            height: 25
            
            color: "transparent"
            
            Text {
                id: verticalHeaderCellText
                
                text: "Column text"
                
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                
                anchors.fill: parent
            }
        }
        
    }
}
