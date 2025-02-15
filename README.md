# tools
## Version Table            
| Tool Name                 | Version       |
| -------------             |:-------------:|
| CheatEngine               | 7.5           |
| x64dbg                    | 25.01.17      |
| HexEdit                   | 2.5.0.0       |
| IDM                       | 6.42          |
| Windows10                 | -             |
| MSYS2                     | 20241208      |
| Visual Studio             | 2022 Community|
| VSCode                    | -             |
| Git                       | 2.47.1        |
| VS WDK                    | 10.0.26100    |
| VmwareHardenedLoader      | -             |

## MSYS2 Configuration
### .bashrc
Copy /tools/msys2/.bashrc into your Windows home directory.  
Copy c/msys64/home/user/.bash_profile into your Windows home directory.  
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
### Modify env.sh
modify env.sh file to your needs.
env.sh is placed at /msys2/.
apply script by `source env.sh`.

## Visual Studio Configuration
### PropertySheet
1. View - Other Windows - Property Manager  
2. Right click on your project.  
3. Add Existing Property Sheet  
4. Select /tools/vs/PropertySheet.pros
### Include directories
1. Right click on project.  
2. Properties - VC++ Directories - Include Directories - Inlcude Directories  
3. Add /tools/hacklib/ into the directory list.  
### When working with DLL
1. Right click on project.  
2. Properties - General - Configuration Type  
3. set it to Dynamic Library(.dll)   

## x64dbg
### Language
Options - Languages - en_US  
### Disable TLS Callback
Options - Preferences - disable User TLS Callbacks and System TLS Callbacks 
### Import Settings
Options - Import Settings - Load x64dbg.ini/x32dbg.ini  
