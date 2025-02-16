#!/bin/bash
export PATH_VSCODE="$PATH_WIN/Users/g1004/AppData/Local/Programs/Microsoft VS Code"
export PATH_VS="$PATH_WIN/Program Files/Microsoft Visual Studio/2022/Community"

alias vscode="\"$PATH_VSCODE\"/Code.exe"
# alias cl32="\"$PATH_VS\"/Common7/Tools/VsDevCmd.bat"
alias vs="\"$PATH_VS\"/Common7/IDE/devenv.exe &"


echo "DEV ENV SETUP ********************************************"
echo "VSCODE            : "$PATH_VSCODE	""
echo "VS                : "$PATH_VS     ""
echo "**********************************************************"
echo "HOTKEYS **************************************************"
echo "vscode            : run Visual Studio Code"
echo "vs                : run Visual Studio"
echo "**********************************************************"
