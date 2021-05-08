cmake_minimum_required(VERSION 3.5)

project(ScheduleMaker LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui
        model/Teacher.h
        model/Schedule.cpp
        model/Schedule.h
        model/ScheduleXLSXConverter.cpp
        model/ScheduleXLSXConverter.h)

set(CMAKE_AUTORCC YES)
add_executable(ScheduleMaker ${PROJECT_SOURCES})
include_directories(SYSTEM lib)
target_link_libraries(ScheduleMaker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets "${CMAKE_CURRENT_SOURCE_DIR}/lib/libOpenXLSX-sharedd.dll")

set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)
install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION programs
        COMPONENT applications)

set(CPACK_PACKAGE_NAME "ScheduleMakerInstaller")
set(CPACK_PACKAGE_VENDOR "Masha Ushakova")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ScheduleMaker")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "ScheduleMakerInstallDir")

include(CPack)