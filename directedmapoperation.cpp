#include <bits/stdc++.h>
using namespace std;

class Graph {
    public :
        int no_vertex;
        int no_edge;
        map <int, vector<int> > nodemap;
        map <int, int> level;
        map <int, bool> visited;

        Graph ();
        int addVertex (int);
        void addEdge (int, int);
        void initializeVisited ();
        void DFS (int);
        void BFS (int);
        void levelOrder (int, int);
        void kosarajuSCC ();
        void DFSutil (int, map<int, vector<int>>&);
        void displayGraph ();

};
//map<int, vector<int>>::iterator itr;

Graph::Graph (){
    cout<<"Enter no of vertex : \t";
    cin>>no_vertex;
    cout<<"Enter no of edges : \t";
    cin>>no_edge;
}

int Graph::addVertex (int vertex){
    if(nodemap.find(vertex)!=nodemap.end()){
        cout << "Vertex already exist" << endl;
        return 0;
    }
    nodemap[vertex];
    visited[vertex] = false;
    return 1;
}

void Graph::initializeVisited (){
    for(map<int, bool>::iterator i = visited.begin(); i!=visited.end(); i++){
        i->second = false;
    }
}

void Graph::addEdge (int vertex, int edge){
    nodemap[vertex].push_back(edge);
}

void Graph::DFS (int startnode){
    if (nodemap.find(startnode) == nodemap.end()){
        cout<<startnode<<" is not found in graph"<<endl;
        return ;
    }
    stack <int> stc;
    stc.push(startnode);
    visited[startnode] = true;

    while(!stc.empty()){
        int temp = stc.top();
        cout<<temp<<" ";
        stc.pop();

        auto it = nodemap.find(temp);
        for (auto &i : it->second){
            if(!visited[i]){
                visited[i] = true;
                stc.push(i);
            }
        }
    }
    cout<<endl;
}

void Graph::BFS (int startnode){
    if (nodemap.find(startnode) == nodemap.end()){
        cout<<startnode<<" is not found in graph"<<endl;
        return ;
    }
    queue <int> que;
    que.push(startnode);
    visited[startnode] = true;

    while(!que.empty()){
        int temp = que.front();
        visited[temp] = true;
        cout<<temp<<" ";
        que.pop();

        auto it = nodemap.find(temp);
        for (auto &i : it->second){
            if(!visited[i]){
                visited[i] = true;
                que.push(i);
            }
        }
    }
    cout<<endl;
}

void Graph::levelOrder (int start, int vertex){
    queue <int> que;
    que.push(start);
    level[start] = 1;

    while(!que.empty()){
        int temp = que.front();
        visited[temp] = true;
        que.pop();

        auto it = nodemap.find(temp);
        for(auto &i : it->second){
            if(!visited[i]){
                level[i] = level[temp]+1;
                visited[i] = true;
                que.push(i);
            }
        }
    }

    cout<<"Level of vertex "<<vertex<<": "<<level[vertex]<<endl;
}

void Graph::DFSutil (int temp, map<int, vector<int>>& reversemap){
    visited[temp] = true;
    cout<<temp<<" ";
    auto it = reversemap.find(temp);
    for (auto &i : it->second){
        if(!visited[i]){
            DFSutil(i, reversemap);
        }
    }
}

