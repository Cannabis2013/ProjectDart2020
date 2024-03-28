import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "inputDisplay.js" as Scripts

Item {
        property string inputsText: ""
        onInputsTextChanged: textInputs.text = inputsText

        property string scoreText: ""
        onScoreTextChanged: textScore.text = scoreText

        Rectangle {
                clip: true
                color: "#4f4f4f"
                radius: 12
                width: parent.width
                height: 32
                anchors.centerIn: parent
                Text {
                        id: textInputs
                        color: "white"
                        font.pixelSize: 18
                        font.weight: Font.Bold
                        width: 160
                        height: parent.height
                        anchors.left: parent.left
                        anchors.leftMargin: 12
                        verticalAlignment: Text.AlignVCenter
                }

                Rectangle {
                        color: "white"
                        width: 1
                        height: parent.height
                        anchors.right: textScore.left
                }

                Text {
                        id: textScore
                        anchors.right: parent.right
                        anchors.rightMargin: 12
                        width: 36
                        height: parent.height
                        font.pixelSize: 18
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignRight
                }
        }
}
