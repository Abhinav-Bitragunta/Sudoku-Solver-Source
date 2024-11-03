#pragma once
#include <math.h>
#include <vector>
#include "2_Board.hpp"

class ConstraintMatrix {
   private:
    std::vector<bool>   data;
    size_t              numCols;
    size_t              numRows;
    size_t              gridSize;

    inline void         set             (const size_t& row, const size_t& col, bool val);
    
   public:
    void                construct       (Board& b);
    inline bool         at              (const size_t& row, const size_t& col);
    size_t              getRows         ();
    size_t              getCols         ();
};

void ConstraintMatrix::construct(Board& b) {
    size_t n        = b.rowlength();

    this->gridSize  = std::sqrt(n);

    this->numCols   = 4 * n * n;
    this->numRows   = n * n * n;

    this->data      = std::vector<bool>(this->numCols * this->numRows, false);

    //0-80: row-col, 81-161: row-num, 162-242: col-num, 243-323: grid-num
    for(size_t row = 0; row < n; row++) {
        for(size_t col = 0; col < n; col++) {
            for(size_t val = 0; val < n; val++) {
                if(b.unsafe(row,col,val+1)) continue;

                size_t  rowidx  = row * n * n + col * n + val,           // rows are 0-728, represent in base 9 as (row)(col)(val)
                        gridnum = (row / gridSize) * gridSize + (col / gridSize),

                        RCidx   = row     * n   + col             ,      // constr 0: row-col
                        RVidx   = row     * n   + val + n * n     ,      // constr 1: row-num
                        CVidx   = col     * n   + val + 2 * n * n ,      // constr 2: col-num
                        GVidx   = gridnum * n   + val + 3 * n * n ;      // constr 3: grid-num

                this->set(rowidx, RCidx,    true);
                this->set(rowidx, RVidx,    true);
                this->set(rowidx, CVidx,    true);
                this->set(rowidx, GVidx,    true);
            }
        }
    }
}

inline void ConstraintMatrix::set(const size_t& row, const size_t& col, bool val)  {   this->data[row * this->numCols + col] = val;    }
inline bool ConstraintMatrix::at(const size_t& row, const size_t& col)             {   return this->data[(row * this->numCols) + col]; }

size_t ConstraintMatrix::getRows()                                          {   return this->numRows;   }
size_t ConstraintMatrix::getCols()                                          {   return this->numCols;   }


