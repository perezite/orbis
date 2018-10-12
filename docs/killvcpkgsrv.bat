@echo off
:loop
timeout 5
taskkill /im vcpkgsrv.exe /f
goto loop