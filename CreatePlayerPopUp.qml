import QtQuick 2.12
import QtQuick.Layouts 1.3


Page{
    id: pageBody
    pageTitle : "Create player"

    pageContent: Content
    {
        id: createPlayerBody

        signal sendPlayerDetails(string firstName, string lastName, string mail)

        signal aboutToClose
        onAboutToClose: pageBody.aboutToClose()

        onReplyFromBackendRecieved : {
            if(status === 0xE)
            {
                backButtonPressed();
            }
            else
            {
                endStateButtons.buttonOneEnabled = true;
                endStateButtons.buttonTwoEnabled = true;
            }
        }

        function evaluateInputs(){
            var firstName = firstNameEdit.currentText;
            var lastName = lastNameEdit.currentText;

            if(firstName !== "" && lastName !== "")
                endStateButtons.buttonTwoEnabled = true;
            else
                endStateButtons.buttonTwoEnabled = false;
        }

        GridLayout{
            anchors.fill: parent

            flow: GridLayout.TopToBottom

            LineEditComponent{
                id: firstNameEdit
                Layout.fillWidth: true
                height: 32
                fontSize: 12
                labelText: "Firstname*"
                labelFontSize: 8
                labelFontColor: "darkblue"
                labelBackgroundColor: "lightblue"
                labelLeftMargin: 10
                onTextChanged: createPlayerBody.evaluateInputs()

            }

            LineEditComponent{
                id: lastNameEdit
                Layout.fillWidth: true

                height: 32
                fontSize: 12

                labelText: "Lastname*"
                labelFontSize: 8
                labelFontColor: "darkblue"
                labelBackgroundColor: "lightblue"
                labelLeftMargin: 10
                onTextChanged: createPlayerBody.evaluateInputs()
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

            ComboBoxView{
                id: raceSelector
                Layout.fillWidth: true
                height: 32
                labelFontSize: 8
                labelFontColor: "darkblue"
                labelBackgroundColor: "lightblue"
                labelText: "Race"
                stringModel: ["Caucasian", "Non-white", "Nigger","Asian"]
                labelLeftMargin: 10
            }

            ComboBoxView{
                id: sexSelector
                Layout.fillWidth: true
                height: 32
                labelFontSize: 8
                labelFontColor: "darkblue"
                labelBackgroundColor: "lightblue"
                labelText: "Sex"

                stringModel: ["Male", "Female", "Queer", "Trans", "Sex? Hell yeah!!", "Bisexual", "Multisexual"]
                labelLeftMargin: 10
            }

            MyRectangle{
                Layout.fillHeight: true
                bottomBorderWidth: 1
            }

            Image {
                id: hitlerImage
                source: "qrc:/pictures/Ressources/hitler.png"

                Layout.fillWidth: true
                Layout.fillHeight: true

                visible: false
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
                    var firstName = firstNameEdit.currentText;
                    var lastName = lastNameEdit.currentText;
                    var mail = mailEdit.currentText;
                    /*
                    var race = raceSelector.currentText;
                    var sex = sexSelector.currentText;
                    */
                    buttonOneEnabled = false;
                    buttonTwoEnabled = false;
                    createPlayerBody.sendPlayerDetails(firstName,lastName,mail);
                }
            }
        }
    }
    Component.onCompleted: {
        createPlayerBody.sendPlayerDetails.connect(localDart.createPlayer);
    }
    Component.onDestruction: {
        createPlayerBody.sendPlayerDetails.disconnect(localDart.createPlayer);
    }
}
