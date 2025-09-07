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
    PageStart {
      onRequestSetupPage: pageLoader.sourceComponent = setupTournament
      onRequestTournamentPage: pageLoader.sourceComponent = tournamentPage
      onRequestAboutPage: pageLoader.sourceComponent = aboutPage
    }
  }

  Component {
    id: tournamentPage
    PageTournament {
      onMenuRequest: pageLoader.sourceComponent = startPageComponent
    }
  }

  Component {
    id: aboutPage
    AboutPage {
      onBackClicked: pageLoader.sourceComponent = startPageComponent
    }
  }

  Component {
    id: setupTournament
    InitializeGamePage {
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
