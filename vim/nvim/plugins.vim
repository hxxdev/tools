call plug#begin()

" List your plugins here
" Plug 'image.nvim', { 'dir': '~/dev/tools/vim/nvim/plugins' }
" Plug '~/dev/tools/vim/nvim/plugins/markdown-preview.nvim', { 'do': { -> mkdp#util#install() },
     \                                             'for': ['markdown', 'vim-plug'] }
Plug '~/dev/tools/vim/nvim/plugins/markdown-preview.nvim', { 'do': 'cd app && npx --yes yarn install' }
Plug '~/dev/tools/vim/nvim/plugins/image.nvim'
Plug '~/dev/tools/vim/nvim/plugins/nui.nvim'
Plug '~/dev/tools/vim/nvim/plugins/noice.nvim'
Plug '~/dev/tools/vim/nvim/plugins/nvim-notify'
Plug '~/dev/tools/vim/nvim/plugins/nvim-treesitter'
Plug '~/dev/tools/vim/nvim/plugins/nvim-tree.lua'
Plug '~/dev/tools/vim/nvim/plugins/nvim-web-devicons'
Plug '~/dev/tools/vim/nvim/plugins/vim-gutentags'
" Plug '~/dev/tools/vim/nvim/plugins/lightline.vim'
Plug '~/dev/tools/vim/nvim/plugins/lualine.nvim'
Plug '~/dev/tools/vim/nvim/plugins/nvim-lspconfig'
Plug '~/dev/tools/vim/nvim/plugins/mason.nvim'
Plug '~/dev/tools/vim/nvim/colorschemes/challenger-deep', { 'as': 'challenger-deep' }
Plug '~/dev/LazyVerilog', { 'as': 'lazy_verilog' }

call plug#end()
