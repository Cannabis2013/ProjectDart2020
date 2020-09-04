import QtQuick 2.12
import QtQuick.Layouts 1.3

Content
{
    id: body
    
    signal sendPlayerDetails(string playerName,string mail)

    function playerCreatedSucess(status)
    {
        if(status)
            backButtonPressed();
        else
        {
            buttonOneEnabled = true;
            buttonTwoEnabled = true;
        }
    }
    
    function evaluateInputs(){
        var playerName = userNameEdit.currentText;
        
        if(playerName !== "")
            endStateButtons.buttonTwoEnabled = true;
        else
            endStateButtons.buttonTwoEnabled = false;
    }
    
    GridLayout{
        anchors.fill: parent
        
        flow: GridLayout.TopToBottom
        
        LineEditComponent{
            id: userNameEdit
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Username*"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
            onTextChanged: body.evaluateInputs()
            
        }
        
        LineEditComponent{
            id: mailEdit
            Layout.fillWidth: true
            height: 32
            fontSize: 12
            labelText: "Mail adress"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }
        
        MyRectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        
        DecoratedItem{
            Layout.preferredWidth: 192
            Layout.preferredHeight: 256
            Layout.alignment: Qt.AlignVCenter |Qt.AlignHCenter
            source: "qrc:/pictures/Ressources/users.png"
        }
        
        MyRectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            bottomBorderWidth: 1
        }
        
        ButtonsComponent{
            id: endStateButtons
            clip: true
            color: "transparent"
            height: 30
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignBottom |Qt.AlignHCenter
            buttonOneTitle: "Cancel"
            buttonTwoTitle: "Save"
            buttonWidth: 100
            buttonTwoEnabled: false
            onButtonOneClicked: backButtonPressed();
            onButtonTwoClicked: {
                var playerName = userNameEdit.currentText;
                var mail = mailEdit.currentText;
                buttonOneEnabled = false;
                buttonTwoEnabled = false;
                body.sendPlayerDetails(playerName,mail);
            }
        }
    }

    Component.onCompleted: {
        body.sendPlayerDetails.connect(applicationInterface.handleCreatePlayer);
        applicationInterface.playerCreatedSuccess.connect(body.playerCreatedSucess);
    }
    Component.onDestruction: {
        body.sendPlayerDetails.disconnect(applicationInterface.handleCreatePlayer);
        applicationInterface.playerCreatedSuccess.disconnect(body.body.playerCreatedSucess);
    }
}
