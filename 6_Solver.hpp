#include <chrono>
#include <iostream>
#include "2_Board.hpp"
#include "3_Node.hpp"
#include "4_ConstraintMatrix.hpp"
#include "5_ToroidalLinkedList.hpp"

class Solver {
    ColumnNode          *head;
    std::vector<Node*>  solution;
    Board               SolvedBoard;
    size_t              n;
    std::vector<int>    nums;

   public:
    
    void                launch          ();
    void                convertToBoard  ();
    
    bool                userInput       ();
    bool                search          ();
    
    ColumnNode*         chooseColumn    ();
};

void Solver::launch() {
    Board               board;
    ConstraintMatrix    M    ;
    ToroidalLinkedList  L    ;
    while(true) {
        while(!this->userInput()) {
            std::cout << "\033[31m Invalid board size detected, it must be a perfect square. \033[0m\n";
        }
        if(board.construct(this->nums)) break;
        std::cout << std::format("\033[31m Illegal board state. All values must be between 0 and {}, both inclusive. \033[0m\n", this->n);
    }
    
    
    auto t1 = std::chrono::high_resolution_clock::now();
    
    M.construct(board);
    this->head          = L.construct(this->n, M);

    auto t2 = std::chrono::high_resolution_clock::now();

    bool solveSuccess   = search();

    auto t3 = std::chrono::high_resolution_clock::now();
    
    auto d1 = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    auto d2 = std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count();

    if(solveSuccess) {
        this->convertToBoard();
        std::cout << "\033[32m\n Solution:\033[0m\n";
        this->SolvedBoard.printBoard("\033[32m");

    } else {
        std::cout << "\033[31m No solutions found. \033[0m\n";
    }
    
    //black magic below
    std::cout << std::format("\nTime to \033[1;33mconstruct Constraint matrix, Toroidal Linked List\033[0m: \033[34m{} microseconds.\033[0m", d1);
    std::cout << std::format("\nTime to \033[1;33msolve the puzzle\033[0m, using \033[1;33mdancing links\033[0m:             \033[36m{} microseconds.\033[0m", d2);
    std::cout << std::format("\n\033[1;42mTotal time elapsed:                                        {} microseconds.\033[0m\n", d1 + d2);  
}

bool Solver::search() {
    if(head->right == head) return true;
    ColumnNode* c = chooseColumn();
    cover(c);
    Node* r = c->down;
    while(r != c) {
        solution.push_back(r);
        Node* j = r->right;
        while(j != r) {
            cover(j->col);
            j = j->right;
        }
        if(search()){ //only want one solution.
            j = r->left;
            while(j != r) {
                uncover(j->col);
                j = j->left;
            }
            uncover(c);
            return true;
        }
        solution.pop_back();
        j = r->left;
        while(j != r) {
            uncover(j->col);
            j = j->left;
        }
        r = r->down;
    }
    uncover(c);
    return false;
}

ColumnNode* Solver::chooseColumn() {
    ColumnNode* headRight   = (ColumnNode*)this->head->right;
    ColumnNode* smallest    = headRight;
    while(headRight->right != this->head) {
        if(headRight->size < smallest->size) smallest = headRight;
        headRight   = (ColumnNode*)headRight->right;
    }
    return smallest;
}

void Solver::convertToBoard() {
    this->SolvedBoard = Board(this->n);
    for(auto* element : this->solution) {
        int idx,val;
        Node* next  = element;
        do {
            if(next->col->data.constraint == 1) {        //row-num constraint.
                val = next->col->data.number;
            } else if(next->col->data.constraint == 0) { //row-col constraint.
                idx = next->col->data.position;
            }
            next    = next->right;
        } while(element != next);

        SolvedBoard.set(idx,val);
    }
}

bool Solver::userInput() {
    std::cout << "\nEnter number of rows/columns in the Sudoku: ";
    std::cin >> this->n;

    if(int root = std::sqrt(this->n); root * root != this->n) return false;

    this->nums = std::vector<int>(this->n * this->n, 0);

    std::cout << "\nPaste unsolved Sudoku:\n";
    for(int i = 0; i < this->n * this->n; i++) {
        std::cin >> this->nums[i];
    }

    return true;
}
