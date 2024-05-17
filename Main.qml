import QtQuick 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import com.example 1.0

ApplicationWindow {
    visible: true
    width: 341
    height: 800
    title: qsTr("MainWindow")

    function addNewMovement(xValue, yValue) {

        // Append the new item to the model
        outputArea.append("X: "+ xValue + "  Y: " + yValue + "\n");
    }

    function updateAccelText(output) {
        accelText.text = "Accel: " + output;
    }

    function updateStatusLabel(output) {
        statusText.text = "Status: " + output;
    }

    Accelerometer {
        id: accelerometer
        onReadingUpdated: {
            updateAccelText(output)
            // Assuming output contains the x and y values as strings separated by spaces
            /*var values = output.split(" ");
            //console.log(values);
            movementDatabase.handleNewAcceleration(parseFloat(values[1]), parseFloat(values[4]), accelerometer.getXBias(), accelerometer.getYBias())*/
        }
        onNewAcceleration: movementDatabase.handleNewAcceleration(x, y, velocityX, velocityY, accelerometer.getXBias(), accelerometer.getYBias())
        onCalibrationFinished: updateStatusLabel(output)
    }

    MovementDatabase {
        id: movementDatabase
        onMovementsUpdated: addNewMovement(x_pos, y_pos);
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        // Status, Angle, Accel, and Patterns rectangles
        ColumnLayout {
            anchors.leftMargin: 20
            spacing: 10

            Rectangle {
                Layout.preferredHeight: 51
                color: "darkgray"
                ColumnLayout {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 10
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                    Label {
                        id: statusText
                        text: qsTr("Status:")
                        font.family: "Segoe UI"
                    }
                }
            }

            Rectangle {
                Layout.preferredHeight: 51
                color: "darkgray"
                ColumnLayout {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 10
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                    Label {
                        id: angleText
                        text: qsTr("Angle:")
                        font.family: "Segoe UI"
                    }
                }
            }

            Rectangle {
                Layout.preferredHeight: 51
                color: "darkgray"
                ColumnLayout {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 10
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                    Label {
                        id: accelText
                        text: qsTr("Accel:")
                        font.family: "Segoe UI"
                    }
                }
            }

            Rectangle {
                Layout.preferredHeight: 20
                ColumnLayout {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 10
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                    Label {
                        text: qsTr("Patterns:")
                        font.family: "Segoe UI"
                    }
                }
            }
        }

        // TextArea in ScrollView
               ScrollView {
                   width: parent.width
                   height: 200

                   TextArea {
                       id: outputArea
                       anchors.fill: parent
                       readOnly: true
                       wrapMode: Text.Wrap
                       text: "Output will be displayed here..."
                   }
               }


        // Buttons
        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 10

            Button {
                id: calibration
                text: qsTr("Calibration")
                Layout.preferredHeight: 41
                onClicked: {
                    accelerometer.calibration();
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
}
