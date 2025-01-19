# tools
## Version Table
| Tool Name     | Version       |
| ------------- |:-------------:|
| CheatEngine   | 7.5           |
| HexEdit       | 2.5.0.0       |
| IDM           | 6.42          |
| Windows10     | -             |
| MSYS2         | 20241208      |

## MSYS2 Configuration
### Changing Home Directory
edit the following file : /C/msys64/etc/nsswitch.conf/
`db_home: windows`
put .bashrc in your windows home directory
### Install vim
`pacman -S vim`
### Installing Git
1. Install wish.exe in /C/msys64/mingw64/bin/
`pacman -S mingw-w64-x86_64-tk`
2. Install git in /C/msys64/bin/
`pacman -S git`
