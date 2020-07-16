import QtQuick 2.0
import QtQuick.Layouts 1.3



import "componentFactory.js" as ComponentFactory
import "setupPageScripts.js" as SetupPageScripts

Content {
    id: body
    color: "transparent"

    signal requestPlayers
    signal sendTournament(string title, int numberOfThrows, int maxPlayers, int gameMode,int keyPoint)


    function handleReply(status){
        if(status === 0x7)
        {

        }
    }

    GridLayout{
        flow: GridLayout.TopToBottom
        anchors.fill: parent
        rowSpacing: 3
        LineEditComponent {
            id: titleEdit
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Title"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }

        LineEditComponent {
            id: legsEdit
            isNumeric: true
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Number of throws"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }

        LineEditComponent {
            id: maxPlayerEdit
            isNumeric: true
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Max allowered players"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }

        LineEditComponent {
            id: keyPointEdit
            isNumeric: true
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Keypoint"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }

        ComboBoxView{
            id: gameModeSelector
            height: 32
            Layout.fillWidth: true
            labelText: "Game modes"
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelFontSize: 8
            labelLeftMargin: 10
            stringModel: localDart.gameModes()
        }

        Rectangle{
            height: 10
        }

        ListComponent {
            id: playersListView
            Layout.alignment: Qt.AlignHCenter
            width: 320
            height: 256
            componentTitle: "Assign players"
            itemTextColor: "black"
            itemSelectedBackgroundColor: "silver"
            itemHoveredColor: "darkgray"
            color: "white"
            radius: 15
            itemFontSize: 8
            itemWidth: 256
            allowCheckState: true
            allowMultipleSelections: true
        }

        MyRectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.minimumHeight: createPlayerButton.height*2
        }

        ButtonsComponent {
            height: 30
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignBottom |Qt.AlignHCenter
            buttonOneTitle: "Back"
            buttonTwoTitle: "Save tournament"
            onButtonOneClicked: {
                backButtonPressed();
            }
            onButtonTwoClicked: {
                buttonTwoEnabled = false;
                sendTournament(titleEdit.currentText,
                               legsEdit.currentText,
                               maxPlayerEdit.currentText,
                               gameModeSelector.currentText,
                               keyPointEdit.currentText);
            }
        }
        CRUDButton{
            id: createPlayerButton
            text: "Create"

            anchors.top: playersListView.bottom
            anchors.right: playersListView.right
            onClicked: {
                var component = ComponentFactory.createPopUp(applicationWindow,"createPlayerPopUp",0,0,applicationWindow.width,applicationWindow.height);
                component.backButtonPressed.connect(updateInterface);
            }
        }
        Component.onCompleted: {
            body.sendTournament.connect(localDart.createTournament);
            localDart.sendStatus.connect(handleReply);
        }
        Component.onDestruction: {

        }
    }
}
