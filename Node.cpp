//
// Created by Merve İlik on 10/12/2017.
//
#include "Node.h"



    Node::Node(){
        coins=new bool[14];
        for(int i=0;i<=13;i++)
            coins[i]=0;
    }

