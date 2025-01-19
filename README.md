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
## MSYS2 Configuration
### Changing Home Directory
edit the following file : `/C/msys64/etc/nsswitch.conf/`  
`db_home: windows`  
put .bashrc in your windows home directory  

### Install vim
you can install vim by `pacman -S vim`  

### Install Git
#### Installing Git
Install git in msys by  
`pacman -S git`  
#### Git-Gui
1. Install wish.exe in minw64 by  
`pacman -S mingw-w64-x86_64-tk`  
2. Run Mingw64
3. Run git gui by `git-gui &`
#### Credential Manager
1. Install git in Windows from `git-scm.com`
2. Copy `C/Program Files/Git/mingw64/bin` into `C/msys64/mingw64/bin`
3. `git credential-manager` should work.
