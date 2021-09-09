import QtQuick 2.12
import QtQuick.Layouts 1.3

Content
{
    id: body
    signal sendPlayerDetails(string json)
    function handleError(msg)
    {
        buttonOneEnabled = buttonTwoEnabled = true;
    }
    
    function evaluateInputs(){
        var playerName = userNameEdit.currentValue;
        
        if(playerName !== "")
            endStateButtons.buttonTwoEnabled = true;
        else
            endStateButtons.buttonTwoEnabled = false;
    }
    
    GridLayout{
        anchors.fill: parent
        
        flow: GridLayout.TopToBottom
        DefaultTextInputBox{
            id: userNameEdit
            Layout.fillWidth: true
            labelText: "Username*"
            onCurrentValueChanged: body.evaluateInputs()
        }
        DefaultTextInputBox{
            id: mailEdit
            Layout.fillWidth: true
            labelText: "Mail adress"
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
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            buttonOneTitle: "Cancel"
            buttonTwoTitle: "Save"
            buttonWidth: 100
            buttonBackgroundColor: ThemeContext.plaButtonBackgroundColor
            buttonsHoveredColor: ThemeContext.plaButtonHoveredBackgroundColor
            buttonTwoEnabled: false
            onButtonOneClicked: requestQuit();
            onButtonTwoClicked: {

                var playerName = userNameEdit.currentValue;
                if(playerName === "")
                    return;
                var mail = mailEdit.currentValue;
                if(mail === "")
                    mail = "defaultsucker@gmail.com";
                var obj = {
                    playerName : playerName,
                    playerMail : mail
                };
                var json = JSON.stringify(obj);
                buttonOneEnabled = false;
                buttonTwoEnabled = false;
                applicationInterface.requestCreatePlayer(json);
            }
        }
    }

    Component.onCompleted: {
        applicationInterface.playerAddedSucces.connect(body.requestQuit);
        applicationInterface.playerAddedError.connect(body.handleError);
    }
    Component.onDestruction: {
        applicationInterface.playerAddedSucces.disconnect(body.requestQuit);
        applicationInterface.playerAddedError.disconnect(body.handleError);
    }
}
