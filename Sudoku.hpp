#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Sudoku {
   private:
    std::vector<int>      BoardState;  // Uses 0 based indexing
    std::vector<uint32_t> RowBitBoard;
    std::vector<uint32_t> ColumnBitBoard;
    std::vector<uint32_t> GridBitBoard;
    size_t                n;

    const int&  at          (int row, int col);
    int         gridNum     (int row, int col);

    bool        rowSafe     (int row, int col, int val);
    bool        columnSafe  (int row, int col, int val);
    bool        gridSafe    (int row, int col, int val);

    void        set         (int row, int col, int val);

   protected:
    bool        solve       (int r, int c);
    bool        construct   (const size_t& n, const std::vector<int>& Board);
   
   public:
    void        printBoard  (std::string color);
};
