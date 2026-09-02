#pragma once

#include <windows.h>
#include <iostream>
#include <string>

namespace matcmd {
inline std::string wideToUtf8(const std::wstring& value) {
    if (value.empty()) {
        return {};
    }

    const int required = WideCharToMultiByte(
        CP_UTF8, WC_ERR_INVALID_CHARS, value.data(), static_cast<int>(value.size()),
        nullptr, 0, nullptr, nullptr);
    if (required <= 0) {
        return {};
    }

    std::string result(static_cast<size_t>(required), '\0');
    if (WideCharToMultiByte(
            CP_UTF8, WC_ERR_INVALID_CHARS, value.data(), static_cast<int>(value.size()),
            result.data(), required, nullptr, nullptr) <= 0) {
        return {};
    }
    return result;
}
}

inline bool addFile(const std::wstring& filename, const std::wstring& extension, const std::wstring& content) {
    std::wstring fullName = filename;
    if (!extension.empty()) {
        if (extension.front() != L'.') {
            fullName += L'.';
        }
        fullName += extension;
    }

    const std::string utf8Content = matcmd::wideToUtf8(content);
    if (!content.empty() && utf8Content.empty()) {
        std::wcerr << L"Ошибка: текст содержит недопустимую последовательность Unicode.\n";
        return false;
    }

    HANDLE file = CreateFileW(
        fullName.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Ошибка: не удалось создать файл '" << fullName
                   << L"'. Код Windows: " << GetLastError() << L"\n";
        return false;
    }

    DWORD written = 0;
    const bool writtenSuccessfully = utf8Content.empty() ||
        (utf8Content.size() <= MAXDWORD &&
         WriteFile(file, utf8Content.data(), static_cast<DWORD>(utf8Content.size()), &written, nullptr) &&
         written == utf8Content.size());
    CloseHandle(file);

    if (!writtenSuccessfully) {
        std::wcerr << L"Ошибка: не удалось записать файл '" << fullName << L"'.\n";
        return false;
    }

    std::wcout << L"Файл '" << fullName << L"' успешно создан в UTF-8.\n";
    return true;
}

inline int whatIsName() {
    std::wstring name;
    std::wstring extension;
    std::wstring content;

    std::wcout << L"Введите имя файла: ";
    if (!std::getline(std::wcin, name) || name.empty()) {
        std::wcerr << L"Ошибка: имя файла не может быть пустым.\n";
        return 1;
    }

    std::wcout << L"Введите расширение файла (например, txt, без точки): ";
    if (!std::getline(std::wcin, extension)) {
        return 1;
    }

    std::wcout << L"Введите содержимое файла: ";
    if (!std::getline(std::wcin, content)) {
        return 1;
    }

    return addFile(name, extension, content) ? 0 : 1;
}