import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

Content {
    id: body
    color: "transparent"

    signal requestPlayers
    signal sendTournament(string title, int numberOfThrows, string gameMode,int keyPoint,var playerIndexes)
    signal requestGameModes

    minimumHeight: 538

    QtObject{
        id: sendPlayerState
        property bool playerSent: false
        readonly property int updateCount: 2
    }

    onReplyFromBackendRecieved: {

        if(response === 0xE) // Backend responds update successfull
        {
            backButtonPressed();
        }
    }

    onRequestUpdate: {
        requestGameModes();
        requestPlayers();
    }

    function addPlayer(userName,email)
    {
        playersListView.addItemModel({"type" : "player","username" : userName, "mail" : email})
    }

    function reConnectInterface()
    {
        body.visible = true;
        applicationInterface.sendStatus.connect(replyFromBackendRecieved); // Handle reply
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
            itemBackgroundColor: "lightblue"
            itemTextColor: "black"
            itemHoveredColor: "lightblue"
            color: "white"
            radius: 15
            itemTitleFontSize: 16
            itemWidth: playersListView.width*0.95
            itemHeight: 50
            allowCheckState: true
            allowMultipleSelections: true
            instantSelectEnabled: true
            itemDecorator: "qrc:/pictures/Ressources/darttournamentmod.png"
        }

        MyRectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.minimumHeight: createPlayerButton.height*2
        }
        /*
          Save button clicked
          */
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
                var indexes = playersListView.currentIndexes();
                if(indexes.length <= 0)
                    return;
                buttonTwoEnabled = false;
                var gameMode = gameModeSelector.currentText;
                sendTournament(titleEdit.currentText,
                               legsEdit.currentText,
                               gameMode,
                               keyPointEdit.currentText,
                               indexes);
            }
        }
        CRUDButton{
            id: createPlayerButton
            text: "Create"

            anchors.top: playersListView.bottom
            anchors.right: playersListView.right
            onClicked: {
                body.visible = false;
                var createdComponent = ComponentFactory.createPopUp(applicationWindow,"createPlayerPopUp",0,0,applicationWindow.width,applicationWindow.height);
                createdComponent.backButtonPressed.connect(body.reConnectInterface);
                applicationInterface.sendStatus.disconnect(replyFromBackendRecieved);
            }
        }

        Component.onCompleted: {
            body.requestGameModes.connect(applicationInterface.handleSendGameModesRequest); // Request gamemodes
            applicationInterface.sendGameModes.connect(gameModeSelector.setModel) // Recieve gamemodes
            body.sendTournament.connect(applicationInterface.createTournament); // Tournament request
            body.requestPlayers.connect(applicationInterface.requestPlayers); // Request initial/continous players
            applicationInterface.sendPlayerDetail.connect(body.addPlayer); // Recieve initial players

            requestUpdate();
        }
        Component.onDestruction: {
            body.sendTournament.disconnect(applicationInterface.createTournament);
            body.sendPlayerIndexes.disconnect(applicationInterface.assignPlayers);
            body.requestPlayers.disconnect(applicationInterface.requestPlayerDetails);
            applicationInterface.sendPlayerDetails.disconnect(body.addPlayer);
        }
    }
}
