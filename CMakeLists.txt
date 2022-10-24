cmake_minimum_required(VERSION 3.5)

project(CW_Vorobyova VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        masters_add_window.h masters_add_window.cpp masters_add_window.ui
        masters_remove_window.h masters_remove_window.cpp masters_remove_window.ui
        records_add_window.h records_add_window.cpp records_add_window.ui
        records_remove_window.h records_remove_window.cpp records_remove_window.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CW_Vorobyova
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CW_Vorobyova APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CW_Vorobyova SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CW_Vorobyova
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CW_Vorobyova PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


########## Моя писанина
add_library(HTLib Hashtable.cpp)
add_library(AVLLib AVL.cpp)
add_library(ParserLib Parser.cpp)

add_library(StructuresLib Structures.cpp)
add_library(ToStringLib ToString.cpp)
target_link_libraries(ToStringLib PUBLIC StructuresLib)

add_library(mastersLib Masters.cpp)
target_link_libraries(mastersLib PUBLIC HTLib AVLLib ParserLib ToStringLib)
add_library(recordsLib Records.cpp)
target_link_libraries(recordsLib PUBLIC HTLib AVLLib ParserLib ToStringLib)

add_library(databaseLib Database.cpp)
target_link_libraries(databaseLib PUBLIC mastersLib recordsLib)

target_link_libraries(CW_Vorobyova PUBLIC databaseLib)
########## Конец моей писанины

set_target_properties(CW_Vorobyova PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CW_Vorobyova)
endif()
