#pragma once
#include "Libraries.hpp"

#include "Board.hpp"
#include "Node.hpp"
#include "ConstraintMatrix.hpp"
#include "ToroidalLinkedList.hpp"

class Solver {
private:
    ColumnNode          *head;
    std::vector<int>    userInputBoard;
    Board               SolvedBoard;
    size_t              n;
    unsigned int        numSols;
    std::vector<Node*>  solution;
    std::array<std::vector<Node*>,10> allSolutions;

private:
    void                convertToBoard  (std::vector<Node*>& _solution);
    void                printSolutions  ();

    void                search          ();
    ColumnNode*         chooseColumn    ();
    void                cover           (ColumnNode* c);
    void                uncover         (ColumnNode* c);
    
    bool                userInput       ();

    size_t              getMemoryUsage  ();

public:
    void                launch          ();  
};