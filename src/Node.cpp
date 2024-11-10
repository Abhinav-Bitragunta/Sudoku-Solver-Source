#include "Node.hpp"

//What up,right,down,left,col are initialized to only matters for the head pointer.
//Possible optimization would be to remove this constructor, and make only the head of toroidal linked list point to self.
Node::Node():
    up(this),
    right(this),
    down(this),
    left(this),
    col(nullptr){}

//Size 0 is necessary.
ColumnNode::ColumnNode():
    size(0){}