void Graph::kosarajuSCC (){
    //stack <int> kosaraju;
    queue <int> kosaraju;
    stack <int> dfs;

    dfs.push(0);
    visited[0] = true;
    while(!dfs.empty()){
        kosaraju.push(dfs.top());
        int temp = dfs.top();
        dfs.pop();

        auto it = nodemap.find(temp);
        for(auto &i : it->second){
            if(!visited[i]){
                visited[i] = true;
                dfs.push(i);
            }
        }
    }

    map <int, vector<int>> reversemap;
    for(auto it=nodemap.begin(); it!=nodemap.end(); it++){
        for(auto &i : it->second){
            reversemap[i].push_back(it->first);
        }
    }
    initializeVisited();
    /*
    while(!kosaraju.empty()){
        int temp = kosaraju.front();
        kosaraju.pop();
        if(!visited[temp]){
            dfs.push(temp);
            while(!dfs.empty()){
                int x = dfs.top();
                dfs.pop();
                visited[x] = true;
                if(visited[x]) cout<<x<<" ";
                auto it = reversemap.find(x);
                for(auto &i : it->second){
                    if(!visited[i]){
                        visited[i] = true;
                        dfs.push(i);
                    }
                }
            }
            cout<<endl;
        }
    }
    */
    while(!kosaraju.empty()){
        int temp = kosaraju.front();
        kosaraju.pop();
        if(!visited[temp]){
            DFSutil(temp, reversemap);
            cout<<endl;
        }
    }
}

void Graph::displayGraph (){
    for (auto it=nodemap.begin(); it!=nodemap.end(); it++){
        cout<<it->first<<" -> ";
        for(auto &i : it->second){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}

int main (){
    Graph root;
    cout<<"Enter the vertex value for "<< root.no_vertex <<" vertices : "<<endl;
    for (int i=0; i<root.no_vertex; i++){
        int vertex;
        cin >> vertex;
        root.addVertex (vertex);
    }
    cout<<"Enter "<< root.no_edge <<" edge connections for "<< root.no_vertex <<" vertices : "<<endl;
    for (int i=0; i<root.no_edge; i++){
        int vertex, edge;
        cin >> vertex >> edge;
        root.addEdge (vertex, edge);
    }
    int choice;
    do{
        cout<<"Choose any one operation : "<<endl
            <<"1. Add Vertex"<<endl
            <<"2. Add Edge connection"<<endl
            <<"3. Depth First Search"<<endl
            <<"4. Breath First Search"<<endl
            <<"5. Connected Components"<<endl
            <<"6. Get elements in level"<<endl
            <<"7. Display Graph"<<endl
            <<"0. Exit"<<endl;

        cin >> choice;

        switch (choice){
            case 1:{
                cout<<"Enter a new vertex for the graph : \t";
                int vertex;
                cin >> vertex;
                if (root.addVertex (vertex)) root.no_vertex++;
                break ;
            }

            case 2:{
                cout<<"Enter a new edge connections for "<< root.no_vertex <<" vertices : "<<endl;
                int vertex, edge;
                cin >> vertex >> edge;
                root.addEdge (vertex, edge);
                break ;
            }

            case 3:{
                cout<<"Enter start node for doing DFS \t";
                int startnode;
                cin>>startnode;
                root.initializeVisited ();
                cout<<"Depth First Search Traversal : "<<endl;
                root.DFS (startnode);
                break ;
            }

            case 4:{
                cout<<"Enter start node for doing BFS \t";
                int startnode;
                cin>>startnode;
                root.initializeVisited ();
                cout<<"Breath First Search Traversal : "<<endl;
                root.BFS (startnode);
                break ;
            }

            case 5:{
                root.initializeVisited ();
                root.kosarajuSCC ();
                break ;
            }

            case 6:{
                cout<<"Enter the start node and final node to find its level [suggestion: 1 as start node] : "<<endl;
                int start, node;
                cin>>start>>node;
                root.initializeVisited ();
                root.levelOrder(start, node);
                break ;
            }

            case 7:{
                cout<<"Graph nodes and their connection : "<<endl;
                root.displayGraph ();
                break ;
            }

            case 0:{
                cout<<"Thank you, Have a great day "<<endl;
                break ;
            }
        }
    } while (choice != 0);
    return 0;
}
/*  Graph structure : 

    | 1 |--> | 0 |--> | 3 |
     /|\    /           |
      |    /            |
      |   /             |
      | !/_            \|/
    | 2 |             | 4 |

vertex no : 5
edge no : 5

connection for 5 edge from a->b (edge*2 = 10) :

1
0
0
2
2
1
0
3
3
4

*/
