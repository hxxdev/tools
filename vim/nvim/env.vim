set number
set relativenumber
set history=1000
set mouse=a
set autoread
set ruler
set hlsearch
set incsearch
set showmatch
set encoding=utf-8
set fileencodings=utf-8,cp949
set shiftwidth=4
set expandtab
set tabstop=4
" let g:clipboard = {
"     \   'name': 'WslClipboard',
"     \   'copy': {
"     \      '+': 'clip.exe',
"     \      '*': 'clip.exe',
"     \    },
"     \   'paste': {
"     \      '+': 'powershell.exe -NoLogo -NoProfile -c [Console]::Out.Write($(Get-Clipboard -Raw).tostring().replace("`r", ""))',
"     \      '*': 'powershell.exe -NoLogo -NoProfile -c [Console]::Out.Write($(Get-Clipboard -Raw).tostring().replace("`r", ""))',
"     \   },
"     \   'cache_enabled': 0,
"     \ }
" set clipboard+=unnamedplus
" clipboard settings
" let g:clipboard = {
"     \   'name': 'win32yank-wsl',
"     \   'copy': {
"     \      '+': '/mnt/c/win32yank.exe -i --crlf',
"     \      '*': '/mnt/c/win32yank.exe -i --crlf',
"     \    },
"     \   'paste': {
"     \      '+': '/mnt/c/win32yank.exe -o --lf',
"     \      '*': '/mnt/c/win32yank.exe -o --lf',
"     \   },
"     \   'cache_enabled': 0,
"     \ }
