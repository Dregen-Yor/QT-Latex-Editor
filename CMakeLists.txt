cmake_minimum_required(VERSION 3.29)

project(KFTEX VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QSCINTILLA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/Qsci")
set(QSCINTILLA_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/lib/libqscintilla2_qt6.a")
# message(CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR})
set(KF5_DEP_VERSION "6.0.0")
# We need some parts of the ECM CMake helpers.
find_package(ECM ${KF5_DEP_VERSION} QUIET REQUIRED NO_MODULE)

find_package(glog REQUIRED)
# We append to the module path so modules can be overridden from the command line.
list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
find_package(KF6 ${KF5_DEP_VERSION}
    REQUIRED COMPONENTS
        I18n
        CoreAddons
        GuiAddons
        Crash
        IconThemes
        TextEditor
    OPTIONAL_COMPONENTS
        DocTools
)
set(KF6DEP KF6::I18n KF6::CoreAddons KF6::GuiAddons KF6::Crash KF6::IconThemes KF6::TextEditor)
find_package(QT NAMES Qt6 COMPONENTS Widgets Network Pdf PdfWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Pdf PdfWidgets REQUIRED)
message("Qt version: ${Qt6Core_VERSION}")

add_subdirectory(src)