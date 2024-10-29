#pragma once
#include <vector>

class Sudoku{
    private:
        std::vector<int> BoardState; //Uses 0 based indexing
        size_t n;

        bool rowSafe(int row, int col, int val);
        bool columnSafe(int row, int col, int val);
        bool gridSafe(int row, int col, int val);
        const int& at(int row, int col);
        void set(int row, int col, int val);
        std::pair<int,int> firstEmptyLocation();

    public:
        Sudoku(const size_t n, const std::vector<int>& Board);
        Sudoku(){}
        ~Sudoku();
        void printBoard();
        bool solve();

};


