//
// Created by Merve İlik on 10/12/2017.
//
#include "Status.h"
#include <vector>
#include <string>
using namespace std;

    Status::Status(int _town,int _distance){
        town=_town;
        distance=_distance;
        path="";
        coins=new bool[14];
        for(int i=0;i<=13;i++){
            coins[i]=false;
        }
    }


