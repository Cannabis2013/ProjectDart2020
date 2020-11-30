import QtQuick 2.7

pragma Singleton

QtObject{
    // Color related
        // Page
    property color pageColor: "black"
    property color pageBackButtonColor: "gray"
        // StartPage
    property color startPageButtonColor : "gray"
    property color startPageTitleColor: "white"
        // GamePageContent
            // TurnControllerItem
    property color navButtonsBackgroundColor: "white"
    property color navButtonsTextColor: "white"
    property color navTextDisplayColor: "white"
    property color navStartButtonBackgroundColor: "gray"
    property color navStartButtonTextColor: "white"
    property color navStartButtonHoveredBackgroundColor: "lightgray"
            // DisplayKeyDataItem
    property color keyTextDisplayColor: "white"
            // ManagePageContent
    property color tournamentListViewTextColor: "white"
    property color manPlayerListViewLabelColor: "white"
    property color manTournamentListViewLabelColor: "white"
            // CRUDButton
    property color cruButtonBackgroundColor: "white"
    property color cruButtonTextColor: "black"
    property color cruButtonHoveredBackgroundColor: "lightgray"
            // CreatePlayerContent/CreatePlayerPopUp
    property color plaButtonBackgroundColor: "gray"
    property color plaButtonHoveredBackgroundColor: "lightgray"
    property color plaButtonTextColor: "white"
        // CreateTournamentContent
            // Buttons
    property color touButtonBackgroundColor: "gray"
    // Geometry related
        // Button border radius
    property int pageBackButtonRadius: 5
}
