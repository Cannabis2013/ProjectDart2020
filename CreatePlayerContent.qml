import QtQuick 2.0
import QtQuick.Layouts 1.3


Item {
    id: createPlayerBody

    Layout.fillWidth: true
    Layout.fillHeight: true

    Layout.maximumWidth: defaultPageContentWidth

    GridLayout{
        anchors.fill: parent

        flow: GridLayout.TopToBottom

        LineEditComponent{
            Layout.fillWidth: true

            height: 32
            fontSize: 12

            labelText: "Firstname"
            labelFontSize: 8
            labelFontColor: "darkblue"
            labelBackgroundColor: "lightblue"
            labelLeftMargin: 10
        }

        LineEditComponent{
            Layout.fillWidth: true

            height: 32
            fontSize: 12

            labelText: "Lastname"
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

        Rectangle{
            Layout.fillHeight: true
        }
    }
}
