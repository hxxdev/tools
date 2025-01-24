# tools
## Version Table
| Tool Name     | Version       |
| ------------- |:-------------:|
| CheatEngine   | 7.5           |
| HexEdit       | 2.5.0.0       |
| IDM           | 6.42          |
| Windows10     | -             |
| MSYS2         | 20241208      |
| Visual Studio | 2022 Community|
| VSCode        | -             |
| Git           | 2.47.1        |
| VS WDK        | 10.0.26100    |

## MSYS2 Configuration
### VIM Installation
you can install vim by `pacman -S vim`  
### Changing Home Directory
edit the following file : `/C/msys64/etc/nsswitch.conf/`  
`db_home: windows`  
put .bashrc in your windows home directory  
### Inheriting Windows environment variable to MSYS2
Open `/C/msys64/mingw64.ini`  
Write `MSYS2_PATH_TYPE=inherit`
### Install Git
1. Install git in Windows from `git-scm.com`  
2. Add these directories into environment variable PATH.  
`C:\Program Files\Git\mingw64\bin`  
`C:\Program Files\Git\cmd`  
3. Test git commands `git-gui`, `gitk`, `git pull`... etc.
