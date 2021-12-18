import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13
ListViewDelegate{
    id: listItem
    isCheckable: true
    height: 60
    width: parent.width * 0.95
    logoUrl: "qrc:/pictures/Ressources/darttournamentmod.png"
    noDelayPressSelect: true
    x: parent.width / 2 - width / 2
}
