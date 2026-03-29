#include <iostream>
#include <string>
#include <ostream>
#include "OpenProg.h"
#include "CreateFile.h"
int main() {
	setlocale(LC_ALL, "RU");
    system("color 0A");
	//Переменные и функции.
	double num1, num2;
    char op;
	std::string comand, printText;
    
	//Операции
    std::cout << "________________________________________________________\n";
    std::cout << "|               MATOS-CMD версия 1.0                   |\n";
    std::cout << "|  (C) Корпорация Matcrosoft, 2024. Все права защищены!|\n";
    std::cout << "|______________________________________________________|\n\n";
	std::cout << "Welcome to MATOS-CMD! " << std::endl;
	while(10){
		std::cout << "Enter your comand >> ";
		std::cin >> comand;
		std::cout << "Result: " << std::endl;
		if (comand == "help") {
			std::cout << "Вы можете использывать команды: help, calculate, print, Shutdown, OpenProgram, NewFile." << std::endl;
		}
        else if (comand == "calculate") { //Калькулятор!!!

            std::cout << "Введите выражение (например, 5 + 3): ";
            std::cin >> num1 >> op >> num2;

            switch (op) {
            case '+':
                std::cout << "Результат: " << num1 + num2 << std::endl;
                break;
            case '-':
                std::cout << "Результат: " << num1 - num2 << std::endl;
                break;
            case '*':
                std::cout << "Результат: " << num1 * num2 << std::endl;
                break;
            case '/':
                if (num2 != 0)
                    std::cout << "Результат: " << num1 / num2 << std::endl;
                else
                    std::cout << "Ошибка: Деление на ноль!" << std::endl;
                break;
            default:
                std::cout << "Ошибка: Неверный оператор!" << std::endl;
            }
        }
        else if (comand == "Shutdown") { // Завершение работы окна.
            return 0;
        } else if (comand == "print") { // Команда print.
            std::cout << ">>";
            std::cin >> printText;
            std::cout << "" << std::endl;
            std::cout << printText << std::endl;
        }
        else if (comand == "OpenProgram") {
            openProg();
        }
        else if (comand == "NewFile") {
            whatIsName();
            
        }
        else {   //Если не определенна!
			std::cout << comand;
			std::cout << " is";
			std::cout << " Unknow comand!" << std::endl;
            system("color 0A");
		}
	}
	return 0;
}