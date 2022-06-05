import QtQuick 2.0
import QtQuick.Layouts 1.3
import "createTournamentScripts.js" as CreateScripts
Content {
    id: createBody
    color: "transparent"
    preferedPageTitle: "Create tournament"
    signal requestPlayers
    signal sendDartsDetails(string json)
    signal sendCricketDetails
    signal requestGameModes
    function selectorComponent()
    {
        return selectorLoader.item;
    }
    GridLayout{
        flow: GridLayout.TopToBottom
        anchors.fill: parent
        rowSpacing: 3
        DefaultTextInputBox {
            id: titleEdit
            Layout.fillWidth: true
            onValueChanged: CreateScripts.stateChanged()
        }
        DefaultComboBox{
            id: gameModeSelector
            labelText: "Game modes"
            Layout.fillWidth: true
            model: ["FirstToPost"]
            onValueChanged: CreateScripts.setupSelectors()
        }
        Loader{
            id: selectorLoader
            Layout.fillWidth: true
        }
        Rectangle{
            height: 10
        }
        DefaultPlayerListView {
            id: playersListView
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            onItemSelected: CreateScripts.stateChanged()
        }
        MyRectangle{
            Layout.fillWidth: true
            height: 32
        }
        ButtonsComponent {
            id: buttonsComponent
            height: 30
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignBottom |Qt.AlignHCenter
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
