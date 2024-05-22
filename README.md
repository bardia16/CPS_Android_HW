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
  
- **.qml file:** This file defines an application window with a UI to display sensor data, handle calibration, and manage motion-based authentication. It includes UI elements like labels, text areas, and buttons for user interaction. and also includes some logic to handle accelerometer and gyroscope data, including updates and calibration and the functions to update the UI and manage the state of the application based on sensor readings.

- **.cpp and .h:** These files are the source files written by C++ and .h files are their corresponding header files.
