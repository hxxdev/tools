call plug#begin()

" List your plugins here
" Plug 'image.nvim', { 'dir': '~/.config/nvim/plugins' }
" Plug '~/.config/nvim/plugins/markdown-preview.nvim', { 'do': { -> mkdp#util#install() },
     \                                             'for': ['markdown', 'vim-plug'] }
Plug '~/.config/nvim/plugins/markdown-preview.nvim', { 'do': 'cd app && npx --yes yarn install' }
Plug '~/.config/nvim/plugins/nui'
Plug '~/.config/nvim/plugins/noice'
Plug '~/.config/nvim/plugins/notify'
Plug '~/.config/nvim/plugins/treesitter'
Plug '~/.config/nvim/plugins/nvim-tree.lua'
Plug 'nvim-tree/nvim-web-devicons'
Plug '~/.config/nvim/plugins/vim-gutentags'
" Plug '~/.config/nvim/plugins/lightline.vim'
Plug '~/.config/nvim/plugins/lualine.nvim'
Plug '~/.config/nvim/colorschemes/challenger-deep', { 'as': 'challenger-deep' }
call plug#end()
