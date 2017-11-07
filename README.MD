# Injector
### Simple injector used to inject DLL's into currently running processes.

## Compiling:

Get the [wxWidgets libraries](http://wxwidgets.org/) and [CMake](https://cmake.org/). Then navigate to the main directory and perform the following:

mkdir build

cd build

cmake ..

This will produce a solution or .sln. Use this file to compile the injector.

You will have to tell CMake the root directory for the wxWidgets libraries and includes.

## Usage:

![main_panel](https://user-images.githubusercontent.com/13967957/32491855-1350c6de-c36d-11e7-8ac6-9cb474dd8604.PNG)

Use the top slot to browse to the dll that should be injected and select the executable you would like to inject in the bottom slot. Simply hit inject and the program will attempt to inject the dll. Save config saves the exe name and path, and load checks for a config file containing the exe name and path.