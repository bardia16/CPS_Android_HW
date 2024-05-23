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
each `scrollView` has these properties: 
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
in the following picture, you can see the `scrollView` and its inside text. Whenever one pattern is captured this text will be updated and one pattern will be appended.

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
- resetButton: when this button is clicked our sensors will reset. and all the movements in `movementDatabase` will be deleted. 

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
Template Parameter (<T>): This specifies the C++ class we are registering. For example, `Accelerometer`, `Gyroscope`, and `MovementDatabase` in our case. <br/>
"com.example": This is the URI (Uniform Resource Identifier) of the module in which the type is registered. It acts like a namespace or module name in QML. As you see it is imported in the .QML file. <br/>
1 and 0 are used for the version number of the module, the major and minor part. in this case, our version will be 1.0. <br/>
last parameter is the name by which the type will be known in QML. by this way we can instantiate and use objects of these types in our .QML file. <br/>
whenever we make a file (object) and we want to use that object in our QML file, by this way we can add it to our created module ("com.example").
```QML
    MovementDatabase movementDatabase;
    engine.rootContext()->setContextProperty("movementDatabase", &movementDatabase);
```
This makes the instance accessible in QML files under the name `movementDatabase`. later we will observe and explain about `movementDatabase`. 

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
these velocities will be calculated based on the acceleration and time by the formula: $ a * t = delta v $ and we need to add it to the previous velocity to reach the new velocity. 
these velocities will be updated after each time intervals. <br/>
then we make an instance of the available `QAccelerometer` sensor object. <br/>
we have two types of timers. One is for sampling intervals (timer) and the other (calibrationTimer) is for handling calibration. then we connect the timer signal to `onSensorReadingChanged` function. so whenever a timer reaches a specified time(we have specified the time intervals in this file in start method), and timeout occurs this function will be called. <br/>
also, we connect the `calibrationTimer` signal to  `onCalibrationFinished` function. so whenever this timer reaches a specified time(we have specified this time duration in calibration method), and timeout occurs this function will be called. <br/>
the reason that we have `calibrationTimer` is that for calculating the initial bias we should get many samples from the sensors in one period of time and calculate the average. thus for indicating the duration of this period we need to set a `calibrationTimer`.
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
- start: Starts the accelerometer sensor and a timer to periodically read sensor data. Emits the activeChanged signal and logs the action.
- stop: Stops the accelerometer sensor and the timers. Emits the `activeChanged` signal and logs the action.
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
this function will be called after each time interval, first, we read the data from the accelerometer sensor. if there is data to read we do the following steps otherwise we log the appropriate message indicating that we have no data to read. then we extract the velocity of x and y from the read data. and update them by applying the Kalman algorithm for noise reduction. <br/>
we have a threshold for acceleration and whenever we are less than that threshold we consider the acceleration as zero. the reason is that to set small values to zero to handle sensor noise. we've determined this variable by trial and error. 
so we check if the acceleration is less than that threshold or not. if not, we apply bias and reach the actual acceleration. 
```cpp
        if (x == 0 && y == 0) // frictional accel
        {
            QVector2D newVelocities = frictionalAccel(velocityX, velocityY);
            velocityX = newVelocities.x();
            velocityY = newVelocities.y();
        }
```
here we consider friction force and simulate it. if we weren't considering this force, when the acceleration becomes zero, it will assume that henceforward we have a constant, not zero velocity. but in reality, we have friction force which will reduce the velocity until it becomes zero and stops. so in this code is checked if our acceleration is zero or not, if yes, we call the `frictionalAccel` function. we will explain about this function later. it will handle how the velocity should be reduced. then it returns new velocities.
```cpp
        velocityX += x * accel_sampling_interval / 1000;
        velocityY += y * accel_sampling_interval / 1000;
```
here we update our velocities in both directions. To do this, we multiply the current velocities by time intervals to reach delta v. Then we add it to previous velocities (division by 1000 is for that our unit for time is mili second so we should convert it to second).
```cpp
        QString output = QStringLiteral("X: %1  Y: %2  Velocity: X: %3  Y: %4")
                             .arg(QString::number(x, 'f', 2),
                                  QString::number(y, 'f', 2),
                                  QString::number(velocityX, 'f', 2),
                                  QString::number(velocityY, 'f', 2));
        emit readingUpdated(output);
        emit newAcceleration(x, y, velocityX, velocityY);
```
here we can see the format of the output that will be shown on the screen of our application which shows the accelerations and velocities.
at the end, we emit signals with the updated values for use in the QML frontend.
we will disscuss these signals later. but briefly `newAcceleration` signal will handle our movements (check if we have finished one movement or not yet in order to add it to our movement database). the connection of this signal can be seen in .QML file. <br/>
`readingUpdated` signal is emited to handle what should be shown on the screen. 
### Frictional Acceleration Calculation
frictionalAccel: Simulates frictional deceleration on the velocities to gradually bring them to zero when no acceleration is detected.
```cpp
QVector2D Accelerometer::frictionalAccel(qreal velocityX, qreal velocityY)
{
    qreal frictionalDecay = accel_threshold * accel_sampling_interval / 1000;

    if (velocityX > 0) // If velocityX is positive
    {
        velocityX -= frictionalDecay;
        if (velocityX < 0) // Ensure velocity doesn't go negative
            velocityX = 0;
    }
    else if (velocityX < 0) // If velocityX is negative
    {
        velocityX += frictionalDecay;
        if (velocityX > 0) // Ensure velocity doesn't go positive
            velocityX = 0;
    }

    if (velocityY > 0) // If velocityY is positive
    {
        velocityY -= frictionalDecay;
        if (velocityY < 0) // Ensure velocity doesn't go negative
            velocityY = 0;
    }
    else if (velocityY < 0) // If velocityY is negative
    {
        velocityY += frictionalDecay;
        if (velocityY > 0) // Ensure velocity doesn't go positive
            velocityY = 0;
    }

    return QVector2D(velocityX, velocityY);
}
```
this function will get the current velocities in both directions. then first calculate by which rate it should reduce the velocity. To calculate this, we multiply an assumed acceleration of friction by the time intervals to reach delta v. This way, we have a decay rate(division by 1000 is for that our unit for time is mili second, so we should convert it to second). in the conditional statements, we check if our velocities in each direction is positive or not. for example, if our velocity in x direction is positive it means that we should reduce it and subtract the frictionDecay from the velocity. after that, we will check if the velocity goes under zero or not. if yes, we consider the new velocity as zero. for other cases accordingly we apply this approach.

