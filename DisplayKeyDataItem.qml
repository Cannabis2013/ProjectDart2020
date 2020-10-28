import QtQuick 2.0
import QtQuick.Layouts 1.3


/*
  Controller status table:
    -> GameControllerIdle = 0x9
    -> GamecontrollerBusy = 0xa
    -> GameControllerStopped = 0xb
    -> GameControllerAwaitsInput = 0xc
    -> GameControllerRunning = 0xd
    -> GameControllerWinnerDeclared = 0xe
    -> GameControllerNotInitialized = 0xf
  */

GridLayout{
    flow: GridLayout.TopToBottom
    anchors.fill: parent

    function setCurrentWinner(text)
    {
        winnerText.text = text;
    }

    function setThrowSuggestion(text)
    {
        suggestText.text = text;
    }

    Text {
        id: winnerText
        text: qsTr(textSourceContainer.winnerLabel)
        Layout.fillHeight: true
        Layout.fillWidth: true
        font.pointSize: 16
        Layout.alignment: Qt.AlignBottom
        color: ThemeContext.keyTextDisplayColor
    }
    Text {
        id: suggestText
        text: qsTr(textSourceContainer.throwSuggestLabel)
        Layout.fillHeight: true
        Layout.fillWidth: true
        font.pointSize: 16
        Layout.alignment: Qt.AlignTop
        color: ThemeContext.keyTextDisplayColor
    }
    Rectangle{
        Layout.fillHeight: true
    }
}
