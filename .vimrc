set path+=src/**10              " For 'gf', looks in current folder, and up to 10 level of sub-sub-folders
set hidden                      " For 'gf', let's you go to next file without requiring to save current.                 
set cindent shiftwidth=4        " In C/C++, size of the tabulation increase each time you have a {
set tabstop=4                   " In all files, size of the Tab
set expandtab                   " Use spaces instead of Tab
autocmd vimenter * NERDTreeVCS  " Automatically opens NERDTree
