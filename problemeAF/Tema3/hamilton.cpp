class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph){
        int n = graph.size();
        int mascaFinala = (1<<n)-1;
        queue<pair<int,pair<int,int>>>q;
        set<pair<int,int>>seen;
        for(int i=0;i<n;i++){
            q.push({i,{0,1<<i}});
            seen.insert({i,1<<i});
        }
        while(!q.empty()){
            auto curr = q.front();
            q.pop();
            int node = curr.first, dist = curr.second.first, mask = curr.second.second;
            if(mask==mascaFinala)
                return dist;
            for(auto &vecin:graph[node]){
                int nextMask = mask | (1<<vecin);
                if(not seen.count({vecin,nextMask})){
                    q.push({vecin,{dist+1,nextMask}});
                    seen.insert({vecin,nextMask});
                }
            }
        }
        return 0;
    }
};