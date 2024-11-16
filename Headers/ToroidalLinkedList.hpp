#pragma once
#include "Libraries.hpp"

#include "Node.hpp"
#include "Board.hpp"

class ToroidalLinkedList {
private:
    ColumnNode               *head;
    size_t                   n;
    std::vector<ColumnNode*> colNodes;

private:
    void            createCols  ();
    
public:
    ~ToroidalLinkedList();
    void            construct   (const Board& B);
    ColumnNode*     listHead    ();
};