#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

void drawFlower(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "f";
    std::cout << "*";
    std::cout << "\033[" << y - 1 << ";" << x + 1 << "f";
    std::cout << "*";
    std::cout << "\033[" << y + 1 << ";" << x + 1 << "f";
    std::cout << "*";
    std::cout << "\033[" << y << ";" << x + 2 << "f";
    std::cout << "*";
    std::cout << "\033[" << y << ";" << x << "f";
    std::cout << "*";
}

int main() {
    const int screenWidth = 80;
    const int screenHeight = 25;

    srand(static_cast<unsigned int>(time(nullptr)));

    while (true) {
        system("cls");

        int centerX = rand() % screenWidth;
        int centerY = rand() % screenHeight;

        drawFlower(centerX, centerY);

        // Dormir durante un corto período de tiempo para una animación más suave
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}
