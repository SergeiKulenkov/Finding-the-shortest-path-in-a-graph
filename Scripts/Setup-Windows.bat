@echo off

pushd ..
Scripts\premake5.exe --file=Build.lua vs2022
popd
pause