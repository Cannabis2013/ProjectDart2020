import QtQuick 2.0
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

Rectangle {
    color: "transparent"

    Layout.fillHeight: true
    Layout.fillWidth: true

    Layout.maximumWidth: defaultPageContentWidth

    Layout.alignment: Qt.AlignHCenter

    function updateInterface(){
        var playerCount = localDart.playersCount();

        for(var i = 0;i < playerCount;i++)
        {
            var playerID = localDart.playerIDFromIndex(i);

            var playerFirstName = localDart.playerFirstName(playerID);
            var playerLastName = localDart.playerLastName(playerID);
            var playerEMail = localDart.playerEmail(playerID);

            playersListView.addPlayerItem(playerFirstName,playerLastName,playerEMail, playerID);
        }
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

            labelText: "Number of legs"
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

            stringModel: localDart.gameModes()
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

            allowMultipleSelections: true
        }

        MyRectangle{
            bottomBorderWidth: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ButtonsComponent {
            clip: true
            color: "transparent"
            height: 30
            width: 200
            Layout.alignment: Qt.AlignBottom |Qt.AlignHCenter

            buttonOneTitle: "Save"
            buttonTwoTitle: "Save and play"

            onSaveClicked: {
                // Save tournament and go back to previous page

                var tournamentTitle = titleEdit.currentText;
                var legs = legsEdit.currentText;
                var maxPlayers = maxPlayerEdit.currentText;
                var keyPoint = keyPointEdit.currentText;
                var gameModeString = gameModeSelector.currentText;
                var gameMode = localDart.gameModeFromString(gameModeString);

                var createdTournament = localDart.createTournament(tournamentTitle,legs,maxPlayers,gameMode,keyPoint);

                var selectedIndexes = playersListView.currentlySelectedIndexes;

                for(var i = 0;i < selectedIndexes.length;i++)
                {
                    var selectedIndex = selectedIndexes[i];
                    var playerID = localDart.playerIDFromIndex(selectedIndex);
                    if(playerID === "")
                        throw "Something went very wrong. This is probably due to inconsistence.";
                    localDart.assignPlayer(playerID,createdTournament);
                }
                backButtonPressed();
            }
        }

        Component.onCompleted: {
            updateInterface();
        }
    }
}
