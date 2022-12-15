class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<pair<int, int>> graf[n];
        vector<int> distanta(n, 1e9);
        queue<vector<int>> q;
        for(auto f: flights){
            graf[f[0]].push_back({f[1], f[2]});
        }   
        q.push({0, src, 0});
        distanta[src] = 0;

        while(!q.empty()){
            int stop = q.front()[0];
            int node = q.front()[1];
            int finalCost = q.front()[2];
            q.pop();
            if(stop > k) continue;
            for(auto it: graf[node]){
                int nod = it.first;
                int price = it.second;
                if(finalCost + price < distanta[nod]) {
                    distanta[nod] = finalCost + price; 
                    q.push({stop+1, nod, finalCost + price});
                }
            }
        }
        if(distanta[dst] == 1e9)
            return -1;
        else return distanta[dst];
    }
};

//Aplicam Dijkstra clasic verificand in acelasi timp sa nu avem pasi > k
//Si alegem mereu drumul cu costul minim, actualizand in vectorul de cost(distanta) cand gasim un drum cu un cost mai mic
