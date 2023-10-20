import QtQuick 2.0
import QtQuick.Controls 2.15

BlackPage {
        signal backClicked

        property string buttonText: pageHeader.buttonText
        onButtonTextChanged: pageHeader.buttonText = buttonText

        property string pageTitle: pageHeader.pageTitle
        onPageTitleChanged: pageHeader.pageTitle = pageTitle

        header: PageHeader {
                id: pageHeader
                onBackButtonClicked: backClicked()
                color: "#121212"
        }

        anchors.fill: parent
}
