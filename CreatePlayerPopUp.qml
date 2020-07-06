import QtQuick 2.0
import QtQuick.Layouts 1.3


Page{
    pageTitle : "Create player"
    pageContent: Content {
        id: createPlayerBody


        GridLayout{
            anchors.fill: parent

            flow: GridLayout.TopToBottom

            LineEditComponent{
                Layout.fillWidth: true

                height: 32
                fontSize: 12

                labelText: "Firstname*"
                labelFontSize: 8
                labelFontColor: "darkblue"
                labelBackgroundColor: "lightblue"
                labelLeftMargin: 10
            }

            LineEditComponent{
                Layout.fillWidth: true

                height: 32
                fontSize: 12

                labelText: "Lastname*"
                labelFontSize: 8
                labelFontColor: "darkblue"
                labelBackgroundColor: "lightblue"
                labelLeftMargin: 10
            }

            LineEditComponent{
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
                Layout.fillWidth: true
                height: 32

                labelFontSize: 8
                labelFontColor: "darkblue"
                labelBackgroundColor: "lightblue"
                labelText: "Race"

                stringModel: ["Privilliged white", "Hispanic","latino", "Nigger","Asian"]
                labelLeftMargin: 10
            }

            ComboBoxView{
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

            ButtonsComponent{
                id: endStateButtons
                clip: true
                color: "transparent"
                height: 30
                width: 200
                Layout.alignment: Qt.AlignBottom |Qt.AlignHCenter

                buttonOneTitle: "Cancel"
                buttonTwoTitle: "Save"

                buttonWidth: 100

                onButtonOneClicked: backButtonPressed();
                onButtonTwoClicked: {
                    backButtonPressed()
                }
            }
        }
    }
}
