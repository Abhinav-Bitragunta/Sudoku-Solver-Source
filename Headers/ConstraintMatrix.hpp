#pragma once
#include "Libraries.hpp"
#include "Board.hpp"

class ConstraintMatrix {
   private:
    std::vector<bool>   data;
    size_t              numCols;
    size_t              numRows;
    size_t              gridSize;

    inline void         set             (const size_t row, const size_t col, const bool val);
    
   public:
    void                construct       (const Board& b);
    bool                at              (const size_t row, const size_t col) const;
    size_t              getRows         () const;
    size_t              getCols         () const;
};