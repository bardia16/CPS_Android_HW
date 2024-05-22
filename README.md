# Motion-based Authentication

## Project Overview

This project aims to develop a motion-based authentication system leveraging the accelerometer and gyroscope sensors in Android smartphones. By understanding and utilizing the Android operating system's capabilities and its interaction with these sensors, we will create a system that authenticates users based on specific movements of their smartphone.

Here we briefly go through the goals we aim to achieve: 
1. Learn Android Sensor Integration focusing on the accelerometer and gyroscope.
2. Motion Data collection
3. Pattern Authentication

## Challenges
the challenges we face in the project:
1. **Sensor Accuracy:**
2. **Saving the direction:**

## Project Directory Structure and Contents

- **.qmlproject file:** This file is a configuration file for a Qt Quick application. It outlines the structure and settings needed to organize and manage various resources and settings for the project. It ensures all necessary resources (QML files, JavaScript files, images, fonts, audio, video, shaders) are included and managed. also, it sets up environment variables for application configuration and debugging.
- **.qmlproject.qtds:** It is an XML file used by Qt Design Studio and Qt Creator to store various project-specific settings and configurations.
- **.qmlproject.user:** This is an XML file that stores user-specific project settings. These settings are typically customized by the user for their development environment.

** The three files above will be created automatically when we build our QtQuick project. 
  
- **.qml file:** This file defines an application window with a UI to display sensor data, handle calibration, and manage motion-based authentication. It includes UI elements like labels, text areas, and buttons for user interaction. and also includes some logic to handle accelerometer and gyroscope data, including updates and calibration and the functions to update the UI and manage the state of the application based on sensor readings.
- **.cpp and .h:** These files are the source files written by C++ and .h files are their corresponding header files.

## UI and its Connections to the Logic

Main.qml file contains the codes of UI of our application and also it can be considered as a connection between our source files. these connections are made and handled by signals. the format of this file is like javascript. 

### ApplicationWindow:
```QML
ApplicationWindow {
    visible: true
    width: 341
    height: 800
    title: qsTr("MainWindow")
```
Defines the main application window with properties for visibility, size, and title.

### Properties:
```QML
    property string gyroCalibrationMessage: ""
    property string accelCalibrationMessage: ""
    property bool gyroCalibrated: false
    property bool accelCalibrated: false
```
These properties store calibration messages and flags indicating whether the gyroscope and accelerometer are calibrated.
### Functions:
We have implemented some functions in this file that handle various tasks: 
#### addNewMovement
```QML
    function addNewMovement(xValue, yValue, angle, direction) {
        var formattedX = xValue.toFixed(2);
        var formattedY = yValue.toFixed(2);
        var formattedAngle = angle.toFixed(2);

        outputArea.text += "Position: X: " + formattedX + " Y: " + formattedY + " Angle: " +
                formattedAngle + " Direction: " + direction + "\n";
    }
```
Whenever this function is called the text in the ScrollView element will be updated by adding new movement to the box which shows the position, angle, and direction.
Here `var formattedX = xValue.toFixed(2);` Formats the `xValue` to two decimal places and assigns it to the variable `formattedX`. the next 2 lines are just like this part.

#### updateAccelText
```QML
    function updateAccelText(output) {
        accelText.text = "Accel: " + output;
    }
```
whenever this function is called the text of Accel label will be updated.

#### updateGyroText
```QML
    function updateGyroText(output) {
        angleText.text = "Angle: " + output;
    }
```
whenever this function is called the text of Angle label will be updated.

#### updateStatusLabel
```QML
    function updateStatusLabel(output) {
        statusText.text = "Status: " + output;
    }
```
whenever this function is called the text of Status label will be updated.

#### checkCalibrationCompletion
```QML
    function checkCalibrationCompletion() {
        if (gyroCalibrated && accelCalibrated) {
            updateStatusLabel(gyroCalibrationMessage + "\n" + accelCalibrationMessage);
        }
    }
```
whenever this function is called the text of Status label will be conditionally updated. the condition is based on two parameters "gyroCalibrated" and "accelCalibrated", which are status parameters that show whether each sensor is yet calibrated or not.

### Sensor Components:
```QML
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

    MovementDatabase {
        id: movementDatabase
        onMovementsUpdated: addNewMovement(x_pos, y_pos, angle, direction);
    }
```
### UI Layout:
```QML
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10
```
The `ColumnLayout` is used to organize the UI components in a vertical stack. The `anchors.fill: parent` ensures that the layout fits the size of its parent container, which is the main application window in this case. The `anchors.margins: 20` add margin to the window. The `spacing: 10` ensures that there is a free space between each of the components which improves readability.

** In the UI Layout, we have some elements: 

