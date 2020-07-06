import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    Layout.fillHeight: true
    Layout.fillWidth: true

    Layout.maximumWidth: defaultPageContentWidth

    Layout.alignment: Qt.AlignHCenter

    color: "transparent"

    clip: true

    GridLayout{
        id: componentLayout

        anchors.fill: parent

        columns: 1

        flow: GridLayout.TopToBottom

        TurnNavigationComponent{
            id: turnNavigator
            Layout.fillWidth: true
            height: 64

            Layout.alignment: Qt.AlignHCenter
        }

        CustomTable{
            id: scoreTable

            color: "transparent"

            verticalHeaderFillMode: 0x1
            Layout.fillWidth: true

            height: 125
        }

        Rectangle{
            Layout.minimumHeight: 25
            Layout.maximumHeight: 25
        }

        KeyPadComponent{
            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.minimumHeight: 128
            Layout.maximumHeight: 384

            Layout.alignment: Qt.AlignTop
        }
        Rectangle{
            Layout.fillHeight: true
        }
    }
    Component.onCompleted: {
        var currentTournamentID = localDart.currentTournamentID();
        if(currentTournamentID === "")
        {
            print("No currently active tournament");
            return;
        }

        var tournamentLegsCount = localDart.tournamentLegsCount(currentTournamentID);
        var playersCount = localDart.tournamentPlayersCount(currentTournamentID);
        // Append headers
        for(var i = 0;i < playersCount;i++){
            var playerID = localDart.assignedPlayerIDfromIndex(currentTournamentID,i);
            var fullName = localDart.playerFirstName(playerID) + " " + localDart.playerLastName(playerID);
            scoreTable.appendHeader(fullName,0x2);
        }
        var headerItemsCount = scoreTable.getHeaderItemCount(0x2);
        for(var j = 0;j < headerItemsCount;j++){
            var headerItem = scoreTable.getHeaderItem(j,0x2);
            var player = localDart.playerIDFromFullName(headerItem);
            var roundIndex = 1;
            var legIndex = 0;
            while(1)
            {
                var point = localDart.pointValue(currentTournamentID,player,roundIndex,++legIndex);
                if(point < 0)
                    break;
                scoreTable.appendData(headerItem,point,0x2);
                if(legIndex % tournamentLegsCount == 0)
                {
                    roundIndex++;
                    legIndex = 0;
                }
            }
        }
    }
}
