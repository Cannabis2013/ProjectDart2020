import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

Content {
    id: body
    color: "transparent"

    signal requestPlayers
    signal sendTournament(string title, int numberOfThrows, int maxPlayers, int gameMode,int keyPoint)
    signal sendPlayerIndexes(var indexes, string tournament)
    signal requestGameModes

    QtObject{
        id: sendPlayerState
        property bool playerSent: false
    }

    function handleReply(status,message){
        if(status === 0x7)
        {
            if(!sendPlayerState.playerSent)
            {
                var indexes = playersListView.currentlySelectedIndexes;
                sendPlayerState.playerSent = true;
                sendPlayerIndexes(indexes,message);
            }
            else{
                backButtonPressed();
            }
        }
        else if(status === 0x8)
        {
            if(sendPlayerState.playerSent)
            {
                var secondIndexes = playersListView.currentlySelectedIndexes;
                sendPlayerIndexes(secondIndexes);
            }
        }
    }

    function reConnectInterface()
    {

        localDart.sendStatus.connect(handleReply); // Handle reply
        playersListView.clear();
        requestPlayers();

    }

    GridLayout{
        flow: GridLayout.TopToBottom
        anchors.fill: parent
        rowSpacing: 3
        LineEditComponent {
            id: titleEdit
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Title"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }

        LineEditComponent {
            id: legsEdit
            isNumeric: true
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Number of throws"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }

        LineEditComponent {
            id: maxPlayerEdit
            isNumeric: true
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Max allowered players"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }

        LineEditComponent {
            id: keyPointEdit
            isNumeric: true
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Keypoint"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }

        ComboBoxView{
            id: gameModeSelector
            height: 32
            Layout.fillWidth: true
            labelText: "Game modes"
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelFontSize: 8
            labelLeftMargin: 10
        }

        Rectangle{
            height: 10
        }

        ListComponent {
            id: playersListView
            Layout.alignment: Qt.AlignHCenter
            width: 320
            height: 256
            componentTitle: "Assign players"
            itemTextColor: "black"
            itemSelectedBackgroundColor: "silver"
            itemHoveredColor: "darkgray"
            color: "white"
            radius: 15
            itemFontSize: 8
            itemWidth: 256
            allowCheckState: true
            allowMultipleSelections: true
        }

        MyRectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.minimumHeight: createPlayerButton.height*2
        }

        ButtonsComponent {
            height: 30
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignBottom |Qt.AlignHCenter
            buttonOneTitle: "Back"
            buttonTwoTitle: "Save tournament"
            onButtonOneClicked: {
                backButtonPressed();
            }
            onButtonTwoClicked: {
                buttonTwoEnabled = false;
                sendTournament(titleEdit.currentText,
                               legsEdit.currentText,
                               maxPlayerEdit.currentText,
                               gameModeSelector.currentText,
                               keyPointEdit.currentText);
            }
        }
        CRUDButton{
            id: createPlayerButton
            text: "Create"

            anchors.top: playersListView.bottom
            anchors.right: playersListView.right
            onClicked: {
                var component = ComponentFactory.createPopUp(applicationWindow,"createPlayerPopUp",0,0,applicationWindow.width,applicationWindow.height);
                component.destroyed.connect(reConnectInterface);
                localDart.sendStatus.disconnect(handleReply);
            }

        }
        Component.onCompleted: {
            localDart.sendStatus.connect(handleReply); // Handle reply
            body.requestGameModes.connect(localDart.gameModes); // Request gamemodes
            body.sendTournament.connect(localDart.createTournament); // Tournament request
            localDart.sendGameModes.connect(gameModeSelector.setModel) // Recieve gamemodes
            requestGameModes();
            body.sendPlayerIndexes.connect(localDart.assignPlayers); // Send player indexes
            body.requestPlayers.connect(localDart.requestPlayerDetails); // Request initial/continous players
            localDart.sendPlayerDetails.connect(playersListView.addPlayerItem); // Recieve initial players
            requestPlayers(); // Make the initial request
        }
        Component.onDestruction: {
            body.sendTournament.disconnect(localDart.createTournament);
            localDart.sendStatus.disconnect(handleReply);
            body.sendPlayerIndexes.disconnect(localDart.assignPlayers);
            body.requestPlayers.disconnect(localDart.requestPlayerDetails);
            localDart.sendPlayerDetails.disconnect(playersListView.addPlayerItem);
        }
    }
}