### Calibration Methods
```cpp
void Accelerometer::calibration()
{
    sensor->start();
    x_values.clear();
    y_values.clear();
    calibrationTimer->start(calibrationDuration);
    connect(sensor, &QAccelerometer::readingChanged, this, &Accelerometer::onCalibrationReadingChanged);
}
```
calibration: Starts the sensor and prepares for calibration by clearing previous values and starting a timer for the calibration duration. from this time we connect `onCalibrationReadingChanged` function to the `readingChanged` signal. it says that for the calibration process we will manually emit reading data signal to read data form sensor in time intervals. instead, the `readingChanged` signal will be authomatically emited whenever a new data is available to read on sensor. 
```cpp
void Accelerometer::onCalibrationReadingChanged()
{
    QAccelerometerReading *reading = sensor->reading();
    if (reading)
    {
        x_values.append(reading->x());
        y_values.append(reading->y());
    }
    else
    {
        qDebug() << "No reading available.";
    }
}
```
this function will be called whenever `readingChanged` signal is emmited. then it will read data from the sensor and append current accelerations to array of acceleraion's history. (we will need these acceleration during the `calibrationDuration` in order to calculate bias)
```cpp
void Accelerometer::onCalibrationFinished()
{
    sensor->stop();
    calibrationTimer->stop();
    disconnect(sensor, &QAccelerometer::readingChanged, this, &Accelerometer::onCalibrationReadingChanged);

    double x_sum = 0.0;
    double y_sum = 0.0;

    for (double x : x_values)
        x_sum += x;

    for (double y : y_values)
        y_sum += y;

    x_bias = x_sum / x_values.size();
    y_bias = y_sum / y_values.size();

    QString output = QStringLiteral("Calibration complete\tX bias: %1 Y bias: %2")
                         .arg(QString::number(x_bias, 'f', 1),
                              QString::number(y_bias, 'f', 1));
    qDebug() << "Biases: " + output;

    emit calibrationFinished(output);
}
```
this function will be called when the timer of the calibration is timeout. then we will stop the sensor from reading. and stop the timer as well(because we just want to calibrate single time). then disconnect `readingChanged` signal because henceforward we don't want to read data from sensor whenever new data is available instead we want to read data by time intervals and get samples priadically.<br/>
in this function we calculate bias by calculating the average of the velocities we have saved in history during the `calibrationDuration`. at the end, we specify the format of output which will be shown on the screen. then we emit `calibrationFinished` signal Indicates that calibration is complete and provides the calibration result. whenever this signal is emmited we will show the output on the screen of our application.

