cmake_minimum_required(VERSION 3.14)

project(QtQuickProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Sensors)

qt_standard_project_setup()

qt_add_executable(QtQuickProject
    main.cpp
    accelerometer.cpp
    accelerometer.h
)

qt_add_qml_module(QtQuickProject
    URI com.example
    VERSION 1.0
    QML_FILES main.qml
)

target_link_libraries(QtQuickProject PRIVATE Qt6::Quick Qt6::Sensors)
