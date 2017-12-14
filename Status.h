//
// Created by Merve İlik on 10/12/2017.
//

#ifndef PROJECT3_MERVE_ILIK_2015400006_MASTER_STATUS_H
#define PROJECT3_MERVE_ILIK_2015400006_MASTER_STATUS_H

#endif //PROJECT3_MERVE_ILIK_2015400006_MASTER_STATUS_H
using namespace std;
#include <set>
#include <vector>
#include <string>
class Status{
public:
    int town;
    int distance;
    string path;
    bool coins[14];
    Status(int town,int distance);
};

struct compareDistance{
public:
    bool operator()(Status const &s1, Status const &s2){
        return s1.distance>s2.distance;
    }
};