## Gyroscope class
The Gyroscope class in the provided code is designed to handle the operations of a gyroscope sensor within a Qt application. The class uses the `QGyroscope` sensor to read gyroscope data, applies Kalman filtering to the sensor data, performs calibration to determine sensor biases, and emits signals for use in the QML frontend.
### Constructor
```cpp
Gyroscope::Gyroscope(QObject *parent)
    : QObject(parent), z_bias(0.0), currentAngle(0.0), angleKalman(0.1, 1, 0.1, 0.0) // Initialize Kalman filter
{
    sensor = new QGyroscope(this);
    timer = new QTimer(this);
    calibrationTimer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Gyroscope::onSensorReadingChanged);
    connect(calibrationTimer, &QTimer::timeout, this, &Gyroscope::onCalibrationFinished);
}
```
here we initialize member variables, including bias, Kalman filter, and the angle.<br/>
note that we consider just one angle in z direction.<br/>
the reason that we have bias is that when we do calibration we check the base state of angle of the cellphone. and we name this initial state as bias and when we want to calculate new angle we should consider this bias as well. Kalman filter is for noise reduction. we will explain its algorithm later.<br/>
the angle will be updated after each time intervals. <br/>
then we make an instance of the available `QGyroscope` sensor object. <br/>
here like Accelormeter, we have two types of timers. One is for sampling intervals (timer) and the other (calibrationTimer) is for handling calibration. then we connect the timer signal to `onSensorReadingChanged` function. so whenever a timer reaches a specified time(we have specified the time intervals in this file in start method), and timeout occurs this function will be called. <br/>
also, we connect the `calibrationTimer` signal to  `onCalibrationFinished` function. so whenever this timer reaches a specified time(we have specified this time duration in calibration method), and timeout occurs, this function will be called. <br/>
the reason that we have `calibrationTimer` is that for calculating the initial bias we should get many samples from the sensors in one period of time and calculate the average. thus for indicating the duration of this period we need to set a `calibrationTimer`.

### Destructor
```cpp
Gyroscope::~Gyroscope()
{
    stop();
    delete sensor;
}
```
Ensures that the sensor is stopped and deleted when the Gyroscope object is destroyed to clean up resources properly.

### Start method and Stop method
```cpp
void Gyroscope::start()
{
    if (!sensor->isActive())
    {
        currentAngle = 0.0; // reset it
        sensor->start();
        timer->start(gyro_sampling_interval);
        emit activeChanged();
        qDebug() << "Gyroscope started.";
    }
}

void Gyroscope::stop()
{
    if (sensor->isActive())
    {
        sensor->stop();
        timer->stop();
        calibrationTimer->stop();
        emit activeChanged();
        qDebug() << "Gyroscope stopped.";
    }
}
```
- start: Starts the gyroscope sensor and a timer to periodically read sensor data. Emits the activeChanged signal and logs the action.
- stop: Stops the accelerometer sensor and the timers. Emits the `activeChanged` signal and logs the action.

### Calibration Methods
```cpp
void Gyroscope::calibration()
{
    sensor->start();
    z_values.clear();
    calibrationTimer->start(calibrationDuration);
    connect(sensor, &QGyroscope::readingChanged, this, &Gyroscope::onCalibrationReadingChanged);
}
```
calibration: Starts the sensor and prepares for calibration by clearing previous values and starting a timer for the calibration duration. from this time we connect `onCalibrationReadingChanged` function to the `readingChanged` signal. it says that for the calibration process we will manually emit reading data signal to read data form sensor in time intervals. instead, the `readingChanged` signal will be authomatically emited whenever a new data is available to read on sensor. 
```cpp
void Gyroscope::onCalibrationReadingChanged()
{
    QGyroscopeReading *reading = sensor->reading();
    if (reading)
    {
        z_values.append(reading->z());
    }
    else
    {
        qDebug() << "No reading available.";
    }
}
```
this function will be called whenever `readingChanged` signal is emited. then it will read data from the sensor and append current angular velocity to array of angular velociti's history. (we will need these angles during the `calibrationDuration` in order to calculate bias)
```cpp
void Gyroscope::onCalibrationFinished()
{
    sensor->stop();
    calibrationTimer->stop();
    disconnect(sensor, &QGyroscope::readingChanged, this, &Gyroscope::onCalibrationReadingChanged);

    double z_sum = 0.0;
    for (double z : z_values)
        z_sum += z;

    z_bias = z_sum / z_values.size();

    QString output = QStringLiteral("Calibration complete\tZ bias: %1")
                         .arg(QString::number(z_bias, 'f', 1));
    qDebug() << "Bias: " + output;

    emit calibrationFinished(output);
}
```
this function will be called when the timer of the calibration is timeout. then we will stop the sensor from reading. and stop the timer as well(because we just want to calibrate single time). then disconnect `readingChanged` signal because henceforward we don't want to read data from sensor whenever new data is available instead we want to read data by time intervals and get samples priadically.<br/>
in this function we calculate bias by calculating the average of the angular velocities we have saved in history during the `calibrationDuration`. at the end, we specify the format of output which will be shown on the screen. then we emit `calibrationFinished` signal indicates that calibration is complete and provides the calibration result. whenever this signal is emited we will show the output on the screen of our application.

