cmake_minimum_required(VERSION 3.5)

project(QT-Latex-Editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QT-Latex-Editor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(QT-Latex-Editor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(QT-Latex-Editor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QT-Latex-Editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)