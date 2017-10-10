cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Injector VERSION 0.0.6)

find_package(wxWidgets)
include_directories(./Header)
include_directories(${wxWidgets_INCLUDE_DIRS})
include(${wxWidgets_USE_FILE})
add_executable(
	Injector WIN32
	Source/Injector.cpp
	Source/Menu.cpp
	Source/MiscFunc.cpp
	)

target_link_libraries(Injector ${wxWidgets_LIBRARIES})