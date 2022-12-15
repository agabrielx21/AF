class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {

    vector<pair<int, float>> graf[100000];
    priority_queue<pair<double,int>> p;
    vector<double> dist(n,0.0);

    for(int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            graf[u].push_back({v,succProb[i]});
            graf[v].push_back({u,succProb[i]});
        }
    
    p.push({1.0,start});
    dist[start]=1.0;

    while(!p.empty()){
        double cost=p.top().first;
        int node=p.top().second;
        p.pop();
        for(auto u:graf[node]){
            if(dist[u.first]<u.second*cost){
                dist[u.first]=u.second*cost;
                p.push({dist[u.first],u.first});
            }
        }
    }
    
    // Aplicam Dijkstra clasic pt a afla distanta de la start la end 
    // cu conditia de actualizare a distantei diferita ( alegem costul maxim, inmultind costurile muchiilor prin care se ajunge )
    return dist[end];
    }
};
