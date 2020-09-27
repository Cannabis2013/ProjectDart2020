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
    }

    onReplyFromBackendRecieved: {
        if(response === 0x32) // Backend has processed transmitted details and created the tournament
        {
            backButtonPressed();
        }
    }

    function evaluateItemSelectedChanged()
    {
        var list = playersListView.currentIndexes();
        var count = list.length;
        buttonsComponent.buttonTwoEnabled = count > 0;

    }

    onRequestUpdate: {
        requestPlayers();
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
        else if(text === gameModes[1])
            return 0x2;
        else if(text === gameModes[2])
            return 0x3;
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
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }
        /*
        LineEditComponent {
            id: legsEdit
            isNumeric: true
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Number of throws"
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }
        */
        SpinBoxCompoent{
            id: throwSpinBox
            Layout.fillWidth: true
            height: 32
            labelBackgroundColor: "lightblue"
            labelText: "Number of throws"
            labelLeftMargin: 10
            labelFontColor: "darkblue"
        }

        LineEditComponent {
            id: keyPointEdit
            isNumeric: true
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Keypoint"

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
            labelLeftMargin: 10
            stringModel: stringModels.gameModes
        }

        ComboBoxView{
            id: winConditionSelector
            height: 32
            Layout.fillWidth: true
            labelText: "Finish with:"
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
            stringModel: stringModels.keyIdentifiers
        }

        Rectangle{
            height: 10
        }

        DefaultPlayerListView {
            id: playersListView
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
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
            onButtonOneClicked: {
                backButtonPressed();
            }
            onButtonTwoClicked: {
                var indexes = playersListView.currentIndexes();
                if(indexes.length <= 0)
                    return;
                buttonTwoEnabled = false;
                var gameMode = gameModeSelector.currentText;
                var gameCode = gameModeToHex(gameMode);
                var winConditionKeyIdentifier = winConditionSelector.currentText;
                var winConditionKeyCode = convertKeyModifierToHex(winConditionKeyIdentifier);
                var numberOfThrows = throwSpinBox.currentValue;
                sendTournament(titleEdit.currentText,
                               numberOfThrows,
                               gameCode,
                               winConditionKeyCode,
                               keyPointEdit.currentText,
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
            applicationInterface.sendPlayerDetail.disconnect(body.addPlayer);
        }
    }
}
