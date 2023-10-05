import QtQuick 2.0
import QtQuick.Controls 2.15

Page {
        signal backClicked

        property string buttonText: pageHeader.buttonText
        onButtonTextChanged: pageHeader.buttonText = buttonText

        property string pageTitle: pageHeader.pageTitle
        onPageTitleChanged: pageHeader.pageTitle = pageTitle

        Rectangle {
                id: backdrop
                anchors.fill: parent
                color: "black"
        }

        header: PageHeader {
                id: pageHeader
                onBackButtonClicked: backClicked()
        }

        anchors.fill: parent
}
