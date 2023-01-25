class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        int m = pairs.size();
        unordered_map<int, stack<int>> adj;
        unordered_map<int, int> in;
        unordered_map<int, int> out;

        adj.reserve(m);
        in.reserve(m);
        out.reserve(m);

        for (int i = 0; i < m; i++) {
            int u = pairs[i][0], v = pairs[i][1];
            in[v]++;
            out[u]++;
            adj[u].push(v);
        }

        int start = -1;
        for (auto& p : adj) {
            int i = p.first;
            if (out[i] - in[i] == 1) start = i;
        }
        if (start == -1) {
            start = adj.begin()->first;
        }
        vector<vector<int>> ans;
        solve(adj, ans, start);
        reverse(ans.begin(), ans.end());
        return ans;
    }
private:
    void solve(unordered_map<int, stack<int>>& adj, vector<vector<int>>& ans, int nod) {
        auto& s = adj[nod];
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            solve(adj, ans, v);
            ans.push_back({nod, v});
        }
    }
};