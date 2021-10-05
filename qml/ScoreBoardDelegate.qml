import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0
import QtGraphicalEffects 1.13
MyRectangle{
    id: delegateBody
    clip: true
    color: "green"
    property string score: ""
    onScoreChanged: scoreText.text = score
    bottomBorderWidth: 1
    rightBorderWidth: 1
    property string text: ""
    layer.enabled: true
    layer.effect: OpacityMask{
        maskSource: Item {
            width: delegateBody.width
            height: delegateBody.height
            Rectangle{
                anchors.fill: parent
                radius: 10
            }
        }
    }
    Text {
        id: scoreText
        anchors.fill: parent
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        color: "white"
        font.pointSize: 18
        text: scoreTextRect.score
    }
}
