import QtQuick 2.0
import QtQuick.Controls 2.15

Page {
        signal backClicked
        Rectangle {
                id: backdrop
                anchors.fill: parent
                color: "black"
        }

        header: PageHeader {
                onBackButtonClicked: backClicked()
        }

        anchors.fill: parent
}
