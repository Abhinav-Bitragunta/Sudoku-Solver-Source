#pragma once
#include "Sudoku.hpp"
#include "SudokuFunctions.hpp"
#include <stdexcept>

class SudokuLauncher {
   private:
    size_t n;
    std::vector<int> nums;

   public:
    void launch() {
        while(!this->userInput()){
            std::cout << "An error occured, please try again.\n";
        }
        Sudoku s(n, nums);
        std::cout << "Board before solving:\n";
        s.printBoard();
        if(s.solve()) {
            std::cout << "Solution:\n";
            s.printBoard();
        } else {
            std::cout << "No solution found.\n";
        }
    }

    bool userInput() {
        std::cout << "Enter number of rows/columns in the Sudoku:\n";
        std::cin >> this->n;
        this->nums = std::vector<int>(n * n, 0);
        std::cout << "Paste unsolved Sudoku:\n";
        for(int i = 0; i < n * n; i++) {
            std::cin >> this->nums[i];
        }
        return true;
    }
};