#pragma once
#include <math.h>
#include <cstddef>
#include <format>
#include <iostream>
#include <string>
#include <vector>

class Board {
    std::vector<int>            board;
    std::vector<unsigned int>   RowBitBoard;
    std::vector<unsigned int>   ColumnBitBoard;
    std::vector<unsigned int>   GridBitBoard;
    size_t                      N;

   public:
    Board(){}
    Board(const size_t n);
    bool                        construct           (const std::vector<int>& newboard);

    const int&                  at                  (const size_t& row, const size_t& col);
    void                        set                 (const size_t& row, const size_t& col, const int& val);
    void                        set                 (const size_t& idx, const int& val);
    size_t                      gridNum             (const size_t& row, const size_t& col);
    const size_t                rowlength           ();

    void                        printBoard          (std::string color);
};


//Attempts to construct a Sudoku board given a user input. Returns false if invalid board state detected.
bool Board::construct(const std::vector<int>& newboard) {
    this->board = std::vector<int>(newboard);
    this->N     = std::sqrt(newboard.size());

    this->RowBitBoard = this->ColumnBitBoard = this->GridBitBoard = std::vector<unsigned int>(this->N, 0);

    for(int row = 0; row < this->N; row++) {
        for(int col = 0; col < this->N; col++) {
            if(this->at(row, col) < 0 || this->at(row, col) > this->N) return false;

            unsigned int onBit = 1U << (this->at(row, col));
            if(onBit == 1) continue;

            if((this->RowBitBoard[row] | this->ColumnBitBoard[col] | this->GridBitBoard[gridNum(row, col)]) & onBit) return false;

            this->RowBitBoard[row]                  |= onBit;
            this->ColumnBitBoard[col]               |= onBit;
            this->GridBitBoard[gridNum(row, col)]   |= onBit;
        }
    }
    return true;
}

void Board::printBoard(std::string color) {
    size_t gridSize = std::sqrt(this->N);
    std::string horizontalLine(3 * (gridSize + this->N) + 1, '-');

    std::cout << color;
    for(int row = 0; row < this->N; row++) {
        if(row % gridSize == 0) std::cout << horizontalLine << std::endl;

        for(int col = 0; col < this->N; col++) {
            if(col % gridSize == 0) std::cout << "|  ";
            std::cout << std::format("{}{} ", this->at(row, col), ((this->at(row, col) > 9) ? "" : " "));
        }

        std::cout << "|  \n";
    }
    std::cout << horizontalLine << "\033[0m\n";
}

Board::Board(const size_t n) {
    this->board = std::vector<int>(n * n, 0);
    this->N     = n;
}

size_t Board::gridNum(const size_t& row, const size_t& col) {
    size_t gridSize = sqrt(this->N);
    return (row/gridSize) * gridSize + (col/gridSize);
}

const int& Board::at(const size_t& row, const size_t& col)              {   return board[row * this->N + col];  }
void Board::set(const size_t& row, const size_t& col, const int& val)   {   board[row * this->N + col] = val;   }
void Board::set(const size_t& idx, const int& val)                      {   board[idx] = val;   }

const size_t Board::rowlength()                                         {   return this->N; }
