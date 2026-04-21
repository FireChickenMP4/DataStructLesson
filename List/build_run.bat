@echo off
cl /Wall /nologo /EHsc /std:c++20 /utf-8 main.cpp /Fe:linear_test.exe
if %ERRORLEVEL% EQU 0 (
	.\linear_test.exe
)