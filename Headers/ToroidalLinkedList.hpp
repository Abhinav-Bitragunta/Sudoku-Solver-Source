#pragma once
#include "Libraries.hpp"

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
    void            construct   (const size_t n, const ConstraintMatrix& M);
    ColumnNode*     listHead    ();
};