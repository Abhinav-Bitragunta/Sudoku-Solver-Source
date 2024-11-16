#include "ToroidalLinkedList.hpp"

//Construct Toroidal linked list from given constraint matrix.
void ToroidalLinkedList::construct(const Board& B) {
    this->n         = B.rowlength();
    size_t gridSize = B.gridsize();
    this->head      = new ColumnNode;

    this->createCols();
    LOG("Column headers created successfully.");
/*    
    Indices 0     - n^2-1  : Individual cell constraints (row-col intersection)
    Indices n^2   - 2*n^2-1: Row    number   constraints
    Indices 2*n^2 - 3*n^2-1: Column number   constraints
    Indices 3*n^2 - 4*n^2-1: Grid   number   constraints
    
    For a 9x9 Sudoku this translates to 0-80, 81-161, 162-242, 243-323.
*/
    for(size_t row = 0; row < n; row++){
        for(size_t col = 0; col < n; col++){
            size_t gridnum = (row / gridSize) * gridSize + (col / gridSize);

            for(size_t val = 0; val < n; val++){
                
                if(B.unsafe(row,col,val+1)) continue;
                size_t  RCidx   = row     * n   + col             , //constr 0: row-col
                        RVidx   = row     * n   + val + n * n     , //constr 1: row-val
                        CVidx   = col     * n   + val + 2 * n * n , //constr 2: col-val
                        GVidx   = gridnum * n   + val + 3 * n * n ; //constr 3: grid-val
                
                Node *a = new Node, *b = new Node, *c = new Node, *d = new Node;
                
                a->right = b; a->left = d;
                b->right = c; b->left = a;
                c->right = d; c->left = b;
                d->right = a; d->left = c;

                a->col   = this->colNodes[RCidx];
                b->col   = this->colNodes[RVidx];
                c->col   = this->colNodes[CVidx];
                d->col   = this->colNodes[GVidx];

                for( Node *x : {a, b, c, d} ) {
                    x->col->size++;
                    x->up       = x->col->up;
                    x->down     = x->col;
                    x->up->down = x;
                    x->down->up = x;
                }
            }
        }
    }
    LOG("Toroidal linked list created successfully.");
}

void ToroidalLinkedList::createCols() {
    size_t numcols        = 4*this->n*this->n;
    this->colNodes        = std::vector<ColumnNode*>(numcols);

    for(int i = 0; i < numcols; i++){
        this->colNodes[i] = new ColumnNode();
        this->colNodes[i]->index = i;
    }

    for(size_t col = 1; col < numcols; col++){
        this->colNodes[col]->left    = this->colNodes[col-1];
        this->colNodes[col-1]->right = this->colNodes[col];
    }

    this->head->right       = this->colNodes[0];
    this->head->left        = this->colNodes[numcols-1];
    this->colNodes[0]->left = this->colNodes[numcols-1]->right = this->head;
}

//Return pointer to head of the linked list.
ColumnNode* ToroidalLinkedList::listHead()      {return this->head;}

//Free memory after execution.
ToroidalLinkedList::~ToroidalLinkedList() {
    LOG("Linked list destructor called");
    int colCount = 0, verticalCount = 0, headCount = 0;

    for(ColumnNode* columnheader: this->colNodes){
        colCount++;
        Node *listNode  = columnheader->down;
        while(listNode != columnheader){
            listNode    = listNode->down;
            delete listNode->up;
            verticalCount++;
        }
        delete columnheader;
    }
    delete this->head;
    headCount++;

    std::cout << std::format("\nHeap memory freed. {} column nodes, {} vertical list nodes, and {} head node for a total of {} nodes destroyed.\n", colCount, verticalCount, headCount, colCount + verticalCount + headCount);
    std::cout << std::format("Memory taken by the data structures: {:.2f} KB.\n", ((headCount+colCount)*sizeof(ColumnNode) + verticalCount*sizeof(Node))/1024.0);
}