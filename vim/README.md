# Setting up neovim
For latest version of nvim, run  
`curl -LO https://github.com/neovim/neovim/releases/tag/stable/nvim.appimage`  
1. `sudo apt install libfuse2`
2. `mkdir -p /opt/nvim/`
3. `mv nvim.appimage /opt/nvim/nvim`
4. `cp init.lua init.vim ~/.config/nvim/`
5. `vi`
6. `:MarkdownPreview`
7. If any error, run `:call mkdp#util#install()`

