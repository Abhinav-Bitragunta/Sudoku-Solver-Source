#include "Node.hpp"

//Default constructor
Node::Node():
    up(this),
    right(this),
    down(this),
    left(this),
    col(nullptr){}

//Size 0 is necessary.
ColumnNode::ColumnNode():
    size(0){}