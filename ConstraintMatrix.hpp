#pragma once
#include <math.h>
#include <vector>
#include "Board.hpp"

class ConstraintMatrix {
   private:
    std::vector<bool>   data;
    size_t              numCols;
    size_t              numRows;

   public:
    void                construct       (Board& b);
    bool                at              (const size_t& row, const size_t& col);
    void                set             (const size_t& row, const size_t& col, bool val);
    size_t              getRows         ();
    size_t              getCols         ();
    bool                filled          (size_t& digit, size_t& row, size_t& col, std::vector<std::vector<int>>& prefill, size_t& SIZE);
};

void ConstraintMatrix::construct(Board& b) {
    size_t n = b.rowlength();
    size_t gridSize = std::sqrt(n);
    
    this->numCols = 4 * n * n;
    this->numRows = n * n * n;
    data = std::vector<bool>(this->numCols * this->numRows, false);
    
    std::vector<std::vector<int>> clues;
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            if(!b.at(row,col))  continue;
            clues.push_back({b.at(row, col), row, col});
        }
    }
    for(size_t d = 0; d < n; d++) {
        for(size_t r = 0; r < n; r++) {
            for(size_t c = 0; c < n; c++) {
                if(filled(d, r, c, clues, gridSize)) continue;
                int rowIdx          = n * n * d + n * r + c;
                int gridIdx         = (r / gridSize) * gridSize + c / gridSize;
                
                int colIdxRow       = 3 * n * d + r;
                int colIdxcol       = 3 * n * d + n + c;
                int colIdxblock     = 3 * n * d + 2 * n + gridIdx;
                int colIdxSimple    = 3 * n * n + c + n * r;
                
                this->set(rowIdx, colIdxRow,    true);
                this->set(rowIdx, colIdxcol,    true);
                this->set(rowIdx, colIdxblock,  true);
                this->set(rowIdx, colIdxSimple, true);
                // std::cout << std::format("Row {} and columns {},{},{},{} set as true.\n",rowIdx,colIdxRow,colIdxcol,colIdxblock,colIdxSimple);
            }
        }
    }
}

bool ConstraintMatrix::filled(size_t& digit, size_t& row, size_t& col, std::vector<std::vector<int>>& prefill, size_t& SIZE) {
    if(prefill.empty()) return false;
    int prefill_length = prefill.size();

    for(int i = 0; i < prefill_length; i++) {
        int d = prefill[i][0] - 1;
        int r = prefill[i][1];
        int c = prefill[i][2];

        // Calculate the block indices
        int blockStartIndexCol  = (c / SIZE) * SIZE;
        int blockEndIndexCol    = blockStartIndexCol + SIZE;
        int blockStartIndexRow  = (r / SIZE) * SIZE;
        int blockEndIndexRow    = blockStartIndexRow + SIZE;

        if((d != digit && row == r && col == c) || ((d == digit) && (row == r || col == c) && !(row == r && col == c)) || ((d == digit) && (row > blockStartIndexRow && row < blockEndIndexRow) && (col > blockStartIndexCol && col < blockEndIndexCol) && !(row == r && col == c))) return true;
    }
    return false;
}

void ConstraintMatrix::set(const size_t& row, const size_t& col, bool val)  {   this->data[row * this->numCols + col] = val;    }
bool ConstraintMatrix::at(const size_t& row, const size_t& col)             {   return this->data[(row * this->numCols) + col]; }

size_t ConstraintMatrix::getRows()                                          {   return this->numRows;   }
size_t ConstraintMatrix::getCols()                                          {   return this->numCols;   }
