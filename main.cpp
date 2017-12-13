 
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
void readTownNumber(char*input,int &townNo){
    ifstream infile2(input);
    infile2>>townNo;
}
void read(char* input,Node vertices[]){
    ifstream infile(input);
    int n;
    infile>>n;
    int roads;
    int thieves;
    int jewelers;
    infile>>roads>>thieves>>jewelers;

    int town;//town id
    int coinNumber;
    int x;
    for(int i=0;i<jewelers;i++){
        infile>>town; //jewelerın olduğu town
        infile>>coinNumber; //coin sayısı
        for(int a=0;a<coinNumber;a++){
            infile>>x;
            vertices[town].coins[x]=1;
        }
    }

    for(int i=0;i<roads;i++){
        int begin;
        int end;
        int weigth;
        int thiefNumber;
        infile>>begin>>end>>weigth>>thiefNumber;
        Edge e1(begin,end,weigth);

        Edge e2(end,begin,weigth);

        for(int j=0;j<thiefNumber;j++){
            int thiefID;
            infile>>thiefID;
            e1.thieves[thiefID-1]=1;
            e2.thieves[thiefID-1]=1;
        }
        vertices[end].edges.push_back(e2);
        vertices[begin].edges.push_back(e1);
    }
}

bool isVisited(vector<int> vec,int finish){
    for(int i=0;i<vec.size();i++){
        if(vec[i]==finish)
            return true;
    }
    return false;
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

    priority_queue <Status,vector<Status>,compareDistance > q;

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
    vector<int> road;
    currentStatus.roadmap.insert(pair <int,vector<int>> (currentStatus.town,road) );
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
        if(!isVisited(currentStatus.roadmap[currentStatus.town],vertices[currentStatus.town].edges[i].finish)){

            if(vertices[currentStatus.town].edges[i].thieves.size()==0){
        Status s(vertices[currentStatus.town].edges[i].finish,vertices[currentStatus.town].edges[i].weigth+currentStatus.distance);
            s.path=currentStatus.path+to_string(vertices[currentStatus.town].edges[i].finish)+" ";
            bool isCoin=false;
                for(int j=1;j<14;j++){
                    if(vertices[s.town].coins[j]==1){
                        s.coins[j]=1;
                        isCoin=true;
                    }
                }
            if(isCoin){
                map <int,vector<int>> newMap;
                s.roadmap=newMap;
            } else{
                s.roadmap=currentStatus.roadmap;
                s.roadmap[currentStatus.town].push_back(s.town);
            }

            q.push(s);

        }

        else if(vertices[currentStatus.town].edges[i].thieves.size()!=0){

            set<int> thiefwants;
                for(int j=0;j<vertices[currentStatus.town].edges[i].thieves.size();j++){
                    if(vertices[currentStatus.town].edges[i].thieves[j]!=0)
                        thiefwants.insert(vertices[currentStatus.town].edges[i].thieves[j]);

                }


            bool enoughCoin=true;
            for (int item : thiefwants){
            if(currentStatus.coins[item]==0)
                enoughCoin=false;
            }
            if(enoughCoin){
                Status s2(vertices[currentStatus.town].edges[i].finish,vertices[currentStatus.town].edges[i].weigth+currentStatus.distance);
                bool isCoin2=false;
                for(int j=1;j<14;j++){
                    if(vertices[s2.town].coins[j]==1){
                        s2.coins[j]=1;
                        isCoin2=true;
                    }
                }
                if(isCoin2){
                    map <int,vector<int>> newMap;
                    s2.roadmap=newMap;
                } else{
                    s2.roadmap=currentStatus.roadmap;
                     s2.roadmap[currentStatus.town].push_back(s2.town);

                }

                s2.path=currentStatus.path+to_string(vertices[currentStatus.town].edges[i].finish)+" ";

                q.push(s2);
            }

        }
    }
        }
    }
    if(!isDone)
        myfile<<-1;

    return 0;
}

    


   
   
                
                   
