import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0


Item{
    id: body

    GridLayout{
        anchors.fill: parent

        columns: 1

        anchors.leftMargin: 20
        anchors.rightMargin: 20

        MyLineEdit {
            Layout.row: 0
            Layout.column: 0

            Layout.fillWidth: true

            height: 32

            Layout.leftMargin: 10
            Layout.rightMargin: 10

            labelText: "Title"
        }

    }
    
}
