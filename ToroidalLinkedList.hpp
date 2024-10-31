#pragma once
#include "ConstraintMatrix.hpp"
#include "Node.hpp"

class ToroidalLinkedList {
    ColumnNode      *head;
    size_t          n;

   public:
    
    ColumnNode*     construct   (size_t n, ConstraintMatrix& M);
    void            createCols  ();
    void            destroy     ();
};


void ToroidalLinkedList::destroy() {
    if(this->head->right == this->head) {
        delete this->head;
        head = nullptr;
        return;
    }
    ColumnNode* current = static_cast<ColumnNode*>(this->head->right);
    ColumnNode* next;

    while(current != this->head) {
        next = static_cast<ColumnNode*>(current->right);

        Node* verticalCurrent   = current->down;
        while(verticalCurrent != current) {
            Node* nodeToDelete  = verticalCurrent;
            verticalCurrent     = verticalCurrent->down;
            delete nodeToDelete;
        }

        delete current;
        current = next;
    }
    delete this->head;
    head = nullptr;
    std::cout << "\nDestruction complete." << std::endl;
}

void ToroidalLinkedList::createCols() {
    size_t numCols      = 4 * n * n;
    ColumnNode* prev    = this->head;

    for(size_t col = 0; col < numCols; col++) {
        ColumnNode* temp = new ColumnNode;
        ColData& id = temp->data;

        if(col < 3 * n * n) {
            int digit = (col / (3 * n)) + 1;
            id.number = digit;
            int index = col - (digit - 1) * 3 * n;

            if(index < n) {
                id.constraint   = 0;
                id.position     = index;
            } else if(index < 2 * n) {
                id.constraint   = 1;
                id.position     = index - n;
            } else {
                id.constraint   = 2;
                id.position     = index - 2 * n;
            }
        } else {
            id.constraint       = 3;
            id.position         = col - 3 * n * n;
            id.number           = -1;
        }
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
        ColumnNode* columnHead = static_cast<ColumnNode*>(this->head->right);

        for(size_t col = 0; col < numcols; col++) {
            if(!M.at(row, col)) {
                columnHead  = static_cast<ColumnNode*>(columnHead->right);
                continue;
            }
            Node* temp      = new Node;
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
