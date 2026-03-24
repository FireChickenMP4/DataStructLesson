$ErrorActionPreference = "Stop"

cl /Wall /nologo /EHsc /std:c++17 /utf-8 main.cpp SeqList.cpp LinkedList.cpp /Fe:linear_test.exe
if ($LASTEXITCODE -eq 0) {
    .\linear_test.exe
}
