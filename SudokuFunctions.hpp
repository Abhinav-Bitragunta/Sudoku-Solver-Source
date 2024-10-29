#pragma once
#include <cmath>

#include "Sudoku.hpp"

Sudoku::Sudoku(const size_t n, const std::vector<int> &Board) {
    this->n = n;
    this->BoardState = std::vector<int>(Board);
    std::cout << std::format("Sudoku board of size {}*{} has been initialized.\n", n, n);
}

Sudoku::~Sudoku() { std::cout << "Solving complete.\n"; }

const int &Sudoku::at(int row, int col) {
    return this->BoardState[row * this->n + col];
}

void Sudoku::set(int row, int col, int val) {
    this->BoardState[row * this->n + col] = val;
}

void Sudoku::printBoard() {
    size_t gridSize = sqrt(this->n);
    for(int row = 0; row < this->n; row++) {
        for(int col = 0; col < this->n; col++) {
            std::cout << std::format("{}\t", this->at(row, col));
            if((col + 1) % gridSize == 0) {
                std::cout << "|\t";
            }
        }
        std::cout << std::endl;

        if((row + 1) % gridSize == 0) {
            std::cout << std::endl;
        }
    }
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
    size_t gridSize = sqrt(this->n);
    int startRow = row - (row % gridSize);
    int startCol = col - (col % gridSize);

    for(int r = startRow; r < startRow + gridSize; r++) {
        for(int c = startCol; c < startCol + gridSize; c++) {
            if(this->at(r, c) == val && row != r && col != c) return false;
        }
    }
    return true;
}

std::pair<int, int> Sudoku::firstEmptyLocation() {
    for(int row = 0; row < this->n; row++) {
        for(int col = 0; col < this->n; col++) {
            if(!this->at(row, col)) return std::make_pair(row, col);
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