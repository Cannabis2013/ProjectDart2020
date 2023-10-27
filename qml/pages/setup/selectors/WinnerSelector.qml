import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle {
        color: "transparent"
        clip: true

        signal optionClicked(int mode, int initialScore)

        Flickable {
                anchors.fill: parent
                contentHeight: 128 * 6 + 6 * 5
                boundsBehavior: Flickable.StopAtBounds
                GridLayout {
                        anchors.fill: parent
                        flow: GridLayout.TopToBottom
                        rowSpacing: 6
                        WinnerOption {
                                Layout.fillWidth: true
                                height: 128
                                title: "Novice"
                                initialScore: "101"
                                description: "The first player to reach 0 or below wins the match."
                                onClicked: optionClicked(1, 101)
                        }

                        WinnerOption {
                                Layout.fillWidth: true
                                height: 128
                                title: "Beginner"
                                initialScore: "201"
                                description: "The first player to reach 0 or below wins the match."
                                onClicked: optionClicked(1, 201)
                        }

                        WinnerOption {
                                Layout.fillWidth: true
                                height: 128
                                title: "Beginner"
                                initialScore: "301"
                                description: "The first player to reach 0 or below wins the match."
                                onClicked: optionClicked(1, 301)
                        }

                        WinnerOption {
                                Layout.fillWidth: true
                                height: 128
                                title: "Beginner"
                                initialScore: "501"
                                description: "The first player to reach 0 or below wins the match."
                                onClicked: optionClicked(1, 501)
                        }

                        WinnerOption {
                                Layout.fillWidth: true
                                height: 128
                                title: "Professional"
                                initialScore: "301"
                                description: "The first player to reach 0 with bulls or double as last throw wins"
                                onClicked: optionClicked(0, 301)
                        }

                        WinnerOption {
                                Layout.fillWidth: true
                                height: 128
                                title: "Professional"
                                initialScore: "501"
                                description: "The first player to reach 0 with bulls or double as last throw wins"
                                onClicked: optionClicked(0, 501)
                        }
                }
        }
}
