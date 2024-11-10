#pragma once
#include "Libraries.hpp"
#include "Board.hpp"

class ConstraintMatrix {
   private:
    std::vector<bool>   data;
    size_t              numCols;
    size_t              numRows;
    size_t              gridSize;

    void         set             (const size_t& row, const size_t& col, bool val);
    
   public:
    void                construct       (Board& b);
    bool         at              (const size_t& row, const size_t& col);
    size_t              getRows         ();
    size_t              getCols         ();
};