### Sensor Reading Handling
```cpp
void Gyroscope::onSensorReadingChanged()
{
    QGyroscopeReading *reading = sensor->reading();
    if (reading)
    {
        double alpha = reading->z();

        // Apply Kalman filter
        alpha = angleKalman.update(alpha);

        // Adjust for bias
        alpha -= z_bias;

        // Apply threshold
        if (std::abs(alpha) < gyro_threshold)
            alpha = 0.0;

        double angleChange = alpha * 0.01;
        currentAngle += angleChange;


        if (currentAngle >= 360.0) currentAngle -= 360.0;
        if (currentAngle < 0.0) currentAngle += 360.0;

        // Normalize the angle change
        double normalizedAngle = 0.0;
        if (currentAngle >= 60.0 && currentAngle < 135.0) {
            normalizedAngle = 90.0;
        } else if (currentAngle >= 135.0 && currentAngle < 225.0) {
            normalizedAngle = 180.0;
        } else if (currentAngle >= 225.0 && currentAngle < 315.0) {
            normalizedAngle = -90.0;
        } else {
            normalizedAngle = 0.0;
        }

        QString output = QStringLiteral("Alpha: %1").arg(QString::number(normalizedAngle, 'f', 2));

        emit readingUpdated(output);
        emit newRotation(normalizedAngle);

    }
    else
    {
        qDebug() << "No reading available.";
    }
}
```
this function will be called after each time interval, first, we read the data from the gyroscope sensor. if there is data to read we do the following steps otherwise we log the appropriate message indicating that we have no data to read. then we extract the angular velocity in z direction from the read data. and update it by applying the Kalman algorithm for noise reduction. <br/>
then we apply bias. and then check if our current angular velocity is less than a threshold or not.
we have a threshold for angular velocity and whenever we are less than that threshold we consider the velocity as zero. the reason is that to set small values to zero to handle sensor noise. we've determined this threshold variable by trial and error. </br>
```cpp
        double angleChange = alpha * 0.01;
        currentAngle += angleChange;
```
here we update our angular velocity. To do this, we multiply the current angular velocity by time intervals to reach delta v. Then we add it to previous angular velocity.

```cpp
        if (currentAngle >= 360.0) currentAngle -= 360.0;
        if (currentAngle < 0.0) currentAngle += 360.0;

        // Normalize the angle change
        double normalizedAngle = 0.0;
        if (currentAngle >= 60.0 && currentAngle < 135.0) {
            normalizedAngle = 90.0;
        } else if (currentAngle >= 135.0 && currentAngle < 225.0) {
            normalizedAngle = 180.0;
        } else if (currentAngle >= 225.0 && currentAngle < 315.0) {
            normalizedAngle = -90.0;
        } else {
            normalizedAngle = 0.0;
        }
```
here we normalize the angel. our valid angels are 0, 90, 180, -90. so we try to normalize the angle to reach these valid angels.
```cpp
        QString output = QStringLiteral("Alpha: %1").arg(QString::number(normalizedAngle, 'f', 2));

        emit readingUpdated(output);
        emit newRotation(normalizedAngle);
```
here we can see the format of the output that will be shown on the screen of our application which shows the angle.
at the end, we emit signals with the updated values for use in the QML frontend.
we will disscuss these signals later. but briefly `newRotation` signal will handle our movements (check if we have finished one movement or not yet in order to add it to our movement database). the connection of this signal can be seen in .QML file. <br/>
`readingUpdated` signal is emited to handle what should be shown on the screen. 

### Reset Method
```cpp
void Gyroscope::reset()
{
    //z_bias = 0.0;
    currentAngle = 0.0;
    //angleKalman.reset(0.0);
    qDebug() << "Gyroscope reset.";
}
```
reset: Resets the current angle to 0 and logs the action.
