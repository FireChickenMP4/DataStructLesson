@echo off
cl /nologo /EHsc /std:c++17 /utf-8 main.cpp SeqList.cpp LinkedList.cpp /Fe:linear_test.exe
if %ERRORLEVEL% EQU 0 (
	.\linear_test.exe
)