#### Label
A Label is a simple UI component used to display a small amount of text.
each label has these properties: 
- id: A unique identifier for the element.
- text: The text content displayed by the label.
- Layout.preferredHeight: Sets the preferred height of the label.
- Layout.fillWidth: Makes the label fill the available width.
- font: Font properties like family, size, boldness, etc.
- verticalAlignment: set the alignment of the text.

  ** Here we have 4 labels including statusText, angleText, accelText, and patterns.
  ```QML
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
  ```
  - statusText: this text shows the status of Calibration or Authentication.
  - angleText:
  - accelText:
  - patterns: this is just a label for the ScrolView part. 
in the following picture, you can see each label and its corresponding text.

#### ScrollView
A ScrollView is a container that provides a scrollable area for its child elements, which is useful when you have content that exceeds the available space.
each scrollView has these properties: 
- Layout.fillWidth: Makes the label fill the available width.
- Layout.preferredHeight: Sets the preferred height of the label.
- TextArea: This is a multi-line text input field in QML. It's being used as the child element of the ScrollView.
    - id: This provides a unique identifier for the TextArea
    - wrapMode: This property determines how the text wraps within the TextArea. In this case, it wraps at word boundaries or anywhere if necessary.
    - font.pixelSize: This sets the size of the text displayed within the TextArea.
    - font.bold: set if we want the text to be bold or not.
    - readOnly: This property makes the TextArea read-only, meaning users can't edit its content directly.

```QML
        ScrollView {
            Layout.fillWidth: true
            Layout.preferredHeight: 200
            TextArea {
                id: outputArea
                wrapMode: TextArea.WrapAtWordBoundaryOrAnywhere
                font.pixelSize: 14
                font.bold: true
                readOnly: true
            }
        }
```
in the following picture, you can see the scrollView and its inside text. Whenever one pattern is captured this text will be updated and one pattern will be appended.

#### Button 
A Button is an interactive component that users can click to trigger actions.
each button has these properties: 
- id: A unique identifier for the element.
- text: The label displayed on the button.
- Layout.fillWidth: Makes the button fill the available width.
- Layout.preferredHeight: Sets the preferred height of the button.
- onClicked: A signal handler that defines what happens when the button is clicked.

** Here we have 5 buttons:
```QML
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
                movementDatabase.reset();
                gyroscope.reset();
                // accelerometer.reset();
            }
        }
```
- calibration: when this button is clicked the calibration status will reset.
- startRecordingButton: the text on this button will shuffled whenever is clicked. if it was "Start Recording" by clicking it will become "Stop Recording". Also, accelerator and gyroscope sensors will start working. then when we click again on this button the text will change back to "Start Recording". Also, the accelerator and gyroscope sensors will stop working.
- startAttemptButton: 
- authenticateButton:
- resetButton: when this button is clicked our sensors will reset. and all the movements in movementDatabase will be deleted. 

## main entry to the project
```QML
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Accelerometer>("com.example", 1, 0, "Accelerometer");
    qmlRegisterType<Gyroscope>("com.example", 1, 0, "Gyroscope");
    qmlRegisterType<MovementDatabase>("com.example", 1, 0, "MovementDatabase");

    QQmlApplicationEngine engine;

    MovementDatabase movementDatabase;
    engine.rootContext()->setContextProperty("movementDatabase", &movementDatabase);

    const QUrl url(u"qrc:/QtQuickProject/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
```
main.cpp file is the main entry point for a Qt Quick application. It sets up the application, registers custom QML types, and loads the main QML file to start the application. <br/>
when we create a QtQuick project it will automatically generate this file with initial codes. So just need to add these parts:
```QML
    qmlRegisterType<Accelerometer>("com.example", 1, 0, "Accelerometer");
    qmlRegisterType<Gyroscope>("com.example", 1, 0, "Gyroscope");
    qmlRegisterType<MovementDatabase>("com.example", 1, 0, "MovementDatabase");
```
These lines of code are registering custom C++ classes with the QML type system. This allows these classes to be used directly in QML files. <br/>
Template Parameter (<T>): This specifies the C++ class we are registering. For example, Accelerometer, Gyroscope, and MovementDatabase in our case. <br/>
"com.example": This is the URI (Uniform Resource Identifier) of the module in which the type is registered. It acts like a namespace or module name in QML. As you see it is imported in the .QML file. <br/>
1 and 0 are used for the version number of the module, the major and minor part. in this case, our version will be 1.0. <br/>
last parameter is the name by which the type will be known in QML. by this way we can instantiate and use objects of these types in our .QML file. <br/>
whenever we make a file (object) and we want to use that object in our QML file, by this way we can add it to our created module ("com.example").
```QML
    MovementDatabase movementDatabase;
    engine.rootContext()->setContextProperty("movementDatabase", &movementDatabase);
```
This makes the instance accessible in QML files under the name movementDatabase. later we will observe and explain about movementDatabase. 

