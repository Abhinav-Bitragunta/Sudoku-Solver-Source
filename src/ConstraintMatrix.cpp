#include "ConstraintMatrix.hpp"

//Construct the matrix using given board.
void ConstraintMatrix::construct(Board& b) {
    size_t n        = b.rowlength();
    size_t nSquared = n*n;

    this->gridSize  = static_cast<size_t>(std::sqrt(n));

    this->numCols   = 4 * nSquared;
    this->numRows   = n * nSquared;

    this->data      = std::vector<bool>(this->numCols * this->numRows, false);

    //0-80: row-col, 81-161: row-num, 162-242: col-num, 243-323: grid-num
    for(size_t row = 0; row < n; row++) {
        for(size_t col = 0; col < n; col++) {
            for(size_t val = 0; val < n; val++) {
                if(b.unsafe(row,col,val+1)) continue;

                size_t  rowidx  = row * nSquared + col * n + val,           // rows are 0-728, represent in base 9 as (row)(col)(val)
                        gridnum = (row / gridSize) * gridSize + (col / gridSize),

                        RCidx   = row     * n   + col                ,      // constr 0: row-col
                        RVidx   = row     * n   + val + nSquared     ,      // constr 1: row-num
                        CVidx   = col     * n   + val + 2 * nSquared ,      // constr 2: col-num
                        GVidx   = gridnum * n   + val + 3 * nSquared ;      // constr 3: grid-num

                this->set(rowidx, RCidx,    true);
                this->set(rowidx, RVidx,    true);
                this->set(rowidx, CVidx,    true);
                this->set(rowidx, GVidx,    true);
            }
        }
    }
}

//Set matrix[row][col] to val
void ConstraintMatrix::set(const size_t& row, const size_t& col, bool val)  {   this->data[row * this->numCols + col] = val;    }

//Return value at matrix[row][col]
bool ConstraintMatrix::at(const size_t& row, const size_t& col)             {   return this->data[(row * this->numCols) + col]; }

//Return number of rows in matrix
size_t ConstraintMatrix::getRows()                                          {   return this->numRows;   }

//Return number of columns in matrix
size_t ConstraintMatrix::getCols()                                          {   return this->numCols;   }