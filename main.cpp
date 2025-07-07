
#include "MenuBiblioteca.h"

int main() {
    #ifdef _WIN32
    system("chcp 65001"); // Para Windows
    #endif
    MenuBiblioteca menu;
    menu.ejecutar();
    return 0;
}
