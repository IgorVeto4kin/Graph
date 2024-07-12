#include <bits/stdc++.h>
using namespace std;
void DFS_walk(set <string> &visited, map<string, set<string>>& Graph, vector <string>& order , string temp_node, vector<string> &inwork, bool loop_found){
    visited.insert(temp_node);
    inwork.push_back(temp_node);
    for( auto& element : Graph[temp_node]){


        for(int i = 0; i<inwork.size(); ++i){
            if(inwork[i] == element){   
                loop_found = true;
                cout<<"Loop found, no RPO available"<<endl;
                for(int j = inwork.size()-1; j>=i; --j){
                    cout<<inwork[j]<<" ";
                }
                cout<<endl;
            }
        }

        if (visited.count(element) == 0 ){
            DFS_walk(visited,  Graph,  order , element, inwork, loop_found);
        }
        
    }
    if(loop_found == false){
        order.push_back(temp_node);
        inwork.pop_back();
    }

}
void RPO( map<string, set<string>>& Graph, string root) {
    set<string> visited;
    vector<string> inwork;
    bool loop_found = false;

    vector <string> order;
    DFS_walk(visited,  Graph,  order , root, inwork, loop_found);

    if(inwork.empty()){
        for(int i = order.size()-1; i>=0; --i){
            cout<<order[i]<<" ";
        }
        cout<<endl;
    }
    
}


int main(){
    string stuff;
    string root = "";
    map < string, set<string>> Graph;
    set<string> names;//for useful names check O(1) 
    cin>>stuff;
    while(stuff != "END"){
        if(stuff == "ADD_NODE"){//done
            string temp;
            cin>>temp;
            if(Graph.count(temp)==1){
                cout<< "Node with name "<<temp<<" is already exist"<<endl;
            }
            else{
                Graph[temp] = {};
            }
        }

        else if(stuff == "ADD_EDGE"){//done
            string departure, destination;
            cin>>departure>> destination;
            if(Graph.count(departure)==0 || Graph.count(destination)==0){
                cout<<"No such Node"<<endl;
            }
            else if(Graph[departure].count(destination) == 1){
                cout<<"such edge already exist"<<endl;
            }
            else{
                Graph[departure].insert(destination);
            }
        }

        else if(stuff == "REMOVE_NODE"){//done
            string temp;
            cin>>temp;
            if(Graph.count(temp) == 0){
                cout<<"No such Node"<<endl;
            }
            else{
                Graph.erase(temp);
                for (auto& pair : Graph){
                    pair.second.erase(temp);
                }
            }
        }

        else if(stuff == "REMOVE_EDGE"){//done
            string departure, destination;
            cin>>departure>> destination;
            if(Graph.count(departure)==0 || Graph.count(destination)==0){
                cout<<"No such Node"<<endl;
            }
            else if(Graph[departure].count(destination) == 0){
                cout<<"Such Node already removed"<<endl;
            }
            else{
                Graph[departure].erase(destination);
            }

        }

        else if(stuff == "ROOT"){//done
            string temp;
            cin>>temp;
            root = temp;
        }

        else if(stuff == "PRINT_RPO"){
            RPO(Graph, root);
        }

        cin>>stuff;



    }

}