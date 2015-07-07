pushd %~dp0
echo off
if not exist boards.txt goto notfound
find /c "aistin.name=Aistin CPU 2" boards.txt
if %errorlevel% equ 1 goto addboard
echo Aistin board already found
goto done
:addboard
if not exist aistinboard.txt goto notfound
type aistinboard.txt >> boards.txt
if %errorlevel% equ 1 goto requireadmin
echo Aistin board succesfully added
goto done
:notfound
echo boards.txt or aistinboard.txt not found, are you sure you are in the right folder
goto done
:requireadmin
echo Admin privileges required, please run script as administrator
goto done
:done
pause