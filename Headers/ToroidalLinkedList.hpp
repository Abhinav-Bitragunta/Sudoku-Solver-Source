#pragma once
#include "Node.hpp"
#include "ConstraintMatrix.hpp"

class ToroidalLinkedList {
private:
    ColumnNode      *head;
    size_t          n;

private:
    void            createCols  ();
    
public:
    ~ToroidalLinkedList();
    ColumnNode*     construct   (size_t n, ConstraintMatrix& M);
};




