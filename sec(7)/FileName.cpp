#include <iostream>
#include <ctime>
using namespace std;
int main() {
    clock_t start, end;
    double cpu_time_used;
    char command;

    std::cout << "Press Enter to start the timer...";
    std::cin.get(); // ���� ����� ������������

    start = clock(); // �������� ����� ������

    while (true) {
        std::cout << "Timer is running. Press 's' to stop, 'c' to continue, 'q' to quit: ";
        std::cin >> command;
        //cout << cpu_time_used << endl;
        if (command == 's') {
            end = clock(); // �������� ����� ���������
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            std::cout << "Time measured: " << cpu_time_used << " seconds." << std::endl;
            start = clock(); // ����� �������
        }
        else if (command == 'c') {
            start = clock(); // ����� �������
        }
        else if (command == 'q') {
            break; // ����� �� �����
        }
    }

    return 0;
}