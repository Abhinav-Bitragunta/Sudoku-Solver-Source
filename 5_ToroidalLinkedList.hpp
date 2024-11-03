#pragma once
#include "3_Node.hpp"
#include "4_ConstraintMatrix.hpp"

class ToroidalLinkedList {
    ColumnNode      *head;
    size_t          n;

    void            createCols  ();
    
   public:
    ~ToroidalLinkedList();
    ColumnNode*     construct   (size_t n, ConstraintMatrix& M);
};



ToroidalLinkedList::~ToroidalLinkedList() {
    ColumnNode *current = static_cast<ColumnNode*>(this->head->right);
    ColumnNode *next;
    int colCount = 0, verticalCount = 0, headCount = 0;

    while(current != this->head) {
        next = static_cast<ColumnNode*>(current->right);

        Node *verticalCurrent   = current->down;
        while(verticalCurrent != current) {
            Node *nodeToDelete  = verticalCurrent;
            verticalCurrent     = verticalCurrent->down;
            delete nodeToDelete;
            verticalCount++;
        }

        delete current;
        colCount ++;
        current = next;
    }
    delete this->head;
    headCount++;
    head = nullptr;
    std::cout << std::format("\nHeap memory freed. {} column nodes, {} vertical list nodes, and {} head node for a total of {} nodes destroyed.\n", colCount, verticalCount, headCount, colCount + verticalCount + headCount);
}

void ToroidalLinkedList::createCols() {
    size_t numCols      = 4 * n * n;
    ColumnNode *prev    = this->head;

    for(size_t col = 0; col < numCols; col++) {
        ColumnNode *temp = new ColumnNode;
        
        temp->index      = col;
        prev->right      = temp;
        temp->left       = prev;
        temp->right      = this->head;
        this->head->left = temp;
        prev             = temp;
    }
}

ColumnNode* ToroidalLinkedList::construct(size_t n, ConstraintMatrix& M) {
    this->n     = n;
    this->head = new ColumnNode;

    this->createCols();

    size_t numrows = M.getRows(), numcols = M.getCols();


    for(size_t row = 0; row < numrows; row++) {
        Node *prev = nullptr, *first = nullptr;
        ColumnNode *columnHead = static_cast<ColumnNode*>(this->head->right);

        for(size_t col = 0; col < numcols; col++) {
            if(!M.at(row, col)) {
                columnHead  = static_cast<ColumnNode*>(columnHead->right);
                continue;
            }
            Node *temp      = new Node;
            temp->up        = columnHead->up;
            temp->down      = columnHead;
            temp->col       = columnHead;
            temp->up->down  = temp;
            temp->down->up  = temp;
            if(prev) {
                prev->right = temp;
                temp->left  = prev;
                temp->right = first;
                first->left = temp;
            } else {
                first       = temp;
            }
            prev            = temp;
            columnHead->size++;
            columnHead      = static_cast<ColumnNode*>(columnHead->right);
        }
    }
    return this->head;
}
