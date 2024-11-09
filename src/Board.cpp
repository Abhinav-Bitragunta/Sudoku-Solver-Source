#include "Board.hpp"

//Return value at Board[row][col]
int  Board::at (size_t row, size_t col)             {   return board[row * this->N + col];  }

//Set Board[row][col] to val
void Board::set(size_t row, size_t col, UINT val)   {   board[row * this->N + col] = val;   }

//Set Board[idx] to val
void Board::set(size_t idx, UINT val)               {   board[idx] = val;   }

//For a n*n Sudoku, returns n.
size_t Board::rowlength()                           {   return this->N; }

//It exists already, and that value is not equal to val. OR It doesn't exist and placement is illegal.
bool Board::unsafe(size_t row, size_t col, UINT val){
    return  (this->at(row,col) && (this->at(row,col) != val)) || (!this->at(row,col) && ((RowBitBoard[row] | ColumnBitBoard[col] | GridBitBoard[gridNum(row,col)]) & 1U << val));
}

//Attempts to construct a Sudoku board given a user input. Returns false if invalid board state detected.
bool Board::construct(const std::vector<int>& newboard) {
    this->board = newboard;
    this->N     = std::sqrt(newboard.size());

    this->RowBitBoard = this->ColumnBitBoard = this->GridBitBoard = std::vector<UINT>(this->N, 0);

    for(int row = 0; row < this->N; row++) {
        for(int col = 0; col < this->N; col++) {
            if(this->at(row, col) < 0 || this->at(row, col) > this->N) return false;

            UINT onBit = 1U << (this->at(row, col));
            if(onBit == 1) continue;

            if((this->RowBitBoard[row] | this->ColumnBitBoard[col] | this->GridBitBoard[gridNum(row, col)]) & onBit) return false;

            this->RowBitBoard[row]                  |= onBit;
            this->ColumnBitBoard[col]               |= onBit;
            this->GridBitBoard[gridNum(row, col)]   |= onBit;
        }
    }
    return true;
}


Board::Board(const size_t n) {
    this->board = std::vector<int>(n * n, 0);
    this->N     = n;
}

//Return the grid to which a certain [row][col] belongs to.
size_t Board::gridNum(size_t row, size_t col) {
    size_t gridSize = sqrt(this->N);
    return (row/gridSize) * gridSize + (col/gridSize);
}

//Prints the board in specified ANSI color
void Board::printBoard(std::string color) {
    size_t gridSize = std::sqrt(this->N);
    std::string horizontalLine(3 * (gridSize + this->N) + 1, '-');

    std::cout << color;
    for(int row = 0; row < this->N; row++) {
        if(row % gridSize == 0) std::cout << horizontalLine << std::endl;

        for(int col = 0; col < this->N; col++) {
            if(col % gridSize == 0) std::cout << "|  ";
            std::cout << std::format("{}{} ", this->at(row, col), ((this->at(row, col) > 9) ? "" : " "));
        }

        std::cout << "|  \n";
    }
    std::cout << horizontalLine << "\033[0m\n";
}