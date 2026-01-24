pragma ComponentBehavior: Bound
import QtQuick 6.0
import QtQuick.Controls 2.12

import "pages"

ApplicationWindow {
  id: applicationWindow

  visible: true

  width: Screen.width
  height: Screen.height
  minimumWidth: 400
  minimumHeight: 800

  title: qsTr("Dart2020")

  signal backPushed

  Component {
    id: startPageComponent

    Start {
      onRequestCalculator: pageLoader.sourceComponent = scoreCalculator
      onRequestSetupPage: pageLoader.sourceComponent = setupTournament
      onRequestTournamentPage: pageLoader.sourceComponent = tournamentPage
      onRequestAboutPage: pageLoader.sourceComponent = aboutPage
    }
  }

  Component {
    id: tournamentPage

    Game {
      onMenuRequest: pageLoader.sourceComponent = startPageComponent
    }
  }

  Component {
    id: scoreCalculator

    Calculator {
      onBackClicked: pageLoader.sourceComponent = startPageComponent
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

    Setup {
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
