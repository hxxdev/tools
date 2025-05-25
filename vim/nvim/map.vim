nnoremap <C-m> <Plug>MarkdownPreview
nnoremap <C-e> :NvimTreeOpen<CR>

cnoreabbrev open NvimTreeOpen

" Clipboard yank and delete mappings
" ----------------------------

" NORMAL MODE
nnoremap y "+y
nnoremap yy "+yy
nnoremap d "+d
nnoremap dd "+dd
nnoremap c "+c
nnoremap cc "+cc
nnoremap C "+C

" VISUAL MODE
vnoremap y "+y
vnoremap d "+d
vnoremap c "+c

" OPERATOR-PENDING MODE
" This covers things like `yaw`, `dap`, etc.
" Remap the operators themselves
nnoremap <silent> y "+y
nnoremap <silent> d "+d
nnoremap <silent> c "+c
