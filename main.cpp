//
// Created by Merve İlik on 10/12/2017.
//
#include <queue>
#include <vector>
#include "Node.h"
#include "Edge.h"
#include "Status.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>
using namespace std;
template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc, char*argv[]){

    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    int n;
    int roads;
    int thieves;
    int jewelers;
    vector<string> words;
    split1(line,words);
    n=stoi(words[0]);
    roads=stoi(words[1]);
    thieves=stoi(words[2]);
    jewelers=stoi(words[3]);

    Node vertices[n+1];

    for(int i=0;i<jewelers;i++){
        int town;
        int coinNumber;
        int x;
        getline(infile,line);
        vector<string> words1;
        split1(line,words1);
        town=stoi(words1[0]);
        coinNumber=stoi(words1[1]);
        for(int a=0;a<coinNumber;a++){
            x=stoi(words1[a+2]);
            vertices[town].coins[x]=1;
        }
    }

    for(int i=0;i<roads;i++){
        int begin;
        int end;
        int weigth;
        int thiefNumber;
        getline(infile,line);
        vector<string> words2;

        split1(line,words2);
        begin=stoi(words2[0]);
        end=stoi(words2[1]);
        weigth=stoi(words2[2]);

        thiefNumber=stoi(words2[3]);

        Edge e1(begin,end,weigth);
        Edge e2(end,begin,weigth);

        for(int j=0;j<thiefNumber;j++){
            int thiefID;
            thiefID=stoi(words2[j+4]);
            e1.thieves.push_back(thiefID);
            e2.thieves.push_back(thiefID);
        }
        vertices[end].edges.push_back(e2);
        vertices[begin].edges.push_back(e1);
    }
    Status currentStatus(1,0);
    for(int a=0;a<14;a++){
        if(vertices[1].coins[a]!=0)
            currentStatus.coins[a]=1;
    }

    priority_queue <Status,vector<Status>,compareDistance > q;
    currentStatus.path="1 ";
    q.push(currentStatus);

    ofstream myfile(argv[2]);
    bool isDone=false;


      while(!q.empty()){

         currentStatus=q.top();
         q.pop();
         if(currentStatus.town==n){
             isDone=true;
             myfile<<currentStatus.path;
             break;
         }
         for(int i=0;i<vertices[currentStatus.town].edges.size();i++){

             Edge e=vertices[currentStatus.town].edges[i];

             vector<int> road={currentStatus.town,e.finish};
            if(e.thieves.size()==0){
                bool mapHasIt=true;
                if(currentStatus.roadmap.count(road)==0)
                    mapHasIt=false;
                if(!mapHasIt){
                    Status s(e.finish,e.weigth+currentStatus.distance);
                    s.path=currentStatus.path+to_string(e.finish)+" ";
                    for(int a=1;a<14;a++){
                        s.coins[a]=currentStatus.coins[a];
                    }
                    bool isCoin=false;
                    for(int b=1;b<14;b++){
                        if(currentStatus.coins[b]==0 && vertices[s.town].coins[b]==1){
                            s.coins[b]=1;
                            isCoin=true;
                            s.roadmap.clear();

                        }
                    }
                    if(!isCoin){
                        s.roadmap.insert(currentStatus.roadmap.begin(),currentStatus.roadmap.end());
                        s.roadmap.insert(make_pair(road,0));
                    }
                    q.push(s);
                }
            }

             else {

                bool canPassThief = true;
                for (int j = 0; j < e.thieves.size(); j++) {
                    if (currentStatus.coins[e.thieves[j]] == 0)
                        canPassThief = false;
                }

                if (canPassThief) {

                    bool mapHasIt = true;
                    if (currentStatus.roadmap.count(road) == 0)
                        mapHasIt = false;
                    if (!mapHasIt) {
                        Status s(e.finish,e.weigth + currentStatus.distance);
                        s.path = currentStatus.path + to_string(e.finish) + " ";
                        for (int a = 1; a < 14; a++) {
                            s.coins[a] = currentStatus.coins[a];
                        }
                        bool isCoin = false;
                        for (int b = 1; b < 14; b++) {
                            if (currentStatus.coins[b]==0 &&vertices[s.town].coins[b] == 1) {
                                s.coins[b] = 1;
                                isCoin = true;
                                s.roadmap.clear();
                            }
                        }
                        if (!isCoin) {
                            s.roadmap.insert(currentStatus.roadmap.begin(),currentStatus.roadmap.end());
                            s.roadmap.insert(make_pair(road, 0));
                        }
                        q.push(s);
                    }
                }
            }
         }
     }
//int visited[n][8192]={0};
    if(!isDone)
        myfile<<-1;

    return 0;
}



