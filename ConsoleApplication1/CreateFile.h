#include <iostream>
#include <fstream>
#include <string>

// Функция для создания файла и записи содержимого
void addFile(const std::string& filename, const std::string& extension, const std::string& content) {
    setlocale(LC_ALL, "RU");
    // Формируем полное имя файла (имя + . + расширение)
    std::string fullName = filename + "." + extension;

    // Открываем файл для записи (ofstream автоматически создает файл, если его нет)
    std::ofstream outFile(fullName);

    // Проверяем, удалось ли создать/открыть файл
    if (outFile.is_open()) {
        outFile << content; // Записываем контент
        outFile.close();    // Закрываем файл
        std::cout << "Файл '" << fullName << "' успешно создан и изменен." << std::endl;
    }
    else {
        std::cerr << "Ошибка: не удалось создать файл '" << fullName << "'." << std::endl;
    }
}

int whatIsName() {
    std::string name, ext, text;
    setlocale(LC_ALL, "RU");
    // Запрос данных у пользователя
    std::cout << "Введите имя файла: ";
    std::cin >> name;
    std::cout << "Введите расширение файла (например, txt БЕЗ ТОЧКИ!): ";
    std::cin >> ext;
    std::cin.ignore(); // Очистка буфера после cin
    std::cout << "Введите содержимое файла: ";
    std::getline(std::cin, text); // Считываем строку с пробелами

    // Вызов функции
    addFile(name, ext, text);

    return 0;
}
