@echo off
setlocal

set "old_extension=.js"
set "new_extension=.txt"
set "folder=C:\KPO\alt\SE_Lab14\lab14\"

pushd "%folder%"
for %%f in (*%old_extension%) do (
    ren "%%f" "%%~nf%new_extension%"
)
popd

endlocal