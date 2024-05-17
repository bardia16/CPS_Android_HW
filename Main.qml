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
        newLine = "X: "+ xValue + "  Y: " + yValue + "\n";
        outputArea.text = outputArea.text + newLine;
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
        anchors.margins: 20
        spacing: 10


        Label {
            id: statusText
            Layout.preferredHeight: 51
            Layout.fillWidth: true
            text: qsTr("Status:")
            font.family: "Segoe UI"
            verticalAlignment: "AlignVCenter"
        }

        Label {
            id: angleText
            text: qsTr("Angle:")
            Layout.preferredHeight: 51
            Layout.fillWidth: true
            font.family: "Segoe UI"
            verticalAlignment: "AlignVCenter"
        }

        Label {
            id: accelText
            text: qsTr("Accel:")
            Layout.preferredHeight: 51
            Layout.fillWidth: true
            font.family: "Segoe UI"
            verticalAlignment: "AlignVCenter"
        }

        Label {
            id: patterns
            text: qsTr("Patterns:")
            Layout.preferredHeight: 51
            Layout.fillWidth: true
            font.family: "Segoe UI"
            verticalAlignment: "AlignVCenter"
        }

        // TextArea in ScrollView
        ScrollView{
            Layout.fillWidth: true
            Layout.preferredHeight: 200
            TextArea{
                id: outputArea
                wrapMode: "WrapAtWordBoundaryOrAnywhere"
                font.pixelSize: 18
                font.bold: true
                readOnly: true
            }
        }


        Button {
            id: calibration
            text: qsTr("Calibration")
            Layout.fillWidth: true
            Layout.preferredHeight: 41
            onClicked: {
                accelerometer.calibration();
            }
        }

        Button {
            id: startRecordingButton
            text: qsTr("Start Recording")
            Layout.fillWidth: true
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
            Layout.fillWidth: true
            Layout.preferredHeight: 41
            onClicked: {
                text = text === "Start Attempt" ? "Stop Attempt" : "Start Attempt"
            }
        }

        Button {
            id: authenticateButton
            text: qsTr("Authenticate")
            Layout.fillWidth: true
            Layout.preferredHeight: 41
            onClicked: {
                // Add your authenticate function here
            }
        }

        Button {
            id: resetButton
            text: qsTr("Reset")
            Layout.fillWidth: true
            Layout.preferredHeight: 41
            onClicked: {
                // Add your reset function here
            }
        }
    }

    Component.onCompleted: {
        for (let i = 1; i < 20; i++){
            outputArea.text += `hello world ${i}\n`
        }
    }
}
