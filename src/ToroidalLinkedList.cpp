#include "ToroidalLinkedList.hpp"

//Construct Toroidal linked list from given constraint matrix.
void ToroidalLinkedList::construct(const size_t n, const ConstraintMatrix& M) {
    this->n     = n;
    this->head = new ColumnNode;

    this->createCols();
    LOG("Column headers created successfully.");

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
    LOG("Toroidal linked list created successfully.");
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

//Return pointer to head of the linked list.
ColumnNode* ToroidalLinkedList::listHead()      {return this->head;}

//Free memory after execution.
ToroidalLinkedList::~ToroidalLinkedList() {
    LOG("Linked list destructor called");
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
    std::cout << std::format("Memory taken by the data structures: {:.2f} KB.\n", ((headCount+colCount)*sizeof(ColumnNode) + verticalCount*sizeof(Node) + (n*n*n*n*n*0.5f))/1024.0);
}

/*
        Memory usage calculation:
            Since the constraint matrix and toroidal linked list have a space complexity of O(n^5), and since everything else is limited to O(n^2) max, we're only counting those both.

            The cryptic "(n*n*n*n*n*0.5f)" is the memory used in bytes by the constraint matrix.
            It has n^3 rows and 4n^2 columns, for a total of 4n^5 booleans stored.
            std::vector<bool> uses only one bit to store a boolean value (using bitfields) unlike the standard 1 byte taken by bool.
            Therefore, 4n^5 bits * 1/8 = 0.5*n^5 bytes.

            The rest should be self explanatory.

*/