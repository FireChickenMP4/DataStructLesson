@echo off
cl /Wall /nologo /EHsc /std:c++17 /utf-8 main.cpp /Fe:stack_test.exe
if %ERRORLEVEL% EQU 0 (
	.\stack_test.exe
)