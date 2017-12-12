//
// Created by Merve İlik on 10/12/2017.
//
using namespace std;
#include <vector>


#ifndef PROJECT3_MERVE_ILIK_2015400006_MASTER_EDGE_H
#define PROJECT3_MERVE_ILIK_2015400006_MASTER_EDGE_H
class Edge{
public:
    int start;
    int finish;
    int weigth;
    vector<int> thieves;
    Edge(int from,int to,int weigth);

};

#endif //PROJECT3_MERVE_ILIK_2015400006_MASTER_EDGE_H
