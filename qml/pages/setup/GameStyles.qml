import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Item {
        signal optionClicked(int mode, int initialScore)

        Flickable {
                clip: true
                anchors.fill: parent
                contentHeight: 128 * 6 + 5 * 6
                boundsBehavior: Flickable.StopAtBounds
                Column {
                        anchors.fill: parent
                        spacing: 6
                        GameStyleRect {
                                width: parent.width
                                height: 128
                                color: "blue"
                                title: "Novice"
                                initialScore: "101"
                                description: "The first player to reach 0 or below wins the match."
                                onClicked: optionClicked(1, 101)
                        }

                        GameStyleRect {
                                width: parent.width
                                height: 128
                                title: "Beginner"
                                initialScore: "201"
                                description: "The first player to reach 0 or below wins the match."
                                onClicked: optionClicked(1, 201)
                        }

                        GameStyleRect {
                                width: parent.width
                                height: 128
                                title: "Beginner"
                                color: "orange"
                                initialScore: "301"
                                description: "The first player to reach 0 or below wins the match."
                                onClicked: optionClicked(1, 301)
                        }

                        GameStyleRect {
                                width: parent.width
                                height: 128
                                title: "Beginner"
                                color: "orange"
                                initialScore: "501"
                                description: "The first player to reach 0 or below wins the match."
                                onClicked: optionClicked(1, 501)
                        }

                        GameStyleRect {
                                width: parent.width
                                height: 128
                                color: "red"
                                title: "Professional"
                                initialScore: "301"
                                description: "The first player to reach 0 with bulls or double as last throw wins"
                                onClicked: optionClicked(0, 301)
                        }

                        GameStyleRect {
                                width: parent.width
                                height: 128
                                color: "red"
                                title: "Professional"
                                initialScore: "501"
                                description: "The first player to reach 0 with bulls or double as last throw wins"
                                onClicked: optionClicked(0, 501)
                        }
                }
        }
}
