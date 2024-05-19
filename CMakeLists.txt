cmake_minimum_required(VERSION 3.29)

project(KDTEX VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QSCINTILLA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/Qsci")
set(QSCINTILLA_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/lib/libqscintilla2_qt6.a")
# message(CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${QSCINTILLA_INCLUDE_DIR})
find_package(KF6SyntaxHighlighting)

# find_package(KF6 ${KF5_DEP_VERSION}
#     REQUIRED COMPONENTS
#         I18n
#         CoreAddons
#         GuiAddons
#         Crash
#         IconThemes
#         TextEditor
#     OPTIONAL_COMPONENTS
#         DocTools
# )

find_package(QT NAMES Qt6 COMPONENTS Widgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)
message("Qt version: ${Qt6Core_VERSION}")

add_subdirectory(src)