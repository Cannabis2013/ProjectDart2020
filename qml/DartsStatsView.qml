import QtQuick 2.0
import QtQuick.Layouts 1.3
MyRectangle{
    id: statsBody
    clip: true
    property string minValue: ""
    onMinValueChanged: minValueText.text = "L: " + minValue
    property string midValue: ""
    onMidValueChanged: midValueText.text = "M: " + midValue
    property string maxValue: ""
    onMaxValueChanged: maxValueText.text = "H: " + maxValue
    property int fontSize: 12
    onFontSizeChanged: {
        minValueText.font.pointSize = fontSize;
        midValueText.font.pointSize = fontSize;
        maxValueText.font.pointSize = fontSize
    }

    GridLayout{
        flow: GridLayout.LeftToRight
        Text {
            id: minValueText
            horizontalAlignment: Qt.AlignLeft
            color: "white"
            font.pointSize: 10
            text: "L: " + statsBody.minValue
        }
        Text {
            id: midValueText
            horizontalAlignment: Qt.AlignLeft
            color: "white"
            font.pointSize: 10
            text: "M: " + statsBody.midValue
        }
        Text {
            id: maxValueText
            horizontalAlignment: Qt.AlignLeft
            color: "white"
            font.pointSize: 12
            text: "H: " + statsBody.maxValue
        }
        Rectangle{
            Layout.fillWidth: true
        }
    }
}
