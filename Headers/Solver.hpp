#pragma once
#include "Libraries.hpp"

#include "Board.hpp"
#include "Node.hpp"
#include "ConstraintMatrix.hpp"
#include "ToroidalLinkedList.hpp"

class Solver {
private:
    ColumnNode          *head;
    std::vector<Node*>  solution;
    Board               SolvedBoard;
    size_t              n;
    std::vector<int>    nums;
    std::vector<std::vector<Node*>> allSolutions;

private:
    void                convertToBoard  (std::vector<Node*>& _solution);
    void                printSolutions  ();

    void                search          ();
    ColumnNode*         chooseColumn    ();
    void                cover           (ColumnNode* c);
    void                uncover         (ColumnNode* c);
    
    bool                userInput       ();

public:
    void                launch          ();  
};

