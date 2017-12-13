
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

    


   
   
                
                   
