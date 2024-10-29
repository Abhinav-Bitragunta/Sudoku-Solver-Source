#pragma once
#include <math.h>
#include <chrono>
#include <iostream>
#include <vector>
#include "Sudoku.hpp"
#include "SudokuFunctions.hpp"

class SudokuLauncher : public Sudoku {
   private:
    size_t N;
    std::vector<int> nums;
    bool userInput();

   public:
    void launch();
};

void SudokuLauncher::launch() {
    SudokuLauncher s;
    while(true) {
        while(!this->userInput()) {
            std::cout << "\033[31m Invalid board size detected, it must be a perfect square. \033[0m\n";
        }
        if(s.construct(this->N, this->nums)) break;
        std::cout << std::format("\033[31m Illegal board state. All values must be between 0 and {}, both inclusive. \033[0m\n", this->N);
    }

    std::cout << "\nBoard before solving:\n";
    s.printBoard("\033[0m");

    auto start  = std::chrono::high_resolution_clock::now();
    bool solveSuccess = s.solve(0, 0);
    auto end    = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    if(solveSuccess) {
        std::cout << "\nSolution:\n";
        s.printBoard("\033[32m");
    } else {
        std::cout << "\033[31m A solution does not exist. \033[0m\n";
    }

    std::cout << std::format("Time elapsed: {} microseconds.\n", duration);
}

bool SudokuLauncher::userInput() {
    std::cout << "Enter number of rows/columns in the Sudoku: ";
    std::cin >> this->N;

    if(int root = std::sqrt(this->N); root * root != this->N) return false;

    this->nums = std::vector<int>(N * N, 0);

    std::cout << "\nPaste unsolved Sudoku:\n";
    for(int i = 0; i < N * N; i++) {
        std::cin >> this->nums[i];
    }

    return true;
}