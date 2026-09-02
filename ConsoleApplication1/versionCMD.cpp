#include <windows.h>
#include <cstdio>
#include <iostream>
#include <string>

namespace {
std::wstring executableDirectory() {
    wchar_t buffer[MAX_PATH] = {};
    const DWORD length = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    if (length == 0 || length >= MAX_PATH) {
        return L"";
    }

    std::wstring path(buffer, length);
    const size_t separator = path.find_last_of(L"\\/");
    return separator == std::wstring::npos ? L"" : path.substr(0, separator);
}

std::wstring readVersion() {
    std::wstring path = executableDirectory();
    if (!path.empty()) {
        path += L"\\version.txt";
    } else {
        path = L"version.txt";
    }

    FILE* file = nullptr;
    if (_wfopen_s(&file, path.c_str(), L"rb") != 0 || file == nullptr) {
        return L"v1.0.2";
    }

    char buffer[64] = {};
    const size_t count = fread(buffer, 1, sizeof(buffer) - 1, file);
    fclose(file);

    std::string value(buffer, count);
    while (!value.empty() && (value.back() == '\n' || value.back() == '\r' ||
                              value.back() == ' ' || value.back() == '\t')) {
        value.pop_back();
    }
    return value.empty() ? L"v1.0.2" : std::wstring(value.begin(), value.end());
}
}

inline void version() {
    std::wcout << L"Версия: " << readVersion() << L"\n"
               << L"Платформа: Windows 10/11\n"
               << L"Кодировка файлов: UTF-8\n";
}