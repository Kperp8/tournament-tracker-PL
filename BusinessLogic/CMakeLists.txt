cmake_minimum_required(VERSION 3.16)

project(BusinessLogic LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(BusinessLogic SHARED
  BusinessLogic_global.h
  teams.cpp
  teams.h
  teamsmodel.h
  teamsmodel.cpp
  file-handling.cpp
  file-handling.h
  extended-teams.h
  extended-teams.cpp
  match-specify.h
)

target_link_libraries(BusinessLogic PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(BusinessLogic PRIVATE BUSINESSLOGIC_LIBRARY)
