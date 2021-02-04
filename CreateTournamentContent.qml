import QtQuick 2.0
import QtQuick.Layouts 1.3

import "createTournamentScripts.js" as CreateScripts

Content {
    id: createBody
    color: "transparent"

    signal requestPlayers
    signal sendFTPDetails(string title,
                          var data,
                          var playerIndexes)
    signal sendCricketDetails
    signal requestGameModes

    minimumHeight: 538

    QtObject{
        id: sendPlayerState
        property bool playerSent: false
        readonly property int updateCount: 2
    }

    /*
      Event/signal handling
      */
    onReplyFromBackendRecieved: {
        // Backend has processed transmitted details and created the tournament
        if(response === 0x32)
        {
            requestQuit();
        }
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
            createBody.sendFTPDetails.connect(applicationInterface.handleFTPDetails); // Tournament request
            createBody.requestPlayers.connect(applicationInterface.requestPlayerDetails); // Request initial/continous players
            applicationInterface.sendPlayerDetail.connect(CreateScripts.addPlayer); // Recieve initial players
            CreateScripts.setupSelectors();
            requestUpdate();
        }
        Component.onDestruction: {
            createBody.sendFTPDetails.disconnect(applicationInterface.handleFTPDetails);
            createBody.requestPlayers.disconnect(applicationInterface.requestPlayerDetails);
            applicationInterface.sendPlayerDetail.disconnect(CreateScripts.addPlayer);
        }
    }
}
