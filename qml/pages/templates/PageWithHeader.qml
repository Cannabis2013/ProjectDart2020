import QtQuick 2.0
import QtQuick.Controls 2.15

Page {
        id: pageRect
        signal backClicked
        signal backLongClicked

        property string buttonText: pageHeader.buttonText
        onButtonTextChanged: pageHeader.buttonText = buttonText

        property string pageTitle: pageHeader.pageTitle
        onPageTitleChanged: pageHeader.pageTitle = pageTitle

        header: PageHeader {
                id: pageHeader
                onBackButtonClicked: pageRect.backClicked()
                onBackButtonLongClicked: pageRect.backLongClicked()
        }

        anchors.fill: parent
}
