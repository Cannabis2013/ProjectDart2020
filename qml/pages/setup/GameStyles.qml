import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

ListModel {
        ListElement {
                modeColor: "green"
                modeTitle: "Novice"
                score: "101"
                modeDescription: "The first player to reach 0 or below wins the match."
                mode: 1
        }

        ListElement {
                modeColor: "green"
                modeTitle: "Novice"
                score: "201"
                modeDescription: "The first player to reach 0 or below wins the match."
                mode: 1
        }

        ListElement {
                modeColor: "orange"
                modeTitle: "Novice"
                score: "301"
                modeDescription: "The first player to reach 0 or below wins the match."
                mode: 1
        }

        ListElement {
                modeColor: "orange"
                modeTitle: "Novice"
                score: "501"
                modeDescription: "The first player to reach 0 or below wins the match."
                mode: 1
        }

        ListElement {
                modeColor: "red"
                modeTitle: "Professional"
                score: "301"
                modeDescription: "The first player to reach 0 with bulls or double as last throw wins"
                mode: 0
        }

        ListElement {
                modeColor: "red"
                modeTitle: "Professional"
                score: "501"
                modeDescription: "The first player to reach 0 with bulls or double as last throw wins"
                mode: 0
        }
}
