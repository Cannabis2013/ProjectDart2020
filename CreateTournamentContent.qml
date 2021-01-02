import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory
import "createTournamentScripts.js" as CreateScripts

Content {
    id: createBody
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
    QtObject{
        id: defaultStateValues
        readonly property int defaultGameModeIndex: 0
        readonly property int defaultWinConditionIndex: 1
        readonly property int defaultKeyPointIndex: 1
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
            onValueChanged: CreateScripts.stateChanged()
        }
        DefaultSpinBox {
            id: throwSpinBox
            Layout.fillWidth: true
        }

        DefaultComboBox{
            id: gameModeSelector
            labelText: "Game modes"
            Layout.fillWidth: true
            model: stringModels.gameModes
            onValueChanged: CreateScripts.initializeKeyPointComponent()
        }

        DefaultComboBox {
            id: keyPointEdit
            Layout.fillWidth: true
            labelText: "Keypoint:"
        }

        DefaultComboBox {
            id: winConditionSelector
            Layout.fillWidth: true
            labelText: "Finish with:"
            model: stringModels.keyIdentifiers
            Component.onCompleted: winConditionSelector.currentIndex = defaultStateValues.defaultWinConditionIndex
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
            onButtonOneClicked: backButtonPressed()
            onButtonTwoClicked: CreateScripts.acceptAndAdd()
        }

        Component.onCompleted: {
            createBody.sendTournament.connect(applicationInterface.handleCreateTournament); // Tournament request
            createBody.requestPlayers.connect(applicationInterface.requestPlayerDetails); // Request initial/continous players
            applicationInterface.sendPlayerDetail.connect(CreateScripts.addPlayer); // Recieve initial players
            requestUpdate();
        }
        Component.onDestruction: {
            createBody.sendTournament.disconnect(applicationInterface.handleCreateTournament);
            createBody.requestPlayers.disconnect(applicationInterface.requestPlayerDetails);
            applicationInterface.sendPlayerDetail.disconnect(CreateScripts.addPlayer);
        }
    }
}
