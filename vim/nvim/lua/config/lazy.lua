-- Bootstrap lazy.nvim
local lazypath = vim.fn.expand("~/.config/nvim/lua/plugins/lazy.nvim")
if not (vim.uv or vim.loop).fs_stat(lazypath) then
    vim.api.nvim_echo({
        { "Lazy not found..." },
    }, true, {})
    os.exit(1)
end
vim.opt.rtp:prepend(lazypath)

-- Make sure to setup `mapleader` and `maplocalleader` before
-- loading lazy.nvim so that mappings are correct.
-- This is also a good place to setup other settings (vim.opt)
vim.g.mapleader = " "
vim.g.maplocalleader = "\\"

require("lazy").setup({{import = "plugins"}})
