#pragma once
#include <math.h>
#include <vector>
#include "2_Board.hpp"

class ConstraintMatrix {
   private:
    std::vector<bool>   data;
    std::vector<std::vector<int>>    clues;
    size_t              numCols;
    size_t              numRows;
    size_t              gridSize;

   public:
    void                construct       (Board& b);
    void                set             (const size_t& row, const size_t& col, bool val);
    bool                at              (const size_t& row, const size_t& col);
    bool                cantPlaceHere   (const size_t& row, const size_t& col, size_t& val);
    size_t              getRows         ();
    size_t              getCols         ();
};

void ConstraintMatrix::construct(Board& b) {
    size_t n        = b.rowlength();
    
    this->gridSize  = std::sqrt(n);

    this->numCols   = 4 * n * n;
    this->numRows   = n * n * n;

    this->data      = std::vector<bool>(this->numCols * this->numRows, false);
    this->clues     = std::vector<std::vector<int>>();
    
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            if(b.at(row,col))  clues.emplace_back(std::vector<int>{b.at(row, col), row, col});
        }
    }

    //0-80: row-col, 81-161: row-num, 162-242: col-num, 243-323: grid-num
    for(size_t row = 0; row < n; row++) {
        for(size_t col = 0; col < n; col++) {
            for(size_t val = 0; val < n; val++) {
                if(cantPlaceHere(row,col,val)) continue;

                size_t  rowidx  = row * n * n + col * n + val,           // rows are 0-728, represent in base 9 as (row)(col)(val)
                        gridnum = (row / gridSize) * gridSize + (col / gridSize),

                        RCidx   = row     * n   + col             ,      // constr 0: row-col
                        RVidx   = row     * n   + val + n * n     ,      // constr 1: row-num
                        CVidx   = col     * n   + val + 2 * n * n ,      // constr 2: col-num
                        GNidx   = gridnum * n   + val + 3 * n * n ;      // constr 3: grid-num

                this->set(rowidx, RCidx,    true);
                this->set(rowidx, RVidx,    true);
                this->set(rowidx, CVidx,    true);
                this->set(rowidx, GNidx,    true);
            }
        }
    }
}

bool ConstraintMatrix::cantPlaceHere(const size_t& row, const size_t& col, size_t& val) {
    if(this->clues.empty()) return false;

    for(const auto& clue : this->clues) {
        
        size_t  v = clue[0] - 1,
                r = clue[1],
                c = clue[2],
                gridNumInput    = (row / this->gridSize) * this->gridSize + (col / this->gridSize),
                gridNumClue     = (r   / this->gridSize) * this->gridSize + (c   / this->gridSize);

        if((v == val || (r == row && c == col)) && (r == row && c == col && gridNumClue == gridNumInput) && !(r == row && v == val && c == col)) return true;
    }
    return false;
}

void ConstraintMatrix::set(const size_t& row, const size_t& col, bool val)  {   this->data[row * this->numCols + col] = val;    }
bool ConstraintMatrix::at(const size_t& row, const size_t& col)             {   return this->data[(row * this->numCols) + col]; }

size_t ConstraintMatrix::getRows()                                          {   return this->numRows;   }
size_t ConstraintMatrix::getCols()                                          {   return this->numCols;   }


