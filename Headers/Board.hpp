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

public:
    Board(){}
    Board(const size_t n);
    
    bool                        construct           (const std::vector<int>& newboard)   ;
    bool                        unsafe              (size_t row, size_t col, UINT val)   ;

    int                         at                  (size_t row, size_t col)             ;
    size_t                      gridNum             (size_t row, size_t col)             ;
    void                        set                 (size_t row, size_t col, UINT val)   ;
    void                        set                 (size_t idx, UINT val)               ;
    size_t                      rowlength           ()                                   ;

    void                        printBoard          (std::string color)                  ;
};


