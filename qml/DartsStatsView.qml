import QtQuick 2.0
import QtQuick.Layouts 1.3
Rectangle {
    color: "transparent"
    id: statsBody
    height: 20
    clip: true
    property string averageValue: ""
    onAverageValueChanged: averageValueText.text = "Avg: " + averageValue
    property string lowerValue: ""
    onLowerValueChanged: lowestValueText.text = "L: " + lowerValue
    property string upperValue: ""
    onUpperValueChanged: highestValueText.text = "H: " + upperValue
    GridLayout{
        anchors.fill: parent
        flow: GridLayout.LeftToRight
        Text {
            id: averageValueText
            Layout.minimumWidth: 56
            Layout.maximumWidth: 56
            horizontalAlignment: Qt.AlignLeft
            color: "white"
            font.pointSize: 12
            text: "Avg: " + statsBody.averageValue
        }
        Text {
            id: lowestValueText
            Layout.minimumWidth: 52
            Layout.maximumWidth: 52
            horizontalAlignment: Qt.AlignLeft
            color: "white"
            font.pointSize: 12
            text: "L: " + statsBody.lowerValue
        }
        Text {
            id: highestValueText
            Layout.minimumWidth: 52
            Layout.maximumWidth: 52
            horizontalAlignment: Qt.AlignLeft
            color: "white"
            font.pointSize: 12
            text: "H: " + statsBody.upperValue
        }
        Rectangle{
            color: "transparent"
            Layout.fillWidth: true
        }
    }
}
