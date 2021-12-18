import QtQuick 2.0
import QtQuick.Layouts 1.3


Rectangle
{   
    id: body

    signal buttonClicked

    color: "transparent"

    GridLayout
    {
        anchors.fill: body
        rows: 2
        columns: 1

        rowSpacing: 2

        PushButton
        {
            Layout.row: 0
            
            width: 128
            height: 50
            text: "Log in"

            enabled: false

            onClicked: buttonClicked()
        }

        Rectangle
        {
            Layout.fillHeight: true
        }
    }
}
