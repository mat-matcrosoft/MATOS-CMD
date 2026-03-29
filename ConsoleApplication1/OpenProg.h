#include <iostream>
#include <string>
#include <cstdlib> // Для функции system()
void openProg() {
	// Команда для запуск системной программы
	std::string progName;
	std::cout << "Введите имя программы/файла для запуска: ";
	std::cin >> progName;

	// Запуск программы
	system(progName.c_str());
}
