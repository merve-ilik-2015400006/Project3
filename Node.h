//
// Created by Merve İlik on 10/12/2017.
//

#ifndef PROJECT3_MERVE_ILIK_2015400006_MASTER_NODE_H
#define PROJECT3_MERVE_ILIK_2015400006_MASTER_NODE_H
using namespace std;
#include <vector>
#include "Edge.h"
class Node{
public:
    vector<Edge> edges;
    bool *coins;

    Node();
};
#endif //PROJECT3_MERVE_ILIK_2015400006_MASTER_NODE_H
