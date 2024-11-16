#pragma once
#include "Libraries.hpp"

#define UINT unsigned int

/*
    !!!!! Does not work for Sudokus greater than 25*25 in size due to 32 bit integer restriction. !!!!!
          Using uint64_t instead allows upto 49*49 boards in 1 based indexing, and 64*64 in 0 based.
*/

class Board {
private:
    std::vector<int>            board;
    std::vector<UINT>           RowBitBoard;
    std::vector<UINT>           ColumnBitBoard;
    std::vector<UINT>           GridBitBoard;
    size_t                      N;
    size_t                      gridSize;

public:
    Board(){}
    Board(const size_t n);
    
    bool                        construct           (const std::vector<int>& newboard)                           ;
    bool                        unsafe              (const size_t row, const size_t col, const UINT val)    const;

    int                         at                  (const size_t row, const size_t col)                    const;
    size_t                      gridNum             (const size_t row, const size_t col)                    const;
    void                        set                 (const size_t row, const size_t col, const UINT val)         ;
    void                        set                 (const size_t idx, const UINT val)                           ;
    size_t                      rowlength           ()                                                      const;
    size_t                      gridsize            ()                                                      const;

    void                        printBoard          (const std::string& color)                                   ;
};