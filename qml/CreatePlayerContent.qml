import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "createPlayerScripts.js" as CPScripts

Page {
        id: body

        signal backButtonClicked

        header: Button {
                text: qsTr("Back")
                onClicked: backButtonClicked()
        }


        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom
                DefaultTextInputBox {
                        id: userNameEdit
                        Layout.fillWidth: true
                        labelText: "Username*"
                        onCurrentValueChanged: CPScripts.evaluateInputs()
                }
                DefaultTextInputBox {
                        id: mailEdit
                        Layout.fillWidth: true
                        labelText: "Mail adress"
                }
                MyRectangle {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        bottomBorderWidth: 1
                }
                Text {
                        id: errTextBox
                        height: 128
                        Layout.fillWidth: true
                        color: "yellow"
                }
                ButtonsComponent {
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
                        onButtonOneClicked: requestQuit()
                        onButtonTwoClicked: CPScripts.process()
                }
        }
}
