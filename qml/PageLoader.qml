import QtQuick 2.12

import "./pages/tournament"
import "./pages/about"
import "./pages/start"
import "./pages/setup"

Item {
        id: body

        signal backPushed

        Component {
                id: startPageComponent
                StartPage {
                        onSetupGameClicked: pageLoader.sourceComponent = setupTournament
                        onRequestTournamentPage: pageLoader.sourceComponent = tournamentPage
                        onRequestAboutPage: pageLoader.sourceComponent = aboutPage
                }
        }

        Component {
                id: tournamentPage
                TournamentPage {
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
                SetupPage {
                        onRequestTournamentPage: pageLoader.sourceComponent = tournamentPage
                        onBackClicked: pageLoader.sourceComponent = startPageComponent
                }
        }

        Loader {
                id: pageLoader
                anchors.fill: parent
                sourceComponent: startPageComponent
        }
}
