-- Neovide
if vim.g.neovide then
    -- Put anything you want to happen only in Neovide here
end

-- Package.path = package.path .. ";" .. vim.fn.expand("$HOME") .. "/.luarocks/share/lua/5.1/?/init.lua;"
-- Package.path = package.path .. ";" .. vim.fn.expand("$HOME") .. "/.luarocks/share/lua/5.1/?.lua;"
vim.opt.tags = '.tags'
require("config.notify")
-- require("config.image")
require("config.noice")
require("config.treesitter")
require("config.nvim-tree")
require("config.lualine")
