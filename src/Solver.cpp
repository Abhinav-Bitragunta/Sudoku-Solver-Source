#include "Solver.hpp"

void Solver::launch() {
    Board                board;
    ToroidalLinkedList   L    ;
    
    this->allSolutions = std::array<std::vector<Node*>,solution_limit>();
    this->numSols      = 0;
    
    while(true) {
        while(!this->userInput()) {
            std::cout << "\033[31m Invalid board size detected, it must be a perfect square. \033[0m\n";
        }
        if(board.construct(this->userInputBoard)) break;
        std::cout << std::format("\033[31m Illegal board state. All values must be between 0 and {}, both inclusive. \033[0m\n", this->n);
    }
    this->solution.reserve(board.rowlength()*board.rowlength()); //to avoid unnecessary reallocation copies.
    

    auto t1 = std::chrono::high_resolution_clock::now();
    
    L.construct(board);
    this->listhead = L.listHead();

    auto t2 = std::chrono::high_resolution_clock::now();
    search();
    auto t3 = std::chrono::high_resolution_clock::now();
    
    auto d1 = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    auto d2 = std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count();

    if(this->numSols > 0) {
        this->printSolutions();
        std::cout << std::format("\033[1;32m{}\033[1m solution(s) found.\033[0m\n",this->numSols);

    } else {
        std::cout << "\033[31m No solutions found. \033[0m\n";
    }

    //black magic below
    std::cout << std::format("\nTime to \033[1;33mconstruct Toroidal Linked List\033[0m:\t\t\t\t\t\t   \033[34m{} microseconds.\033[0m", d1);
    std::cout << std::format("\nTime to find \033[1;33mALL solutions to the puzzle\033[0m, using \033[1;33mdancing links\033[0m(Search+Copy time):  \033[36m {} microseconds.\033[0m", d2);
    std::cout << std::format("\n\033[1;42mTotal time elapsed:                                                                {} microseconds.\033[0m\n", d1 + d2);  
    if(this->numSols > 1) std::cout << std::format("\033[1;33mAverage time\033[0m to find each solution to the puzzle:      \t                           \033[36m{} microseconds.\033[0m\n", static_cast<float>(1.0*d2/this->numSols));
}

//Algorithm X implementation.
void Solver::search() {
    if(listhead->right == listhead){
        this->allSolutions[this->numSols++] = this->solution;
        LOG("Solution " + std::to_string(numSols) + " found.");
        return;
    } 
    ColumnNode *c = chooseColumn();
    this->cover(c);
    Node *r = c->down;
    while(r != c) {
        solution.push_back(r);
        Node *j = r->right;
        while(j != r) {
            this->cover(j->col);
            j = j->right;
        }
        if(this->numSols < solution_limit) search();
        solution.pop_back();
        j = r->left;
        while(j != r) {
            this->uncover(j->col);
            j = j->left;
        }
        r = r->down;
    }
    this->uncover(c);
    return;
}

//Return pointer to column node with least number of vertical list nodes.
ColumnNode* Solver::chooseColumn() {
    ColumnNode *headRight   = static_cast<ColumnNode*>(this->listhead->right);
    ColumnNode *smallest    = headRight;
    while(headRight->right != this->listhead) {
        if(headRight->size < smallest->size) smallest = headRight;
        headRight   = static_cast<ColumnNode*>(headRight->right);
    }
    LOG("Column Node of index " + std::to_string(smallest->index) + " with " + std::to_string(smallest->size) + " \'option(s)\'chosen.");
    return smallest;
}

//Cover a column.
void Solver::cover(const ColumnNode *c) {
    c->right->left = c->left;
    c->left->right = c->right;
    Node *i = c->down;
    while(i != c) {
        Node *j = i->right;
        while(j != i) {
            j->down->up = j->up;
            j->up->down = j->down;
            static_cast<ColumnNode*>(j->col)->size--;
            j = j->right;
        }
        i = i->down;
    }
    LOG("Column of index " + std::to_string(c->index) + " covered");
}

//Uncover a column.
void Solver::uncover(ColumnNode *c) {
    Node *i = c->up;
    while(i != c) {
        Node *j = i->left;
        while(j != i) {
            static_cast<ColumnNode*>(j->col)->size++;
            j->down->up = j;
            j->up->down = j;
            j = j->left;
        }
        i = i->up;
    }
    c->right->left = c;
    c->left->right = c;
    LOG("Column of index " + std::to_string(c->index) + " uncovered");
}

//Decode Node* to index,value
void Solver::convertToBoard(std::vector<Node*>& _solution) {
    this->SolvedBoard = Board(this->n);
    for(auto* element : _solution) {
        int idx,val,constraintType;
        Node *next  = element;
        do {
            constraintType  = (next->col->index)/(n*n);
            
            if(constraintType == 0)     idx = next->col->index;
            else                        val = (next->col->index)%(this->n) + 1;
            
            next            = next->right;
        } while(element != next);

        SolvedBoard.set(idx,val);
    }
}

//Take input from user, return false on non-square length entries
bool Solver::userInput() {
    LOG("\n\033[31m!!! IMPORTANT !!!\033[0m App running in debug mode, which will cause a huge loss of performance, and is intended for the developers only.");
    LOG("To change this, go to Headers/Libraries.hpp and comment out the line \'#define DEBUG\', and run build.bat again.");
    std::cout << "\nEnter number of rows/columns in the Sudoku: ";
    std::cin >> this->n;

    if(int root = std::sqrt(this->n); root * root != this->n) return false;

    this->userInputBoard = std::vector<int>(this->n * this->n, 0);

    std::cout << std::format("\nThe number of solutions shown will be limited to {}.\n", solution_limit);
    std::cout << "\nPaste unsolved Sudoku:\n";
    for(int i = 0; i < this->n * this->n; i++) {
        std::cin >> this->userInputBoard[i];
    }

    return true;
}

void Solver::printSolutions(){
    size_t cnt = 0;
    for(auto& _solution : this->allSolutions){
        if(_solution.empty())    continue;
        this->convertToBoard(_solution);
        std::cout << std::format("\n\033[1mSolution {}:\033[0m\n", ++cnt);
        this->SolvedBoard.printBoard("\033[32m");
        std::cout << "\n";
    }
}