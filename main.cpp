#include <bits/stdc++.h>
using namespace std;
struct Node{
    string name;
    set<string> successors;
};

struct Graph{
    vector <struct Node> body;

    int find(string some_node_name){//сheck, if node with name "some_node_name" is already exists
        for(int i = 0; i < body.size(); ++i){
            bool temp = (body[i].name == some_node_name);
            if(temp){
                return i;
            }
        }
        return -1;

    }

    void add_node(string some_node_name){
        struct Node new_node;
        new_node.name = some_node_name;
        new_node.successors = {};
        body.push_back(new_node);
    }
    
    void add_edge(string departure, string destination ){
        this->body[this->find(departure)].successors.insert(destination);
    }

    void remove_node(string node_name){
        int num = this->find(node_name);
        this->body.erase(body.begin()+num);
        for(int i = 0; i<body.size(); ++i){
            this->body[i].successors.erase(node_name);
        }
    }

    void DFS_walk(set <string> &visited, vector <string>& order, int temp_node, vector <string>& in_work){
        visited.insert(this->body[temp_node].name);
        in_work.push_back(this->body[temp_node].name);

        for ( auto& element : this->body[temp_node].successors  ){
            for(int i = 0; i<in_work.size(); ++i){
            if(in_work[i] == element){   
                cout<<"Loop found"<<endl;
                for(int j = in_work.size()-1; j>=i; --j){
                    cout<<in_work[j]<<" ";
                }
                cout<<endl;
            }
        }
            if(visited.count(element) == 0){
                DFS_walk(visited, order, this->find(element), in_work);
            }
        }
        order.push_back(this->body.at(temp_node).name);
        in_work.pop_back();
    }

    void RPO_cout(int root_node){
        set <string> visited;
        vector <string> order;
        vector<string> in_work; // such stack for catching loops
        DFS_walk(visited, order, root_node, in_work);
        cout<<"RPO-enumeration"<<endl;
        for(int i = order.size(); i>=0; --i){
            cout <<order[i]<<" ";

        }
        cout<<"\n";

    }
};

int main(){
    struct Graph main_graph;
    string stuff;
    int root = 0;
    
    cin>>stuff;
    while(stuff != "END"){
        if(stuff == "ADD_NODE"){//done
            string temp;
            cin>>temp;
            if(main_graph.find(temp)!= -1){
                cout<< "Node with name "<<temp<<" is already exist"<<endl;
            }
            else{
                main_graph.add_node(temp);
            }
        }

        else if(stuff == "ADD_EDGE"){//done
            string departure, destination;
            cin>>departure>> destination;
            if( main_graph.find(departure) == -1 || main_graph.find(destination) == -1){
                cout<<"No such Node"<<endl;
            }
            else if(main_graph.body[main_graph.find(departure)].successors.count(destination) == 1){
                cout<<"such edge already exist"<<endl;
            }
            else{
                main_graph.add_edge(departure, destination);
            }
        }

        else if(stuff == "REMOVE_NODE"){//done
            string temp;
            cin>>temp;
            if(main_graph.find(temp) == -1){
                cout<<"No such Node"<<endl;
            }
            else{
                main_graph.remove_node(temp);
            }
        }
        
        else if(stuff == "REMOVE_EDGE"){//done
            string departure, destination;
            cin>>departure>> destination;
            if(main_graph.find(departure) == -1 || main_graph.find(destination) == -1){
                cout<<"No such Node"<<endl;
            }
            else if(main_graph.body[main_graph.find(departure)].successors.count(destination) == 0){
                cout<<"Such Node already removed"<<endl;
            }
            else{
                main_graph.body[main_graph.find(departure)].successors.insert(destination);
            }

        }

        else if(stuff == "ROOT"){//done
            string temp;
            cin>>temp;
            root = main_graph.find(temp);
        }

        else if(stuff == "PRINT_RPO"){
            main_graph.RPO_cout(root);
        }

        cin>>stuff;



    }
}