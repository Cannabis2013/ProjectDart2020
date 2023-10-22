import QtQuick 2.12

import "./pages/tournament"
import "./pages/about"
import "./pages/start"
import "./pages/setup/full"
import "./pages/setup/quick"

Item {
        id: body

        signal backPushed

        Component {
                id: startPageComponent
                StartPage {
                        onSetupGameClicked: pageLoader.sourceComponent = setupTournamentPage
                        onQuickGameClicked: pageLoader.sourceComponent = quickSetup
                        onRequestTournamentPage: pageLoader.sourceComponent = tournamentPage
                        onRequestAboutPage: pageLoader.sourceComponent = aboutPage
                }
        }

        Component {
                id: tournamentPage
                TournamentPage {
                        onBackClicked: pageLoader.sourceComponent = startPageComponent
                }
        }

        Component {
                id: setupTournamentPage
                SetupTournamentPage {
                        onBackClicked: pageLoader.sourceComponent = startPageComponent
                        onRequestTournamentPage: pageLoader.sourceComponent = tournamentPage
                }
        }

        Component {
                id: aboutPage
                AboutPage {
                        onBackClicked: pageLoader.sourceComponent = startPageComponent
                }
        }

        Component {
                id: quickSetup
                QuickSetup {
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
