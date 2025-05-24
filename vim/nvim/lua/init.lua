-- Neovide
if vim.g.neovide then
    -- Put anything you want to happen only in Neovide here
end

-- Package.path = package.path .. ";" .. vim.fn.expand("$HOME") .. "/.luarocks/share/lua/5.1/?/init.lua;"
-- Package.path = package.path .. ";" .. vim.fn.expand("$HOME") .. "/.luarocks/share/lua/5.1/?.lua;"
vim.opt.tags = '.tags'
package.path = package.path .. ";/home/hxxdev/dev/tools/vim/nvim/lua/config/?.lua"
require("notify")
require("noice")
require("treesitter")
require("nvim-tree")
require("lualine")
-- require("config.image")
