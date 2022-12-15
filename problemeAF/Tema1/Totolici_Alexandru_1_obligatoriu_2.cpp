#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
int permutari[100001],order[100001],ord[100001];
int n1,n2,n,m,element,ind=0;
bool visited[100001];

void read(){
    cin>>n>>m;
    for(int i=0; i<n; i++){
        cin>>element;
        permutari[i] = element;
        ord[permutari[i]] = i;
    }
    adj.resize(n+1);
    for(int i=0; i<m; i++){
        cin>>n1>>n2;
        adj[n1].push_back(n2);
        adj[n2].push_back(n1);
    }
}


void dfs(int root){
    visited[root] = true;
    order[ind++] = root;
    for(int i=0;i<adj[root].size();i++) {
        if (!visited[adj[root][i]])
            dfs(adj[root][i]);
    }
}

bool cmp(int a, int b) {
    return ord[a] < ord[b];
}


int main(){
    read();
    for(int i = 0; i < adj.size(); ++i)
        sort(adj[i].begin(), adj[i].end(), cmp);
    dfs(1);
    bool ok = true;
    for(int i = 0; i < n; ++i)
        if(permutari[i] != order[i]) {
            ok = false;
            break;
        }
    cout << ok;
    }

