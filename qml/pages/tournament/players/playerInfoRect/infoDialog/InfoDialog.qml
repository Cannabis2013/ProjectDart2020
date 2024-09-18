import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "infoDialog.js" as Scripts

Dialog {
    width: parent.width * 0.95
    height: parent.height * 0.95
    anchors.centerIn: parent

    property string playerName: ""

    FontMetrics {
        id: fontMetrics
        font.family: textName.font.family
        font.pointSize: 32
        readonly property rect fontRect: boundingRect(playerName)
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 48
        Flickable {
            clip: true
            Layout.preferredHeight: 64
            Layout.fillWidth: true
            boundsBehavior: Flickable.StopAtBounds
            contentWidth: fontMetrics.fontRect.width + 6
            contentHeight: 64
            Text {
                id: textName
                text: playerName
                color: "white"
                font.pointSize: 32
                width: fontMetrics.fontRect.width
            }
        }

        ListView {
            id: inputsList
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.alignment: Qt.AlignCenter
            clip: true
            boundsBehavior: ListView.StopAtBounds
            spacing: 6
            model: ListModel {
                id: inputsModel
            }
            delegate: InputDelegate {
                id: inputDelegate
                height: 32
                width: ListView.view.width
            }
            Component.onCompleted: currentIndex = count - 1
        }
    }

    standardButtons: Dialog.Ok

    Component.onCompleted: Scripts.init()
}
