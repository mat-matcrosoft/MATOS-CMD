#pragma once

#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Shell32.lib")

inline std::wstring trimProgramName(std::wstring value) {
    const auto first = value.find_first_not_of(L" \t");
    if (first == std::wstring::npos) {
        return L"";
    }
    const auto last = value.find_last_not_of(L" \t");
    value = value.substr(first, last - first + 1);
    if (value.size() >= 2 && value.front() == L'"' && value.back() == L'"') {
        value = value.substr(1, value.size() - 2);
    }
    return value;
}

inline void openProg(const std::wstring& requestedName = L"") {
    std::wstring programName = trimProgramName(requestedName);
    if (programName.empty()) {
        std::wcout << L"Введите путь к программе или файлу: ";
        if (!std::getline(std::wcin, programName)) {
            return;
        }
        programName = trimProgramName(programName);
    }

    if (programName.empty()) {
        std::wcerr << L"Ошибка: путь не может быть пустым.\n";
        return;
    }

    const HINSTANCE result = ShellExecuteW(
        nullptr, L"open", programName.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    if (reinterpret_cast<INT_PTR>(result) <= 32) {
        std::wcerr << L"Ошибка: не удалось открыть '" << programName
                   << L"'. Код Windows: " << reinterpret_cast<INT_PTR>(result) << L"\n";
        return;
    }

    std::wcout << L"Открыто: " << programName << L"\n";
}