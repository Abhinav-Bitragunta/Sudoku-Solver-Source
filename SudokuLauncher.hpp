#pragma once
#include <math.h>

#include <chrono>
#include <iostream>
#include <vector>

#include "Sudoku.hpp"
#include "SudokuFunctions.hpp"

class SudokuLauncher {
   private:
    size_t n;
    std::vector<int> nums;
    bool userInput();

   public:
    void launch();
};

void SudokuLauncher::launch() {
    Sudoku s;
    while(true) {
        while(!this->userInput()) {
            std::cout << "Sudoku length/breadth must be a perfect square.\n";
        }
        s = Sudoku(this->n, this->nums);
        if(s.validState())  break;
        std::cout << "\033[31m Illegal board state. \033[0m\n";
    }
    std::cout << "Board before solving:\n";
    s.printBoard("\033[0m");
    auto start = std::chrono::high_resolution_clock::now();
    bool solveSuccess = s.solve();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    if(solveSuccess) {
        std::cout << "Solution:\n";
        s.printBoard("\033[32m");
    } else {
        std::cout << "\033[31m No solution found. \033[0m\n";
    }
    std::cout << std::format("Time elapsed: {} microseconds.\n", duration);
}

bool SudokuLauncher::userInput() {
    std::cout << "Enter number of rows/columns in the Sudoku:\n";
    std::cin >> this->n;
    if(int root = std::sqrt(this->n); root * root != this->n) return false;
    this->nums = std::vector<int>(n * n, 0);
    std::cout << "Paste unsolved Sudoku:\n";
    for(int i = 0; i < n * n; i++) {
        std::cin >> this->nums[i];
    }
    return true;
}