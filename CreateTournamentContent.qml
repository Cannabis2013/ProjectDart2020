import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

Content {
    id: body
    color: "transparent"

    signal requestPlayers
    signal sendTournament(string title,
                          int numberOfThrows,
                          string gameMode,
                          int keyCode,
                          int keyPoint,
                          var playerIndexes)
    signal requestGameModes

    minimumHeight: 538

    QtObject{
        id: sendPlayerState
        property bool playerSent: false
        readonly property int updateCount: 2
    }

    QtObject{
        id: stringModels
        property var gameModes: ["FirstToPost"]
        property var keyIdentifiers: ["Single","Double", "Tripple"]
        property var firstToPostPointValues: ["301","501","701","901"]
    }

    function stateChanged()
    {
        var selectedIndexes = playersListView.currentIndexes();
        var selectedIndexesLength = selectedIndexes.length;
        var tournamentTitle = titleEdit.currentValue;
        var tournamentTitleLength = tournamentTitle.length;
        var status = selectedIndexesLength > 0 && tournamentTitleLength > 0;
        buttonsComponent.buttonTwoEnabled = status;
    }

    function addPlayer(playerName,email)
    {
        playersListView.addItemModel({"type" : "player","username" : playerName, "mail" : email})
    }

    function gameModeToHex(text)
    {
        var gameModes = stringModels.gameModes;
        if(text === gameModes[0])
            return 0x1;
    }
    function convertKeyModifierToHex(key){
        var keyIdentifiers = stringModels.keyIdentifiers;
        if(key === keyIdentifiers[0])
            return 0x2A;
        else if(key === keyIdentifiers[1])
            return 0x2B;
        else if(key === keyIdentifiers[2])
            return 0x2C;
        else
            return -1;
    }
    function createStringModel()
    {
        var text = gameModeSelector.currentValue;
        var gameMode = gameModeToHex(text);
        if(gameMode === 0x1)
            return stringModels.firstToPostPointValues;

        return [];
    }

    /*
      Event/signal handling
      */
    onReplyFromBackendRecieved: {
        // Backend has processed transmitted details and created the tournament
        if(response === 0x32)
        {
            backButtonPressed();
        }
    }
    onRequestUpdate: {
        requestPlayers();
    }

    GridLayout{
        flow: GridLayout.TopToBottom
        anchors.fill: parent
        rowSpacing: 3
        DefaultTextInputBox {
            id: titleEdit
            Layout.fillWidth: true
            onValueChanged: body.stateChanged()
        }
        DefaultSpinBox {
            id: throwSpinBox
            Layout.fillWidth: true
        }

        DefaultComboBox {
            id: keyPointEdit
            Layout.fillWidth: true
            labelText: "Keypoint:"
            model: createStringModel()
        }

        DefaultComboBox{
            id: gameModeSelector
            labelText: "Game modes"
            Layout.fillWidth: true
            model: stringModels.gameModes
            onValueChanged: keyPointEdit.model = createStringModel()
            Component.onCompleted: keyPointEdit.model = createStringModel()
        }
        DefaultComboBox {
            id: winConditionSelector
            Layout.fillWidth: true
            labelText: "Finish with:"
            model: stringModels.keyIdentifiers
        }

        Rectangle{
            height: 10
        }

        DefaultPlayerListView {
            id: playersListView
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            onItemSelected: body.stateChanged()
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
            onButtonOneClicked: backButtonPressed()
            onButtonTwoClicked: {
                var indexes = playersListView.currentIndexes();
                if(indexes.length <= 0)
                    return;
                buttonTwoEnabled = false;
                var title = titleEdit.currentValue;
                var gameMode = gameModeSelector.currentValue;
                var gameCode = gameModeToHex(gameMode);
                var keyPoint = keyPointEdit.currentValue;
                var winConditionKeyIdentifier = winConditionSelector.currentValue;
                var winConditionKeyCode = convertKeyModifierToHex(winConditionKeyIdentifier);
                var numberOfThrows = throwSpinBox.currentValue;
                sendTournament(title,
                               numberOfThrows,
                               gameCode,
                               winConditionKeyCode,
                               keyPoint,
                               indexes);
            }
        }

        Component.onCompleted: {
            body.sendTournament.connect(applicationInterface.handleCreateTournament); // Tournament request
            body.requestPlayers.connect(applicationInterface.requestPlayerDetails); // Request initial/continous players
            applicationInterface.sendPlayerDetail.connect(body.addPlayer); // Recieve initial players
            requestUpdate();
        }
        Component.onDestruction: {
            body.sendTournament.disconnect(applicationInterface.handleCreateTournament);
            body.requestPlayers.disconnect(applicationInterface.requestPlayerDetails);
            applicationInterface.sendPlayerDetail.disconnect(body.addPlayer);
        }
    }
}
