@echo off

pushd ..
Vendor\bin\premake5.exe --file=Build.lua vs2022
popd
pause