1. Run `Windows Powershell` in administrator mode
2. `Set-ExecutionPolicy Unrestricted`
3. `New_Item -ItemType File -Path $Profile -Force`
4. `notepad $PROFILE`
5. Write `. "the path to profile.ps1"`