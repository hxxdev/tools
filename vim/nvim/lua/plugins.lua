return {
    {   dir = "~/.config/nvim/lua/plugins/markdown-preview.nvim",
        cmd = { "MarkdownPreviewToggle", "MarkdownPreview", "MarkdownPreviewStop" },
        ft = { "markdown" },
        build = function()
        require("lazy").load({ plugins = { "markdown-preview.nvim" } })
        vim.fn["mkdp#util#install"]() end,
    },
    {   dir = "~/.config/nvim/lua/plugins/noice.nvim",
        event = "VeryLazy",
        opts = {},
        dependencies = {
        	{dir = "~/.config/nvim/lua/plugins/nui.nvim"},
        
        	{dir = "~/.config/nvim/lua/plugins/nvim-notify"},
        }  
    },
    {   dir = "~/.config/nvim/lua/plugins/image.nvim",
        build = false,
        opts = {}
    },
}
