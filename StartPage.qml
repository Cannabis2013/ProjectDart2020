import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {

    id: body

    signal startGameRequest
    signal loginPageRequest
    signal logOutRequest

    property color labelColor: "transparent"
    property color backgroundContentColor: "transparent"

    onLabelColorChanged: label.color = labelColor
    onBackgroundContentColorChanged: content.color = backgroundContentColor

    GridLayout
    {
        columnSpacing: 0
        rowSpacing: 0
        anchors.fill: parent
        rows: 2
        columns: 1

        PageLabelItem {

            id: label

            height: 64
            width: 384

            Layout.fillWidth: true

            Layout.row: 0

            Layout.maximumHeight: 64
        }

        StartPageContent{

            id: content

            Layout.row: 1

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
