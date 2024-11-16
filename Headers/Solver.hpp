#pragma once
#include "Libraries.hpp"

#include "Board.hpp"
#include "Node.hpp"
#include "ToroidalLinkedList.hpp"

class Solver {
private:
    ColumnNode                          *listhead;
    std::vector<int>                    userInputBoard;
    Board                               SolvedBoard;
    size_t                              n;
    unsigned int                        numSols;
    std::vector<Node*>                  solution;
    std::array<std::vector<Node*>,10>   allSolutions;

private:
    void                convertToBoard  (std::vector<Node*>& _solution) ;
    void                printSolutions  ()                              ;

    void                search          ()                              ;
    ColumnNode*         chooseColumn    ()                              ;
    void                cover           (const ColumnNode* c)           ; //const for compiler optimizations.
    void                uncover         (ColumnNode* c)                 ;       
    
    bool                userInput       ()                              ;
                                 
public:                             
    void                launch          ()                              ;  
};