cmake_minimum_required(VERSION 3.14)

project(QtQuickProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Sensors)

qt_standard_project_setup()

qt_add_executable(appQtQuickProject
    main.cpp
)

qt_add_qml_module(appQtQuickProject
    URI QtQuickProject
    VERSION 1.0
    SOURCES accelerometer.h accelerometer.cpp
    QML_FILES Main.qml
    SOURCES movement.h movement.cpp
    SOURCES movementdatabase.h movementdatabase.cpp
    SOURCES
    SOURCES
    SOURCES
    SOURCES gyroscope.h
    SOURCES gyroscope.cpp
    SOURCES patterndatabase.h patterndatabase.cpp
    SOURCES pattern.h pattern.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQtQuickProject PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQtQuickProject
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQtQuickProject PRIVATE Qt6::Quick Qt6::Sensors)

include(GNUInstallDirs)
install(TARGETS appQtQuickProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

