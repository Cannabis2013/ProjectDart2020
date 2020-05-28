import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    id: body

    clip: true

    signal requestGamePage
    signal requestSettingsPage
    signal requestLoginPage // Experimental
    signal requestLogOut // Experimental
    signal requestQuit

    property color labelColor: "transparent"
    property color backgroundContentColor: "transparent"

    property int topPadding: 9
    property int leftPadding: 9
    property int bottomPadding: 9
    property int rightPadding: 9
    property int padding: 9

    onTopPaddingChanged: topRectArea.height = body.topPadding
    onLeftPaddingChanged: leftRectArea.width = body.leftPadding
    onBottomPaddingChanged: bottomRectArea.height = body.bottomPadding
    onRightPaddingChanged: bottomRectArea.width = body.rightPadding

    onPaddingChanged: {
        topRectArea.height = body.padding
        leftRectArea.width = body.padding
        bottomRectArea.height = body.padding
        rightRectArea.width = body.padding
    }

    onLabelColorChanged: label.color = labelColor
    onBackgroundContentColorChanged: {
        content.color = backgroundContentColor
        topRectArea.color = backgroundContentColor
        leftRectArea.color = backgroundContentColor
        bottomRectArea.color = backgroundContentColor
        rightRectArea.color = backgroundContentColor
    }

    GridLayout
    {
        columnSpacing: 0
        rowSpacing: 0
        anchors.fill: parent
        rows: 4
        columns: 3

        Rectangle
        {
            id: topRectArea
            Layout.row: 0
            Layout.column: 1

            Layout.fillWidth: true

            height: 9

            color: "transparent"
        }

        Rectangle
        {
            id: leftRectArea

            Layout.row: 0
            Layout.rowSpan: 4
            Layout.column: 0

            width: 9

            Layout.fillHeight: true

            color: "transparent"
        }

        Rectangle
        {
            id: bottomRectArea
            Layout.row: 3
            Layout.column: 1

            Layout.fillWidth: true

            height: 9

            color: "transparent"
        }

        Rectangle
        {
            id: rightRectArea

            Layout.row: 0
            Layout.rowSpan: 4
            Layout.column: 2

            width: 9

            Layout.fillHeight: true

            color: "transparent"
        }

        PageLabelItem {

            id: label

            height: 64
            width: 384

            Layout.fillWidth: true

            Layout.row: 1
            Layout.column: 1

            Layout.maximumHeight: 64
        }

        StartPageContent{
            id: content

            Layout.row: 2
            Layout.column: 1

            Layout.fillWidth: true
            Layout.fillHeight: true

            onGameButtonClicked: requestGamePage()
            onSettingsButtonClicked: requestSettingsPage()
            onLoginButtonClicked: requestLoginPage()
            onLogoutButtonClicked: requestLogOut()
            onQuitButtonClicked: requestQuit()
        }
    }
}
