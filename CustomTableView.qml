import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

TableView
{
    id: body
    
    clip: true

    signal dataHasChanged

    property color cellColor: "white"
    onCellColorChanged: cellDelegate.color = cellColor

    property color textColor: "black"
    onTextColorChanged: cellText = textColor

    property int cellBorderWidth: 0
    onCellBorderWidthChanged: cellDelegate.border.width = cellBorderWidth

    property color cellBorderColor: "black"
    onCellBorderColorChanged: cellDelegate.border.color = cellBorderColor

    property int horizontalTextAlignment: Text.AlignHCenter
    onHorizontalTextAlignmentChanged: cellText.horizontalAlignment = horizontalTextAlignment

    property int verticalTextAlignment: Text.AlignVCenter
    onVerticalTextAlignmentChanged: cellText.verticalAlignment = verticalTextAlignment

    function getModel()
    {
        return myModel;
    }
    
    columnWidthProvider: function(column)
    {
        return myModel.columnWithAt(column);
    }
    
    model: CustomTableModel
    {
        id: myModel
        
        // Signal handling
        onDataChanged: dataHasChanged()
    }
    
    delegate: Rectangle{
        id: cellDelegate

        border.color: cellBorderColor
        border.width: cellBorderWidth

        implicitWidth: 25
        implicitHeight: 25

        color: cellColor
        
        Text {
            id: cellText
            horizontalAlignment: horizontalTextAlignment
            verticalAlignment: verticalTextAlignment
            anchors.fill: parent
            text: display
            color: textColor
        }
    }
}
