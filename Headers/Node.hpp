#pragma once
#include "Libraries.hpp"

class Node;
class ColumnNode;

class Node {
public:
    Node        *up;
    Node        *right;
    Node        *down;
    Node        *left;
    ColumnNode  *col;

public:
    Node();
};


class ColumnNode : public Node {
public:
    size_t size;
    size_t index;

public:
    ColumnNode();
};