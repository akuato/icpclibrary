sy on
se nu bs=2 cin sta ts=4 sw=4 et ic scs hls is cb=unnamed
let g:loaded_matchparen=1
ino ( ()<Left>
ino { {}<Left>
ino [ []<Left>
ino <expr> ) getline('.')[col('.')-1]==')'?'<Right>':')'
ino <expr> } getline('.')[col('.')-1]=='}'?'<Right>':'}'
ino <expr> ] getline('.')[col('.')-1]==']'?'<Right>':']'
nn <Space> :noh<CR>