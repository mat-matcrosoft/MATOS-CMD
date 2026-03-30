#include <iostream>
#include <fstream>
#include <string>
void version(){
    std::ifstream file("version.txt");
    std::string vers;
    file >> vers;
    if (file.is_open()) {
        std::cout << "Version: " << std::endl;
        std::cout << vers << std::endl;
        std::cout << "Platform - Windows" << std::endl;
        std::cout << "You can update your version of application, write 'update'. " << std::endl;
        file.close();
    }
}