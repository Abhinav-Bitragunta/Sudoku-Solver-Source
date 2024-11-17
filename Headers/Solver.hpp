#pragma once
#include "Libraries.hpp"

#include "Board.hpp"
#include "Node.hpp"
#include "ToroidalLinkedList.hpp"

const int solution_limit = 10;  //Can't make user input if std::array is to be used

class Solver {
private:
    ColumnNode                          *listhead;
    std::vector<int>                    userInputBoard;
    Board                               SolvedBoard;
    size_t                              n;
    unsigned int                        numSols;
    std::vector<Node*>                  solution;
    std::array<std::vector<Node*>,solution_limit>   allSolutions;

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