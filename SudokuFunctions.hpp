#pragma once
#include <math.h>

#include <format>
#include <iostream>
#include <string>

#include "Sudoku.hpp"

Sudoku::Sudoku(const size_t n, const std::vector<int> &Board) {
    this->n = n;
    this->BoardState = std::vector<int>(Board);
    std::cout << std::format("Sudoku board of size {}*{} has been initialized.\n", n, n);
}

const int &Sudoku::at(int row, int col) {
    return this->BoardState[row * this->n + col];
}

void Sudoku::set(int row, int col, int val) {
    this->BoardState[row * this->n + col] = val;
}

void Sudoku::printBoard(std::string color) {
    size_t gridSize = std::sqrt(this->n);
    std::string horizontalLine(gridSize * 3 + this->n * 3 + 1, '-');
    std::cout << color;
    for(int row = 0; row < this->n; row++) {
        if(row % gridSize == 0) std::cout << horizontalLine << std::endl;

        for(int col = 0; col < this->n; col++) {
            if(col % gridSize == 0) std::cout << "|  ";
            std::cout << std::format("{}{} ", this->at(row, col), (((this->at(row, col) > 9 || col == this->n - 1) && !(this->at(row, col) <= 9 && col == this->n - 1)) ? "" : " "));
        }

        std::cout << "|  " << std::endl;
    }
    std::cout << horizontalLine << "\033[0m\n";
}

bool Sudoku::rowSafe(int row, int col, int val) {
    for(int i = 0; i < this->n; i++) {
        if(this->at(row, i) == val && i != col) return false;
    }
    return true;
}

bool Sudoku::columnSafe(int row, int col, int val) {
    for(int i = 0; i < this->n; i++) {
        if(this->at(i, col) == val && i != row) return false;
    }
    return true;
}

bool Sudoku::gridSafe(int row, int col, int val) {
    size_t gridSize = std::sqrt(this->n);
    int startRow = row - (row % gridSize);
    int startCol = col - (col % gridSize);

    for(int r = startRow; r < startRow + gridSize; r++) {
        for(int c = startCol; c < startCol + gridSize; c++) {
            if(this->at(r, c) == val && row != r && col != c) return false;
        }
    }
    return true;
}

bool Sudoku::validState() {
    for(int row = 0; row < this->n; row++) {
        for(int col = 0; col < this->n; col++) {
            int val = this->at(row, col);

            if(val!=0 && !(gridSafe(row,col,val) && rowSafe(row,col,val) && columnSafe(row,col,val) && val <= (int)this->n)) return false;
        }
    }
    return true;
}

std::pair<int, int> Sudoku::firstEmptyLocation() {
    for(int row = 0; row < this->n; row++) {
        for(int col = 0; col < this->n; col++) {
            if(this->at(row, col) <= 0) return std::make_pair(row, col);
        }
    }
    return std::make_pair(this->n, this->n);
}

bool Sudoku::solve() {
    auto [row, col] = this->firstEmptyLocation();
    if(row == this->n || col == this->n) return true;
    for(int candidate = 1; candidate <= this->n; candidate++) {
        if(this->gridSafe(row, col, candidate) && this->rowSafe(row, col, candidate) && this->columnSafe(row, col, candidate)) {
            this->set(row, col, candidate);
            if(this->solve()) return true;
            this->set(row, col, 0);
        }
    }
    return false;
}