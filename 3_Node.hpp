#pragma once
#include <stddef.h>
#include <iostream>
#include <string>
class Node;
class ColumnNode;

class Node {
   public:
    Node        *up;
    Node        *right;
    Node        *down;
    Node        *left;
    ColumnNode  *col;
    Node() {
        up = right = down = left = this;
        col     = nullptr;
    }
};

class ColumnNode : public Node {
   public:
    size_t size;
    size_t index;
    
    ColumnNode() {
        size    = 0;
        up = right = down = left = this;
    }
};

void cover(ColumnNode *c) {
    c->right->left = c->left;
    c->left->right = c->right;
    Node *i = c->down;
    while(i != c) {
        Node *j = i->right;
        while(j != i) {
            j->down->up = j->up;
            j->up->down = j->down;
            static_cast<ColumnNode*>(j->col)->size--;
            j = j->right;
        }
        i = i->down;
    }
}

void uncover(ColumnNode *c) {
    Node *i = c->up;
    while(i != c) {
        Node *j = i->left;
        while(j != i) {
            static_cast<ColumnNode*>(j->col)->size++;
            j->down->up = j;
            j->up->down = j;
            j = j->left;
        }
        i = i->up;
    }
    c->right->left = c;
    c->left->right = c;
}
