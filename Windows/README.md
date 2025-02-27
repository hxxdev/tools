### Setting up your Windows
- [How to disable Onedrive](https://support.microsoft.com/en-us/office/turn-off-disable-or-uninstall-onedrive-f32a17ce-3336-40fe-9c38-6efb09f944b0)

- How to logout Microsoft account from Windows
1. 설정
2. 계정
3. 사용자 정보
4. 계정 설정
5. 대신 로컬 계정으로 로그인합니다.

- Enabling administartor account
`net user Administrator /active:yes`

- Changing User folder name
1. Enable administrator account
2. Login to administrator account
3. `powershell "Get-LocalUser | Select-Object -Property @('Name', 'SID')"​`
Open Registry Editor (regedit.exe).
Navigate to `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\ProfileList\<SID>`
Change `ProfileImagePath` to C:\Users\<username you want>
4. Change user folder name
Run cmd in administrator mode
run mklink /d "C:\Users\<old username>" "C:\Users\<new username>"

- Disabling Windows Update
1. run `disable updates.bat`
2. To enable again, run `enable updates.bat`
