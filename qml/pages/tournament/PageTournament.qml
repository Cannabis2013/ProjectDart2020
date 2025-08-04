import QtQuick 2.1
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "turnControls"
import "keyPad"
import "inputDisplay"
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
    rows: Scripts.isPortrait() ? 6 : 4

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
      Layout.fillHeight: !Scripts.isPortrait()
    }

    InputDisplay {
      id: inputDisplay
      Layout.fillWidth: Scripts.isPortrait() || tournamentPage.width < 1024
      Layout.preferredWidth: tournamentPage.width < 1024 ? 0 : 512
      Layout.preferredHeight: 72
      Layout.alignment: Qt.AlignBottom
    }

    KeyPad {
      id: inputSection
      Layout.fillWidth: Scripts.isPortrait() || tournamentPage.width < 1024
      Layout.preferredWidth: tournamentPage.width < 1024 ? 0 : 512
      Layout.fillHeight: true
      Layout.minimumWidth: 12
      Layout.rowSpan: Scripts.isPortrait() ? 1 : 3
      onEnter: (modId, point) => inputDisplay.add(modId, point)
      onReport: Scripts.reportInputs()
    }
  }

  Component.onCompleted: Scripts.updateTurnValues()
  Component.onDestruction: dartsInitializer.saveState()
}
