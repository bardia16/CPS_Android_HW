import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.example 1.0

ApplicationWindow {
    visible: true
    width: 341
    height: 800
    title: qsTr("MainWindow")

    // Variables to store calibration messages and completion flags
    property string gyroCalibrationMessage: ""
    property string accelCalibrationMessage: ""
    property bool gyroCalibrated: false
    property bool accelCalibrated: false

    function addNewMovement(xValue, yValue, angle, direction) {
        var formattedX = xValue.toFixed(2);
        var formattedY = yValue.toFixed(2);
        var formattedAngle = angle.toFixed(2);

        outputArea.text += "Position: X: " + formattedX + " Y: " + formattedY + " Angle: " +
                formattedAngle + " Direction: " + direction + "\n";
    }

    function updateAccelText(output) {
        accelText.text = "Accel: " + output;
    }

    function updateGyroText(output) {
        angleText.text = "Angle: " + output;
    }

    function updateStatusLabel(output) {
        statusText.text = "Status: " + output;
    }

    function checkCalibrationCompletion() {
        if (gyroCalibrated && accelCalibrated) {
            updateStatusLabel(gyroCalibrationMessage + "\n" + accelCalibrationMessage);
        }
    }

    Accelerometer {
        id: accelerometer
        onReadingUpdated: updateAccelText(output)
        onNewAcceleration: movementDatabase.handleNewAcceleration(x, y, velocityX, velocityY, accelerometer.getXBias(), accelerometer.getYBias())
        onCalibrationFinished: {
            accelCalibrationMessage = "Accelerometer: " + output;
            accelCalibrated = true;
            checkCalibrationCompletion();
        }
    }

    Gyroscope {
        id: gyroscope
        onReadingUpdated: updateGyroText(output)
        onNewRotation: movementDatabase.handleNewAngle(alpha)
        onCalibrationFinished: {
            gyroCalibrationMessage = "Gyroscope: " + output;
            gyroCalibrated = true;
            checkCalibrationCompletion();
        }
    }

    PatternDatabase {
        id: patternDatabase
        onAuthenticationResult: updateStatusLabel(output)
    }

    MovementDatabase {
        id: movementDatabase
        onMovementsUpdated: addNewMovement(x_pos, y_pos, angle, direction);
        onNewPattern:
        {
            patternDatabase.addPattern(pattern)
            patternDatabase.savePatternsToJson("Patterns.json")
        }
        onNewAttempt: patternDatabase.authenticatePattern(pattern)
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

        ScrollView {
            Layout.fillWidth: true
            Layout.preferredHeight: 300
            TextArea {
                id: outputArea
                wrapMode: TextArea.WrapAtWordBoundaryOrAnywhere
                font.pixelSize: 12
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
                // Reset calibration status
                gyroCalibrated = false;
                accelCalibrated = false;
                gyroCalibrationMessage = "";
                accelCalibrationMessage = "";

                gyroscope.calibration();
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
                    gyroscope.start()
                } else {
                    text = "Start Recording"
                    accelerometer.stop()
                    gyroscope.stop()
                    movementDatabase.createNewPattern(false)
                }
            }
        }

        Button {
            id: startAttemptButton
            text: qsTr("Start Attempt")
            Layout.fillWidth: true
            Layout.preferredHeight: 41
            onClicked: {
                if (text === "Start Attempt") {
                    text = "Stop Attempt"
                    accelerometer.start()
                    gyroscope.start()
                } else {
                    text = "Start Attempt"
                    accelerometer.stop()
                    gyroscope.stop()
                    movementDatabase.createNewPattern(true)
                }
            }
        }

        /*Button {
            id: authenticateButton
            text: qsTr("Authenticate")
            Layout.fillWidth: true
            Layout.preferredHeight: 41
            onClicked: {
                // Add your authenticate function here
            }
        }*/

        Button {
            id: resetButton
            text: qsTr("Reset")
            Layout.fillWidth: true
            Layout.preferredHeight: 41
            onClicked: {
                movementDatabase.reset();
                gyroscope.reset();
                // accelerometer.reset();
            }
        }
    }
}
