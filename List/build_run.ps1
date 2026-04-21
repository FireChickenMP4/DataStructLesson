$ErrorActionPreference = "Stop"

cl /Wall /nologo /EHsc /std:c++20 /utf-8 main.cpp /Fe:linear_test.exe
if ($LASTEXITCODE -eq 0) {
    .\linear_test.exe
}
