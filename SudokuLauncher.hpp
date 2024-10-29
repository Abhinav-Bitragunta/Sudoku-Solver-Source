#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
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
    while(!this->userInput()) {
        std::cout << "Sudoku length/breadth must be a perfect square\n";
    }
    Sudoku s(this->n, this->nums);
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
        std::cout << "\033[31m" << "No solution found.\n" << "\033[0m";
    }
    std::cout << std::format("Time elapsed: {} microseconds.\n",duration);
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