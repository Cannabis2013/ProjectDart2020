import QtQuick 6.0
import QtQuick.Controls 6.0
import "../components"

Page {
  signal backClicked

  header: PageHeader{
    pageTitle: "About"
    onBack: backClicked()
  }

  Text {
    id: aboutText

    anchors.fill: parent
    anchors.margins: 8

    wrapMode: Text.WordWrap
    font.pointSize: 16

    onLinkActivated: link => Qt.openUrlExternally(link)

    color: "white"
  }

  Component.onCompleted: aboutText.text = fileHtml.aboutHtml()
}
