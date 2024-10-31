#pragma once
#include <stddef.h>
#include <iostream>
#include <string>
class Node;
class ColumnNode;
class ColData;

class Node {
   public:
    Node        *up;
    Node        *right;
    Node        *down;
    Node        *left;
    ColumnNode  *col;
    Node() {
        up      = this;
        right   = this;
        down    = this;
        left    = this;
        col     = nullptr;
    }
};

class ColData {
   public:
    int constraint;
    int number;
    int position;
    ColData() {
        constraint = number = position = -1;
    }
};

class ColumnNode : public Node {
   public:
    size_t size;
    ColData data;
    ColumnNode() {
        size    = 0;
        data    = ColData();
        up      = this;
        right   = this;
        down    = this;
        left    = this;
        col     = this;
    }
};

void cover(Node *c) {
    c->right->left = c->left;
    c->left->right = c->right;
    Node *i = c->down;
    while(i != c) {
        Node *j = i->right;
        while(j != i) {
            j->down->up = j->up;
            j->up->down = j->down;
            ((ColumnNode *)j->col)->size--;
            j = j->right;
        }
        i = i->down;
    }
    // std::cout << "Column covered.\n";
}

void uncover(Node *c) {
    Node *i = c->up;
    while(i != c) {
        Node *j = i->left;
        while(j != i) {
            ((ColumnNode *)j->col)->size++;
            j->down->up = j;
            j->up->down = j;
            j = j->left;
        }
        i = i->up;
    }
    c->right->left = c;
    c->left->right = c;
    // std::cout << "Column uncovered.\n";
}
