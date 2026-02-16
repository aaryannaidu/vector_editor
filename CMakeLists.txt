cmake_minimum_required(VERSION 3.15)

project(MicroVectorEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
add_executable(editor
    src/main.cpp
    src/model/Circle.cpp
    src/model/Rectangle.cpp
    src/model/Diagram.cpp
    src/model/Line.cpp
    src/model/Hexagon.cpp
    src/model/Text.cpp
    src/model/FreeHand.cpp
    src/model/RoundedRectangle.cpp
    src/svg/SVGwriter.cpp
    src/svg/SVGparser.cpp
    src/gui/Canvas.cpp
    src/gui/Canvasdrawing.cpp
    src/gui/Canvasmouse.cpp
    src/gui/MainWindowcore.cpp
    src/gui/MainWindowconnection.cpp
    include/gui/Canvas.h
    include/gui/MainWindow.h
    src/svg/SVGparser2.o.cpp
    include/svg/SVGparser2.o.h
)

target_include_directories(editor
    PRIVATE include
)
target_link_libraries(editor PRIVATE Qt6::Widgets)