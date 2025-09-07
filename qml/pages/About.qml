import QtQuick 6.0
import QtQuick.Layouts 1.3
import "../templates"

PageWithHeader {
  pageTitle: "About"

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
