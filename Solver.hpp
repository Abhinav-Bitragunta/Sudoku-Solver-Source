#include <chrono>
#include <iostream>
#include "Board.hpp"
#include "ConstraintMatrix.hpp"
#include "ToroidalLinkedList.hpp"
#include "Node.hpp"

class Solver {
    ColumnNode          *head;
    std::vector<Node*>  solution;
    Board               SolvedBoard;
    size_t              n;
    size_t              N;
    std::vector<int>    nums;

   public:
    
    void                launch          ();
    void                solve           (Board& board);
    void                convertToBoard  ();
    
    bool                userInput       ();
    bool                search          ();
    
    ColumnNode*         chooseColumn    ();
};

void Solver::solve(Board& board) {
    
    auto t1 = std::chrono::high_resolution_clock::now();
    
    ConstraintMatrix M;
    ToroidalLinkedList L;
    M.construct(board);
    this->n             = board.rowlength();
    this->SolvedBoard   = Board(this->n);
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
    std::cout << std::format("\nTotal time elapsed:                                        \033[34m{} microseconds.\033[0m\n", d1 + d2);
    //L.destroy(); //why no work??? setting the destructor to call 
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
        if(search()) return true;
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

void Solver::convertToBoard() {
    std::vector<int> ans(this->n * this->n, -1);
    for(auto* element : this->solution) {
        int num = -1, cell = -1;
        Node* next = element;

        do {
            if(next->col->data.constraint == 0) {
                num = next->col->data.number;
            } else if(next->col->data.constraint == 3) {
                cell = next->col->data.position;
            }
            next = next->right;
        } while(element != next);

        ans[cell] = num;
    }
    this->SolvedBoard.construct(ans);
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

bool Solver::userInput() {
    std::cout << "\nEnter number of rows/columns in the Sudoku: ";
    std::cin >> this->N;

    if(int root = std::sqrt(this->N); root * root != this->N) return false;

    this->nums = std::vector<int>(N * N, 0);

    std::cout << "\nPaste unsolved Sudoku:\n";
    for(int i = 0; i < N * N; i++) {
        std::cin >> this->nums[i];
    }

    return true;
}

void Solver::launch() {
    Board b;
    while(true) {
        while(!this->userInput()) {
            std::cout << "\033[31m Invalid board size detected, it must be a perfect square. \033[0m\n";
        }
        if(b.construct(this->nums)) break;
        std::cout << std::format("\033[31m Illegal board state. All values must be between 0 and {}, both inclusive. \033[0m\n", this->N);
    }
    solve(b);
}