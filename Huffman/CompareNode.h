#pragma once

#include "Node.h"

struct CompareNode {
    bool operator()(Node* a, Node* b) const {
        return a->frequency > b->frequency; // min-heap
    }
};

