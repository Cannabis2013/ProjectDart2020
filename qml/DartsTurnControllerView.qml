import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

import "turnControllerScripts.js" as TurnControllerScripts

Rectangle{
    clip: true
    color: "transparent"
    width: 128
    property string currentRoundIndex: ""
    onCurrentRoundIndexChanged: currentRoundLabel.text = currentRoundIndex
    property string currentPlayer: ""
    onCurrentPlayerChanged: currentPlayerLabel.text = currentPlayer
    GridLayout{
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        Label{
            id: currentRoundLabel
            color: ThemeContext.navTextDisplayColor
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: currentRoundIndex
            font.pointSize: 20
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }
        Label{
            id: currentPlayerLabel
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"
            text: currentPlayer
            font.pointSize: 20
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
