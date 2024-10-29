#pragma once
#include <math.h>
#include <cstdint>
#include <format>
#include <iostream>
#include <string>
#include "Sudoku.hpp"

const int& Sudoku::at(int row, int col) {
    return this->BoardState[row * this->n + col];
}
int Sudoku::gridNum(int row, int col) {
    size_t gridSize = sqrt(this->n);
    row /= gridSize;
    col /= gridSize;
    return row * gridSize + col;
}

void Sudoku::set(int row, int col, int val) {
    int index = row * this->n + col;
    int prev  = this->BoardState[index];
    this->BoardState[index] = val;

    int gridIdx = gridNum(row, col);
    if(!val) {
        this->RowBitBoard[row]      &= ~(1U << prev);
        this->ColumnBitBoard[col]   &= ~(1U << prev);
        this->GridBitBoard[gridIdx] &= ~(1U << prev);
    } else {
        this->RowBitBoard[row]      |= (1U << val);
        this->ColumnBitBoard[col]   |= (1U << val);
        this->GridBitBoard[gridIdx] |= (1U << val);
    }
}

void Sudoku::printBoard(std::string color) {
    size_t gridSize = std::sqrt(this->n);
    std::string horizontalLine(3 * (gridSize + this->n) + 1, '-');

    std::cout << color;
    for(int row = 0; row < this->n; row++) {
        if(row % gridSize == 0) std::cout << horizontalLine << std::endl;

        for(int col = 0; col < this->n; col++) {
            if(col % gridSize == 0) std::cout << "|  ";
            std::cout << std::format("{}{} ", this->at(row, col), ((this->at(row, col) > 9) ? "" : " "));
        }

        std::cout << "|  \n";
    }
    std::cout << horizontalLine << "\033[0m\n";
}

bool Sudoku::rowSafe(int row, int col, int val) {
    return !(RowBitBoard[row] & 1U << val);
}

bool Sudoku::columnSafe(int row, int col, int val) {
    return !(ColumnBitBoard[col] & 1U << val);
}

bool Sudoku::gridSafe(int row, int col, int val) {
    return !(GridBitBoard[gridNum(row, col)] & 1U << val);
}

//Attempts to construct a board of given size. If valid returns true else false.
bool Sudoku::construct(const size_t& n, const std::vector<int>& Board) {
    this->n = n;
    this->BoardState  = std::vector<int>(Board);
    this->RowBitBoard = this->ColumnBitBoard = this->GridBitBoard = std::vector<uint32_t>(this->n, 0);

    for(int row = 0; row < this->n; row++) {
        for(int col = 0; col < this->n; col++) {
            if(this->at(row, col) < 0 || this->at(row, col) > this->n) return false;
            
            uint32_t onBit = 1U << (this->at(row, col));
            if(onBit == 1) continue;
            
            if((this->RowBitBoard[row] | this->ColumnBitBoard[col] | this->GridBitBoard[gridNum(row, col)]) & onBit) return false;

            this->RowBitBoard[row] |= onBit;
            this->ColumnBitBoard[col] |= onBit;
            this->GridBitBoard[gridNum(row, col)] |= onBit;
        }
    }
    return true;
}

bool Sudoku::solve(int r, int c) {
    if(r == this->n)    return true;
    if(c == this->n)    return solve(r + 1, 0);
    if(this->at(r, c))  return solve(r, c + 1);

    for(int candidate = 1; candidate <= this->n; candidate++) {
        
        if(this->gridSafe(r, c, candidate) && this->rowSafe(r, c, candidate) && this->columnSafe(r, c, candidate)) {
            
            this->set(r, c, candidate);
            if(this->solve(r, c + 1)) return true;
            this->set(r, c, 0);

        }
    }
    return false;
}