## Accelerometer class
Accelerometer class is designed to interface with a QML application to handle accelerometer sensor readings. It provides functionality for starting and stopping the sensor, processing the sensor readings, applying a Kalman filter for noise reduction, handling calibration, and emitting relevant signals for use in a QML application. Here we explain each part of this class in detail:

### Constructor
```cpp
Accelerometer::Accelerometer(QObject *parent) : QObject(parent), x_bias(0.0), y_bias(0.0),
    xKalman(0.1, 1, 0.1, 0.0), yKalman(0.1, 1, 0.1, 0.0), velocity(0.0),velocityX(0.0), velocityY(0.0) // Initialize Kalman filters
{
    sensor = new QAccelerometer(this);
    timer = new QTimer(this);
    calibrationTimer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Accelerometer::onSensorReadingChanged);
    connect(calibrationTimer, &QTimer::timeout, this, &Accelerometer::onCalibrationFinished);
}
```
here we initialize member variables, including bias, Kalman filter, and velocities.
the reason that we have bias is that when we do calibration we check the base state of velocity of the cellphone. and we name this initial state as bias and when we want to calculate new velocities we should consider this bias as well. Kalman filter is for noise reduction. we will explain its algorithm later. but briefly, it reduce the noise by choosing to consider and rely more on the older data or newer ones. In this way, sudden short changes in velocity won't affect the result. for the velocity we have 3 kinds, one for x direction and the other for y direction and one of them is the general velocity. <br/>
then we make an instance of the available QAccelerometer sensor object. <br/>
we have two types of timers. One is for sampling intervals (timer) and the other (calibrationTimer) is for handling calibration. then we connect the timer signal to `onSensorReadingChanged` function. so whenever a timer reach a specified time(we have specified the time intervals in this file in start method), and timeout occurs this function will be called. <br/>
also we connect the `calibrationTimer` signal to  `onCalibrationFinished` function. so whenever a this timer reach a specified time(we have specified the time intervals in .... file), and timeout occurs this function will be called.
### Destructor
```cpp
Accelerometer::~Accelerometer()
{
    stop();
    delete sensor;
}
```
Ensures that the sensor is stopped and deleted when the Accelerometer object is destroyed to clean up resources properly.
### Start method and Stop method
```cpp
void Accelerometer::start()
{
    if (!sensor->isActive())
    {
        sensor->start();
        timer->start(accel_sampling_interval);
        emit activeChanged();
        qDebug() << "Accelerometer started.";
    }
}

void Accelerometer::stop()
{
    if (sensor->isActive())
    {
        sensor->stop();
        timer->stop();
        calibrationTimer->stop();
        emit activeChanged();
        qDebug() << "Accelerometer stopped.";
    }
}
```
- start: Starts the accelerometer sensor and a timer to periodically read sensor data. Emits the activeChanged signal and logs the action. later we will show what will happen when the activeChanged signal is emitted. 
- stop: Stops the accelerometer sensor and the timers. Emits the activeChanged signal and logs the action.
### Sensor Reading Handling
onSensorReadingChanged: Handles sensor readings when the timer times out.
```cpp
void Accelerometer::onSensorReadingChanged()
{
    QAccelerometerReading *reading = sensor->reading();
    if (reading)
    {
        qreal x = reading->x();
        qreal y = reading->y();

        // Apply Kalman filter
        x = xKalman.update(x);
        y = yKalman.update(y);

        // Adjust for bias
        if (std::abs(x) <= accel_threshold)
            x = 0.0;
        else
            x -= x_bias;

        if (std::abs(y) <= accel_threshold)
            y = 0.0;
        else
            y -= y_bias;

        if (x == 0 && y == 0) // frictional accel
        {
            QVector2D newVelocities = frictionalAccel(velocityX, velocityY);
            velocityX = newVelocities.x();
            velocityY = newVelocities.y();
        }

        velocityX += x * accel_sampling_interval / 1000;
        velocityY += y * accel_sampling_interval / 1000;

        QString output = QStringLiteral("X: %1  Y: %2  Velocity: X: %3  Y: %4")
                             .arg(QString::number(x, 'f', 2),
                                  QString::number(y, 'f', 2),
                                  QString::number(velocityX, 'f', 2),
                                  QString::number(velocityY, 'f', 2));
        emit readingUpdated(output);
        emit newAcceleration(x, y, velocityX, velocityY);
        //qDebug() << output;
    }
    else
    {
        qDebug() << "No reading available.";
    }
}
```
when this function is called, first we read the data from the accelerometer sensor. if there is data to read we do the following steps otherwise we log the appropriate message indicating that we have no data to read. then we extract the velocity of x and y from the read data. and update them by applying the Kalman algorithm for noise reduction. 
