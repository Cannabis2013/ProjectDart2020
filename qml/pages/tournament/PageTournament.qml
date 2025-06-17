import QtQuick 2.1
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "turnControls"
import "inputs"
import "messages"
import "scoreDisplay"
import "pageTournament.js" as Scripts
import "dialogs/dialogs.js" as Dialogs

Page {
  id: tournamentPage
  signal menuRequest

  focus: true
  Keys.onPressed: event => Scripts.handleCloseEvent(event)

  GridLayout {
    anchors.fill: parent
    rowSpacing: 0
    columnSpacing: 0
    flow: GridLayout.TopToBottom
    rows: 4

    ScoreDisplay {
      id: playerInfo
      Layout.preferredHeight: 146
      Layout.fillWidth: true
    }

    MessagesDisplay {
      id: messageSection
      Layout.topMargin: 6
      Layout.fillWidth: true
      Layout.minimumHeight: 48
      Layout.alignment: Qt.AlignTop
    }
    TurnControls {
      id: turnControls
      Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
      Layout.preferredHeight: 36
      Layout.fillWidth: true
      Layout.leftMargin: 6
      Layout.rightMargin: 6
      onUndoClicked: Scripts.undo()
      onRedoClicked: Scripts.redo()
      onRestartClicked: Dialogs.openConfirmDialog("Sure you want to restart?",
                                                  Scripts.restartGame)
    }

    Item {
      visible: !Scripts.isPortrait()
      Layout.fillHeight: true
    }

    CompInputs {
      id: inputSection
      Layout.fillWidth: Scripts.isPortrait() || tournamentPage.width < 1024
      Layout.preferredWidth: tournamentPage.width < 1024 ? 0 : 512
      Layout.fillHeight: true
      Layout.minimumWidth: 12
      Layout.rowSpan: Scripts.isPortrait() ? 1 : 4
      onReportInputs: inputs => Scripts.addScore(inputs)
      onReportPreview: inputs => playerInfo.updateScorePreview(inputs)
    }
  }

  Component.onCompleted: Scripts.initializeUI()
  Component.onDestruction: dartsInitializer.saveState()
}
