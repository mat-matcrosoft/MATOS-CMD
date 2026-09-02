#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <cwctype>
#include <iostream>
#include <sstream>
#include <string>

#include "OpenProg.h"
#include "CreateFile.h"
#include "versionCMD.cpp"

namespace {
constexpr const wchar_t* kReset = L"\x1b[0m";
constexpr const wchar_t* kCyan = L"\x1b[96m";
constexpr const wchar_t* kGreen = L"\x1b[92m";
constexpr const wchar_t* kRed = L"\x1b[91m";
constexpr const wchar_t* kYellow = L"\x1b[93m";

std::wstring trim(const std::wstring& value) {
    const auto first = value.find_first_not_of(L" \t\r\n");
    if (first == std::wstring::npos) {
        return L"";
    }
    const auto last = value.find_last_not_of(L" \t\r\n");
    return value.substr(first, last - first + 1);
}

std::wstring lowerCommand(std::wstring value) {
    for (wchar_t& character : value) {
        character = static_cast<wchar_t>(std::towlower(character));
    }
    return value;
}

void configureConsole() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // Keep stdin/stdout in UTF-8 while wide streams preserve Unicode text.
    _setmode(_fileno(stdin), _O_U8TEXT);
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stderr), _O_U8TEXT);

    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (output != INVALID_HANDLE_VALUE && GetConsoleMode(output, &mode)) {
        SetConsoleMode(output, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
}

void printHelp() {
    std::wcout << kCyan << L"Доступные команды:" << kReset << L"\n"
               << L"  help        — показать эту справку\n"
               << L"  calculate   — вычислить простое выражение\n"
               << L"  print       — вывести текст\n"
               << L"  newfile     — создать UTF-8 файл\n"
               << L"  openprogram — открыть программу или файл\n"
               << L"  version     — показать версию\n"
               << L"  shutdown    — завершить работу\n";
}

bool readLine(const wchar_t* prompt, std::wstring& value) {
    std::wcout << prompt;
    std::wcout.flush();
    return static_cast<bool>(std::getline(std::wcin, value));
}
}

int wmain() {
    configureConsole();

    std::wcout << kCyan
               << L"________________________________________________________\n"
               << L"|               MATOS-CMD версия 1.0.2                |\n"
               << L"|  (C) MT Software, 2026. Лицензия MIT                |\n"
               << L"|______________________________________________________|\n\n"
               << kReset
               << L"Добро пожаловать в MATOS-CMD! Введите help для справки.\n";

    std::wstring line;
    while (readLine(L"Введите команду >> ", line)) {
        line = trim(line);
        if (line.empty()) {
            continue;
        }

        std::wistringstream input(line);
        std::wstring command;
        input >> command;
        std::wstring arguments;
        std::getline(input, arguments);
        arguments = trim(arguments);
        command = lowerCommand(command);

        if (command == L"help") {
            printHelp();
        } else if (command == L"calculate") {
            if (arguments.empty() && !readLine(L"Введите выражение (например, 5 + 3): ", arguments)) {
                break;
            }

            std::wistringstream expression(arguments);
            double first = 0.0;
            double second = 0.0;
            wchar_t operation = L'\0';
            if (!(expression >> first >> operation >> second)) {
                std::wcout << kRed << L"Ошибка: введите выражение в формате 5 + 3." << kReset << L"\n";
                continue;
            }

            switch (operation) {
            case L'+':
                std::wcout << kGreen << L"Результат: " << first + second << kReset << L"\n";
                break;
            case L'-':
                std::wcout << kGreen << L"Результат: " << first - second << kReset << L"\n";
                break;
            case L'*':
                std::wcout << kGreen << L"Результат: " << first * second << kReset << L"\n";
                break;
            case L'/':
                if (second == 0.0) {
                    std::wcout << kRed << L"Ошибка: деление на ноль." << kReset << L"\n";
                } else {
                    std::wcout << kGreen << L"Результат: " << first / second << kReset << L"\n";
                }
                break;
            default:
                std::wcout << kRed << L"Ошибка: неизвестный оператор." << kReset << L"\n";
                break;
            }
        } else if (command == L"print") {
            if (arguments.empty() && !readLine(L">> ", arguments)) {
                break;
            }
            std::wcout << arguments << L"\n";
        } else if (command == L"newfile") {
            whatIsName();
        } else if (command == L"openprogram") {
            openProg(arguments);
        } else if (command == L"version") {
            version();
        } else if (command == L"shutdown" || command == L"exit" || command == L"quit") {
            std::wcout << kYellow << L"Работа MATOS-CMD завершена." << kReset << L"\n";
            return 0;
        } else {
            std::wcout << kRed << L"Неизвестная команда: " << command << kReset << L"\n";
        }
    }

    return 0;
}