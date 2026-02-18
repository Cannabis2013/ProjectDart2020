import QtQuick 6.0

Item {
  function update(){
    const stats = JSON.parse(dartsStats.current())
    lowText.text = `MIN\n${stats.low}`
    averageText.text = `MID\n${stats.average}`
    highText.text = `MAX\n${stats.high}`
    totalText.text = `HIT\n${stats.throwCount}`
    const indexes = JSON.parse(dartsTurns.indexes())
    turnIndex.text = `TRN\n${indexes.turnIndex + 1}`
    roundText.text = `RND\n${indexes.roundIndex}`
  }

  Text {
    id: lowText
    anchors {
      verticalCenter: parent.verticalCenter
      right: averageText.left
    }
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text {
    id: averageText
    anchors {
      verticalCenter: parent.verticalCenter
      right: highText.left
    }
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text {
    id: highText
    anchors {
      verticalCenter: parent.verticalCenter
      right: parent.horizontalCenter
    }
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text {
    id: totalText
    anchors {
      verticalCenter: parent.verticalCenter
      left: parent.horizontalCenter
    }
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text{
    id: turnIndex
    anchors {
      verticalCenter: parent.verticalCenter
      left:totalText.right
    }
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text{
    id: roundText
    anchors {
      verticalCenter: parent.verticalCenter
      left: turnIndex.right
    }
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
}
