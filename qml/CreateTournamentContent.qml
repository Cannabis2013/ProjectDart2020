import QtQuick 2.0
import QtQuick.Layouts 1.3

import "createTournamentScripts.js" as CreateScripts

Content {
    id: createBody
    color: "transparent"

    signal requestPlayers
    signal sendDartsDetails(string json)
    signal tournamentAssembledAndStored()
    onTournamentAssembledAndStored: {
        if(status)
        {
            requestQuit();
        }
        else
        {
            buttonsComponent.buttonOneEnabled = true;
            buttonsComponent.buttonTwoEnabled = true;
        }
    }

    signal sendCricketDetails
    signal requestGameModes

    minimumHeight: 538

    QtObject{
        id: sendPlayerState
        property bool playerSent: false
        readonly property int updateCount: 2
    }

    onRequestUpdate: {
        requestPlayers();
    }

    function selectorComponent()
    {
        return selectorLoader.item;
    }

    GridLayout{
        flow: GridLayout.TopToBottom
        anchors.fill: parent
        rowSpacing: 3
        DefaultTextInputBox {
            id: titleEdit
            Layout.fillWidth: true
            onValueChanged: CreateScripts.stateChanged()
        }
        DefaultComboBox{
            id: gameModeSelector
            labelText: "Game modes"
            Layout.fillWidth: true
            model: ["FirstToPost"]
            onValueChanged: CreateScripts.setupSelectors()
        }

        Loader{
            id: selectorLoader
            Layout.fillWidth: true
        }

        Rectangle{
            height: 10
        }

        DefaultPlayerListView {
            id: playersListView
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            onItemSelected: CreateScripts.stateChanged()
        }

        MyRectangle{
            Layout.fillWidth: true
            height: 32
        }
        /*
          Save button clicked
          */
        ButtonsComponent {
            id: buttonsComponent
            height: 30
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignBottom |Qt.AlignHCenter
            buttonOneTitle: "Back"
            buttonTwoTitle: "Save tournament"
            buttonTwoEnabled: false
            buttonBackgroundColor: ThemeContext.touButtonBackgroundColor
            onButtonOneClicked: requestQuit()
            onButtonTwoClicked: CreateScripts.acceptAndAdd()
        }
        Component.onCompleted: {
            applicationInterface.tournamentCreatedSuccess.connect(createBody.tournamentAssembledAndStored);
            applicationInterface.sendPlayers.connect(CreateScripts.recievePlayers);
            CreateScripts.setupSelectors();
            applicationInterface.requestPlayers();
        }
        Component.onDestruction: {
            applicationInterface.tournamentCreatedSuccess.disconnect(createBody.tournamentAssembledAndStored);
            applicationInterface.sendPlayers.disconnect(CreateScripts.recievePlayers);
        }
    }
}
