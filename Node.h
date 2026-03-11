#ifndef NODE_H
#define NODE_H

#include <cstring>

class Node {
public:
    char data[20];
    Node* left;
    Node* right;
    Node* next;

    Node(const char* value) {
        strcpy(data, value);
        left = nullptr;
        right = nullptr;
        next = nullptr;
    }
};

#endif
