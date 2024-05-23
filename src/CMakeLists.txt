file(GLOB_RECURSE DIR_LIB_SRCS "*.cpp" "*.h" "*.ui" ".qrc" "*.hpp" )
list(APPEND DIR_LIB_SRCS ../application.qrc)
install(FILES dark_red.qss DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${DIR_LIB_SRCS})
# # 将theme目录安装到构建目录
message(${CMAKE_CURRENT_BINARY_DIR})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/theme DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network  Qt${QT_VERSION_MAJOR}::Pdf Qt6::PdfWidgets ${KF6DEP})
qt_finalize_executable(${PROJECT_NAME})
