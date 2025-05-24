local lspconfig = require("lspconfig")
lspconfig.pyright.setup {}
lspconfig.clangd.setup {}
lspconfig.svlangserver.setup {
  cmd = { "svlangserver" },
  filetypes = { "verilog", "systemverilog" },
  root_dir = lspconfig.util.root_pattern("*.v", "*.sv"),
}
