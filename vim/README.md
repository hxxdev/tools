# Setting up neovim
For latest version of nvim, run  
`curl -LO https://github.com/neovim/neovim/releases/tag/stable/nvim.appimage`  
1. `mkdir -p /opt/nvim/`
2. `mv nvim.appimage /opt/nvim/nvim`
3. `cp init.lua init.vim ~/.config/nvim/`
4. `vi`
5. `:MarkdownPreview`
6. If any error, run `:call mkdp#util#install()`

