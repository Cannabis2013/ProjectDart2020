import QtQuick 2.7

pragma Singleton

QtObject{
    // Color related
    property color pageColor: "black"
    property color pageBackButtonColor: "gray"
    property color startPageButtonColor : "gray"
    property color startPageTitleColor: "white"
    property color tournamentListViewTextColor: "white"

    // Geometry related
        // Button border radius
    property int pageBackButtonRadius: 5
}
