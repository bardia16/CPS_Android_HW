import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.example 1.0

ApplicationWindow {
    visible: true
    width: 341
    height: 800
    title: qsTr("MainWindow")

    Accelerometer {
        id: accelerometer
        onReadingUpdated: {
            accelText.text = output
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            Layout.preferredHeight: 51
            color: "darkgray"
            RowLayout {
                anchors.fill: parent
                spacing: 10

                Label {
                    text: qsTr("Angle:")
                    font.family: "Segoe UI"
                }

                Text {
                    id: textBrowser2
                    text: "Angle value"
                    color: "white"
                    font.family: "Segoe UI"
                }
            }
        }

        Rectangle {
            Layout.preferredHeight: 51
            color: "darkgray"
            RowLayout {
                anchors.fill: parent
                spacing: 10

                Label {
                    text: qsTr("Accel:")
                    font.family: "Segoe UI"
                }

                Text {
                    id: accelText
                    text: "Accelerometer readings will appear here"
                    color: "white"
                }
            }
        }

        Rectangle {
            Layout.preferredHeight: 20
            RowLayout {
                anchors.fill: parent
                spacing: 10

                Label {
                    text: qsTr("Patterns:")
                    font.family: "Segoe UI"
                }
            }
        }

        ListView {
            id: listView
            Layout.preferredHeight: 341
            model: ListModel {
                ListElement { name: "Pattern 1" }
                ListElement { name: "Pattern 2" }
                // Add more patterns as needed
            }
            delegate: Item {
                width: listView.width
                height: 40  // Adjust height as needed

                Rectangle {
                    width: parent.width
                    height: parent.height
                    color: "darkgray"

                    Text {
                        anchors.centerIn: parent
                        text: model.name
                        color: "white"
                    }
                }
            }
        }


        Button {
            id: startRecordingButton
            text: qsTr("Start Recording")
            Layout.preferredHeight: 41
            onClicked: {
                if (text === "Start Recording") {
                    text = "Stop Recording"
                    accelerometer.start()
                } else {
                    text = "Start Recording"
                    accelerometer.stop()
                }
            }
        }

        Button {
            id: startAttemptButton
            text: qsTr("Start Attempt")
            Layout.preferredHeight: 41
            onClicked: {
                text = text === "Start Attempt" ? "Stop Attempt" : "Start Attempt"
            }
        }

        Button {
            id: authenticateButton
            text: qsTr("Authenticate")
            Layout.preferredHeight: 41
            onClicked: {
                // Add your authenticate function here
            }
        }

        Button {
            id: resetButton
            text: qsTr("Reset")
            Layout.preferredHeight: 41
            onClicked: {
                // Add your reset function here
            }
        }
    }
}
