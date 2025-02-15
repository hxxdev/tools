#!/bin/bash
export PATH_HOME="~/dev"
export PATH_CE="/c/Program Files/Cheat Engine 7.5/"
export PATH_DBG="/c/dbg/"
export PATH_VSCODE="/c/Users/g1004/AppData/Local/Programs/Microsoft VS Code/"
export PATH_NASM="~/dev/toolstools/assembly/nasm-2.14.02"

alias ce='$PATH_CE/Cheat\ Engine.exe &'
alias dbg32='$PATH_DBG/release/x32/x32dbg &'
alias dbg64='$PATH_DBG/release/x64/x64dbg &'
alias vscode='$PATH_VSCODE/Code.exe &'
alias nasm='$PATH_HOME/tools/assembly/nasm-2.14.02'

echo "ENV VARIABLES ****************************"
echo "HOME PATH         : $PATH_HOME	"
echo "CHEAT ENGINE      : $PATH_CE	"
echo "DEBUGGER          : $PATH_DBG	"
echo "VSCODE            : $PATH_VSCODE	"
echo "NASM              : $PATH_NASM	"
echo "******************************************"
echo "HOTKEYS **********************************"
echo "ce                : run Cheat Engine 7.5"
echo "dbg32             : run x32 debugger"
echo "dbg64             : run x64 debugger"
echo "vscode            : run Visual Studio Code"
echo "nasm              : run Netwide Assembler"
echo "******************************************"
