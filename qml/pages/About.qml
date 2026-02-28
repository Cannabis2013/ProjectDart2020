import QtQuick 6.0
import QtQuick.Controls 6.0
import "../components"

Page {
  id: aboutPage

  signal backClicked

  header: PageHeader{
    pageTitle: "About"
    onBack: aboutPage.backClicked()
  }

  Text {
    id: aboutText

    anchors.fill: parent
    anchors.margins: 8

    wrapMode: Text.WordWrap
    font.pointSize: 16

    onLinkActivated: link => Qt.openUrlExternally(link)
    text: `
    <html>
        Author: Martin Hansen
        <br>
        Rank: Master developer
        <br>
        <br>
        Darts 501 is a popular game for both professionals and amateurs. This application aims to enhance the game experience
        by reducing the need for score calculations.
        <br>
        <br>
        The rules is largely inspired by the rules inferred from
        <a href="https://billard.dk/shop/cms-spilleregler-dart.html?CookieConsentChanged=1">billard.dk</a>
    </html>
    `
    color: "white"
  }
}
