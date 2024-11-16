#include "Board.hpp"

//Return value at Board[row][col]
int  Board::at (const size_t row, const size_t col)              const{   return board[row * this->N + col];  }

//Set Board[row][col] to val
void Board::set(const size_t row, const size_t col, const UINT val)   {   board[row * this->N + col] = val;   }

//Set Board[idx] to val
void Board::set(const size_t idx, const UINT val)                     {   board[idx] = val;   }

//For a n*n Sudoku, returns n.
size_t Board::rowlength()                                        const{   return this->N; }

//For a n*n Sudoku, returns sqrt(n).
size_t Board::gridsize()                                         const{   return this->gridSize; }


//It exists already, and that value is not equal to val. OR It doesn't exist and placement is illegal.
bool Board::unsafe(const size_t row, const size_t col, const UINT val) const{
    return  (this->at(row,col) && (this->at(row,col) != val)) || (!this->at(row,col) && ((RowBitBoard[row] | ColumnBitBoard[col] | GridBitBoard[gridNum(row,col)]) & 1U << val));
}

//Attempts to construct a Sudoku board given a user input. Returns false if invalid board state detected.
bool Board::construct(const std::vector<int>& newboard) {
    this->board     = newboard;
    this->N         = std::sqrt(newboard.size());
    this->gridSize  = std::sqrt(this->N);

    this->RowBitBoard = this->ColumnBitBoard = this->GridBitBoard = std::vector<UINT>(this->N, 0);
    LOG("Initialization of bitboards successful.");

    for(int row = 0; row < this->N; row++) {
        for(int col = 0; col < this->N; col++) {
            if(this->at(row, col) < 0 || this->at(row, col) > this->N){
                LOG("Value out of limits at row " + std::to_string(row) + " " + ", col " + std::to_string(col));
                return false;
            }

            UINT onBit = 1U << (this->at(row, col));
            if(onBit == 1) continue;

            if((this->RowBitBoard[row] | this->ColumnBitBoard[col] | this->GridBitBoard[gridNum(row, col)]) & onBit){
                LOG("Constraint violated by value at row " + std::to_string(row) + " " + ", col " + std::to_string(col));
                return false;
            }

            this->RowBitBoard[row]                  |= onBit;
            this->ColumnBitBoard[col]               |= onBit;
            this->GridBitBoard[gridNum(row, col)]   |= onBit;
        }
    }
    LOG("Board constructed successfully");
    return true;
}

//Constructor for n*n board
Board::Board(const size_t n) {
    this->board     = std::vector<int>(n * n, 0);
    this->N         = n;
    this->gridSize  = std::sqrt(n);
}

//Return the grid to which a certain [row][col] belongs to.
size_t Board::gridNum(const size_t row, const size_t col) const {
    return (row/this->gridSize) * this->gridSize + (col/this->gridSize);
}

//Prints the board in specified ANSI color
void Board::printBoard(const std::string& color) {
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