import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "../../buttons"
import "../../userInputs"
import "../../viewDelegates"
import "../../players/listView"
import "../../geometry"
import "createTournamentScripts.js" as CreateScripts

Page {
        id: createBody
        signal backButtonClicked

        header: Button {
                text: qsTr("Back")
                onClicked: backButtonClicked()
        }

        signal requestPlayers
        signal sendDartsDetails(string json)
        signal sendCricketDetails
        signal requestGameModes
        function selectorComponent() {
                return selectorLoader.item
        }
        GridLayout {
                flow: GridLayout.TopToBottom
                anchors.fill: parent
                rowSpacing: 3
                DefaultTextInputBox {
                        id: titleEdit
                        Layout.fillWidth: true
                        onValueChanged: CreateScripts.stateChanged()
                }
                DefaultComboBox {
                        id: gameModeSelector
                        labelText: "Game modes"
                        Layout.fillWidth: true
                        model: ["FirstToPost"]
                        onValueChanged: CreateScripts.setupSelectors()
                }
                Loader {
                        id: selectorLoader
                        Layout.fillWidth: true
                }
                Rectangle {
                        height: 10
                }
                PlayerListView {
                        id: playersListView
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        onItemSelected: CreateScripts.stateChanged()
                }
                MyRectangle {
                        Layout.fillWidth: true
                        height: 32
                }
                ButtonsComponent {
                        id: buttonsComponent
                        height: 30
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
                        buttonOneTitle: "Back"
                        buttonTwoTitle: "Save tournament"
                        buttonTwoEnabled: false
                        buttonBackgroundColor: ThemeContext.touButtonBackgroundColor
                        onButtonOneClicked: requestQuit()
                        onButtonTwoClicked: CreateScripts.acceptAndAdd()
                }
                Component.onCompleted: CreateScripts.init()
        }
}
