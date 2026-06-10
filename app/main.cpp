#include <iostream>
#include <window.h>

int main() {
    std::cout << "Hello world!" << std::endl;
    AppWindow screen = AppWindow();

    screen.open();

    return 0;
}