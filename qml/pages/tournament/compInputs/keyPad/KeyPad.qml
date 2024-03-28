import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "keyPad.js" as Scripts

Item {
        GridLayout {
                id: numberPads
                width: parent.width * 0.8
                height: parent.height
                columns: 4
                columnSpacing: 0
                rowSpacing: 0
                layoutDirection: Qt.RightToLeft
                Repeater {
                        model: 20
                        NumberPad {
                                padValue: 20 - index
                                text: `${20 - index}`
                                onPadClicked: padValue => Scripts.handleNumberPadClick(padValue)
                        }
                }
        }

        ColumnLayout {
                id: specialPads
                spacing: 0
                anchors.left: numberPads.right
                anchors.right: parent.right
                height: parent.height
                ModPad {
                        id: modTripple
                        text: "T"
                        onModClicked: modId => Scripts.selectTrippeMod(modId)
                }

                ModPad {
                        id: modDouble
                        text: "D"
                        onModClicked: modId => Scripts.selectDoubleMod(modId)
                }

                NumberPad {
                        color: "green"
                        text: "25"
                        padValue: 25
                        onPadClicked: value => Scripts.handleSpecialPadClick(padValue)
                }

                NumberPad {
                        color: "red"
                        padValue: 50
                        text: "50"
                        onPadClicked: value => Scripts.handleSpecialPadClick(padValue)
                }

                NumberPad {
                        color: "orange"
                        text: ">>"
                        onPadClicked: value => reportScore()
                }
        }
}
