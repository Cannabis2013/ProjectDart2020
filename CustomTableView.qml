import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

TableView
{
    id: customTableViewBody

    interactive: false
    
    clip: true

    signal dataHasChanged

    readonly property int cellHeight: cellDelegate.height

    property color cellColor: "white"
    onCellColorChanged: cellDelegate.color = cellColor

    property color textColor: "black"
    onTextColorChanged: cellText = textColor

    property int fontSize: 16
    onFontSizeChanged: cellText.font.pointSize = fontSize

    property double cellBorderWidth: 0
    onCellBorderWidthChanged: cellDelegate.border.width = cellBorderWidth

    property color cellBorderColor: "black"
    onCellBorderColorChanged: cellDelegate.border.color = cellBorderColor

    property int horizontalTextAlignment: Text.AlignHCenter
    onHorizontalTextAlignmentChanged: cellText.horizontalAlignment = horizontalTextAlignment

    property int verticalTextAlignment: Text.AlignVCenter
    onVerticalTextAlignmentChanged: cellText.verticalAlignment = verticalTextAlignment

    property int verticalHeaderFillMode: 0x02
    onVerticalHeaderFillModeChanged: myModel.headerFillMode = verticalHeaderFillMode

    function getModel()
    {
        return myModel;
    }

    columnWidthProvider: function(column)
    {
        return myModel.columnWidthAt(column,"MS Sans Serif",fontSize);
    }

    model: ScoreDataModel
    {
        id: myModel

        headerFillMode : verticalHeaderFillMode

        columnWidthScale: 2

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
            font.pointSize: fontSize
        }
    }
}
