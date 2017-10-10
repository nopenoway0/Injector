Simple injector used to inject DLL's into currently running processes.

Compiling:

install wxWidgets then perform the following

mkdir build
cd build
cmake ..
then make produced solution with msbuild Injector.sln or open with Visual Studio and compile

More information on the how to set up a solution with wxWidgets here: https://wiki.wxwidgets.org/Microsoft_Visual_C%2B%2B_Guide

Usage:

Use the top slot to browse to the dll that should be injected and type the name of the exe into the next textbox. Simply hit inject and the program will attempt to inject the dll. Save config saves the exe name and path, and load checks for a config file containing the exe name and path