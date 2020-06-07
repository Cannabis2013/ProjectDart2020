import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

ListView
{
    Layout.fillWidth: true
    Layout.fillHeight: true

    function addItem(firstName, lastName, eMail, id = 0)
    {
        listModel.append({"firstName" : firstName,"lastName" : lastName, "email" : eMail, "uuid" : id});
    }
    
    
    model: ListModel {
        id: listModel
    }
    
    delegate: PushButton{
        id: listItem

        clip: true

        hoveredColor: "transparent"
        hoveredTextColor: "blue"

        height: 70
        width: bodyLayout.width

        backgroundColor: "transparent"

        text: "Full name: " + firstName + " " + lastName + "\n" + "E-mail:" + email + "\n" + "Uuid: " + uuid
    }
}
