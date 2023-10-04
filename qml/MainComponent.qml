import QtQuick 2.12

import "./pages/tournamentPage"
import "./pages/startPage"
import "./components/pages"

Item {
        id: body

        signal backPushed

        Component {
                id: startPageComponent
                StartPage {
                        onSetupGameClicked: pageLoader.sourceComponent = setupTournamentPage
                        onManageContentClicked: pageLoader.sourceComponent = managePageComponent
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

        Loader {
                id: pageLoader
                anchors.fill: parent
                sourceComponent: startPageComponent
        }
}
