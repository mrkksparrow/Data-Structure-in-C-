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
        void topologicalSort ();
        void topologicalSortUtil (stack <int>&, int);
        void tarjanInitialize (map <int, pair<int, int>>&, map<int, bool>&);
        void tarjanAlgoUtil (int, stack<int>&, map<int, pair<int, int>>&, map<int, bool>&);
        void tarjanAlgo ();
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

void Graph::topologicalSortUtil (stack <int>& topo, int temp){
    visited[temp] = true;
    auto it = nodemap.find(temp);
    for(auto &i : it->second){
        if (!visited[i]){
            topologicalSortUtil (topo, i);
        }
    }
    topo.push(temp);
}

void Graph::topologicalSort (){
    stack <int> topo;
    for (auto it=nodemap.begin(); it!=nodemap.end(); it++){
        if(!visited[it->first]){
            topologicalSortUtil (topo, it->first);
        }
    }

    while(!topo.empty()){
        cout<<topo.top()<<" ";
        topo.pop();
    }
    cout<<endl;
    /*
    stack <int> dfs;
    stack <int> shift;
    queue <int> topo;
    for (auto it=nodemap.begin(); it!=nodemap.end(); it++){
        if(!visited[it->first]){
            dfs.push(it->first);
            visited[it->first] = true;
            while(!dfs.empty()){
                int temp = dfs.top();
                dfs.pop();
                shift.push(temp);
                auto itr = nodemap.find(temp);
                for(auto &i : it->second){
                    if(!visited[i]){
                        visited[i] = true;
                        dfs.push(i);
                    }
                }
            }
            while(!shift.empty()){
                topo.push(shift.top());
                shift.pop();
            }
        }
    }
    while(!topo.empty()){
        cout<<topo.front()<<" ";
        topo.pop();
    }
    */
}

void Graph::tarjanInitialize (map <int, pair<int, int>>& ldmap, map<int, bool>& instack){
    for (auto it=nodemap.begin(); it!=nodemap.end(); it++){
        ldmap[it->first] = make_pair(-1, -1);
        instack[it->first] = false;
    }
}

void Graph::tarjanAlgoUtil (int temp, stack<int>& tarjan, map<int, pair<int, int>>& ldmap, map<int, bool>& instack){
    static int timer = 0;
    ldmap[temp] = make_pair(timer, timer);
    tarjan.push(temp);
    instack[temp] = true;
    timer++;

    auto it = nodemap.find(temp);
    for(auto &i : it->second){
        if(ldmap[i].first==-1){
            tarjanAlgoUtil(i, tarjan, ldmap, instack);
            ldmap[temp].second = min(ldmap[temp].second, ldmap[i].second);
        }
        else if(instack[i]){
            ldmap[temp].second = min(ldmap[temp].second, ldmap[i].first);
        }
    }

    if(ldmap[temp].second==ldmap[temp].first){
        while (tarjan.top()!=temp){
            cout<<tarjan.top()<<" ";
            instack[tarjan.top()] = false;
            tarjan.pop();
        }
        cout<<tarjan.top()<<endl;
        instack[tarjan.top()] = false;
        tarjan.pop();
    }
}

void Graph::tarjanAlgo (){
    stack <int> tarjan;
    map <int, pair<int, int>> ldmap;
    map <int, bool> instack;

    tarjanInitialize (ldmap, instack);
    for (auto it = ldmap.begin(); it!=ldmap.end(); it++){
        if(it->second.second==-1){
            tarjanAlgoUtil(it->first, tarjan, ldmap, instack);
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
            <<"5. Connected Components - Kosaraju"<<endl
            <<"6. Connected Components - Tarjan"<<endl
            <<"7. Get elements in level"<<endl
            <<"8. Topological Sort"<<endl
            <<"9. Display Graph"<<endl
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
                cout<<"Stongly Connected Component [Kosaraju] : "<<endl;
                root.initializeVisited ();
                root.kosarajuSCC ();
                break ;
            }

            case 6:{
                cout<<"Stongly Connected Component [Tarjan] : "<<endl;
                root.tarjanAlgo ();
                break ;
            }

            case 7:{
                cout<<"Enter the start node and final node to find its level [suggestion: 1 as start node] : "<<endl;
                int start, node;
                cin>>start>>node;
                root.initializeVisited ();
                root.levelOrder (start, node);
                break ;
            }

            case 8:{
                cout<<"Topological Sort of the Graph : \t";
                root.initializeVisited ();
                root.topologicalSort ();
                break ;
            }

            case 9:{
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
