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

    property double cellBorderWidth: 0
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
    
    delegate: MyRectangle{
        id: cellDelegate

        bottomBorderWidth: 1
        rightBorderWidth: 1

        implicitWidth: 25
        implicitHeight: 25

        color: cellColor

        PropertyAnimation on rotation
        {
            from: 90
            to: 0

            duration: 500

            loops: 1
        }

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
