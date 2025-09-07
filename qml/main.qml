import QtQuick 6.0
import QtQuick.Controls 2.12

import "pages"

ApplicationWindow {
  id: applicationWindow

  visible: true

  minimumHeight: 640
  minimumWidth: 400

  title: qsTr("Dart2020")

  signal backPushed

  Component {
    id: startPageComponent
    Start {
      onRequestSetupPage: pageLoader.sourceComponent = setupTournament
      onRequestTournamentPage: pageLoader.sourceComponent = tournamentPage
      onRequestAboutPage: pageLoader.sourceComponent = aboutPage
    }
  }

  Component {
    id: tournamentPage
    Tournament {
      onMenuRequest: pageLoader.sourceComponent = startPageComponent
    }
  }

  Component {
    id: aboutPage
    About {
      onBackClicked: pageLoader.sourceComponent = startPageComponent
    }
  }

  Component {
    id: setupTournament
    Setup{
      onRequestTournamentPage: pageLoader.sourceComponent = tournamentPage
      onBackClicked: pageLoader.sourceComponent = startPageComponent
    }
  }

  Loader {
    id: pageLoader
    anchors.fill: parent
    sourceComponent: startPageComponent
    asynchronous: true
  }
}
