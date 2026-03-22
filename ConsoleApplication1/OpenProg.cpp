#include <string>
#include <iostream> 
#include <cstdlib>
void openProg() {
    std::string nameProg;
    std::cout << "Please enter the name of the program you would like to open. ";
    std::getline(std::cin, nameProg); // Используем getline, чтобы считать имя с пробелами

    // 2. Открываем программу
    std::cout << "Starting " << nameProg << "..." << std::endl;

    // system() передает строку в командную строку
    int result = std::system(nameProg.c_str());

    // Проверка на ошибки (результат != 0 обычно означает, что программа не найдена или не запустилась)
    if (result != 0) {
        std::cerr << "Failed to start or program not found." << std::endl;
     }
    }
    

