Simple injector used to inject DLL's into currently running processes.

Compiling:

Open solution and change the include directory to standard wxWidgets includes, and the msvc include as well. Preprocessor commands should already be present in the solution. Link to the appropriate libraries and make sure to include the appropriate library directories as well. Make sure the configurations are set to build Win32 or x86. X64 builds are not set up.

More information on the how to set up a solution with wxWidgets here: https://wiki.wxwidgets.org/Microsoft_Visual_C%2B%2B_Guide

Usage:

Use the top slot to browse to the dll that should be injected and type the name of the exe into the next textbox. Simply hit inject and the program will attempt to inject the dll. Save config saves the exe name and path, and load checks for a config file containing the exe name and path