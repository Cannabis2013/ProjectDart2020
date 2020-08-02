import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

MyRectangle{
    id: cellDelegate
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
    bottomBorderWidth: 1
    rightBorderWidth: 1
    
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
        font.pointSize: fontSize
    }
}
