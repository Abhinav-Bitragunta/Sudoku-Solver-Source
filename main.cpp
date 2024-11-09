#include "Solver.hpp"

int main(){
    //Keep the application open till the user decides to close it.
    std::string exitOrNo;
    do{
        Solver game;
        game.launch();

        std::cout << "\nPlease type \'Exit\' to close, anything else to run again: ";
    }while(std::cin >> exitOrNo && exitOrNo != "Exit");
}