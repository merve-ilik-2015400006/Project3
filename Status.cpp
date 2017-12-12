//
// Created by Merve İlik on 10/12/2017.
//
#include "Status.h"
#include <vector>
#include <string>

    Status::Status(int _town,int _distance){
        town=_town;
        distance=0;
        path="";
        for(int i=0;i<=13;i++){
            coins[i]=0;
        }
    }


