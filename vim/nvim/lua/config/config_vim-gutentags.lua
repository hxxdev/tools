-- Function to get Git project name or fallback to cwd name
local function get_git_project_name()
  local handle = io.popen("git rev-parse --show-toplevel 2>/dev/null")
  if handle then
    local result = handle:read("*l")
    handle:close()
    if result and result ~= "" then
      return vim.fn.fnamemodify(result, ":t")
    end
  end
  return vim.fn.fnamemodify(vim.fn.getcwd(), ":t")
end

local home = vim.fn.expand("~")
local tags_dir = home .. "/tags"
local project_name = get_git_project_name()
local tagfile_path = tags_dir .. "/" .. project_name

-- Use Neovim's luv (libuv) to check and create directory safely
local uv = vim.loop
local function ensure_dir(path)
  local stat = uv.fs_stat(path)
  if not stat then
    vim.fn.mkdir(path, "p")
  end
end

ensure_dir(tags_dir)
ensure_dir(tagfile_path)

-- Gutentags configuration
vim.g.gutentags_enabled = 1
vim.g.gutentags_modules = { 'ctags' }
vim.g.gutentags_cache_dir = tags_dir
vim.g.gutentags_ctags_tagfile = tagfile_path .. "/tags"

vim.g.gutentags_file_list_command = {
  ['default'] = 'find . -type f \\( -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.v" -o -name "*.sv" -o -name "*.lua" -o -name "*.vim" \\)'
}

vim.opt.tags:prepend(tagfile_path)

vim.g.gutentags_ctags_extra_args = {
  '--tag-relative=no',
  '--fields=+l',
}
