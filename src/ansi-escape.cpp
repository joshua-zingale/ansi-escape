#include<iostream>
#include<stdlib.h>

#include<ansi.hpp>
#include<environment.hpp>

int main(int argc, char *argv[]) {
    int height, width;
    bool piping = false;
    if (get_terminal_size(&width, &height) != 0){
        piping = true;
    }


    if (!piping) {
        std::cout
        << ansi::clearScreen
        << ansi::moveCursor(0,0)
        << ansi::save
        << std::flush; 

        std::cerr << ansi::moveCursor(height-1, 1) << "> " << std::flush;
    }


    std::string input = "";

    bool first = true;
    while (first || std::getline(std::cin, input)) {
        first = false;
        std::string unescapedInput = ansi::unescape(input);

        std::cout << ansi::load << unescapedInput << ansi::save;

        if (!piping) {
            std::cerr << ansi::moveCursor(height-2, 1);
            for (int i = 0; i < width; ++i) std::cerr << '~';
            std::cerr
            << ansi::moveCursor(height-1, 1)
            << ansi::clearScreenFromCursor
            << "> " << std::flush;
        }
        

       
    }

    
    return 1;
}

