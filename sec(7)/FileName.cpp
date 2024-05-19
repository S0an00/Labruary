#include <iostream>
#include <ctime>
using namespace std;
int main() {
    clock_t start, end;
    double cpu_time_used;
    char command;

    std::cout << "Press Enter to start the timer...";
    std::cin.get(); // Ждем ввода пользователя

    start = clock(); // Засекаем время начала

    while (true) {
        std::cout << "Timer is running. Press 's' to stop, 'c' to continue, 'q' to quit: ";
        std::cin >> command;
        //cout << cpu_time_used << endl;
        if (command == 's') {
            end = clock(); // Засекаем время окончания
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            std::cout << "Time measured: " << cpu_time_used << " seconds." << std::endl;
            start = clock(); // Сброс таймера
        }
        else if (command == 'c') {
            start = clock(); // Сброс таймера
        }
        else if (command == 'q') {
            break; // Выход из цикла
        }
    }

    return 0;
}