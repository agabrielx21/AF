#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

ifstream f("C:\\Users\\Alex\\CLionProjects\\untitled\\cmake-build-debug\\date.in");

vector<vector<int>> graf;
vector<int> level;
vector<bool> visited;
int n, m,s ;


void read(){
    f>>n>>m;
    graf.resize(n+1);
    for(int i = 0; i < m; i++){
        int n1, n2;
        f>>n1>>n2;
        graf[n1].push_back(n2);
        graf[n2].push_back(n1);
    }

}

void afisareGraf(){
    for(int i=1; i<=n; i++) {
        for (auto &node: graf[i])
            cout << "(" << i << "," << node << ")\n";
    }
}

void bfs(int node) {
    visited[node] = true;
    queue<int> q;
    q.push(node);
    level[node] = 0;

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(auto v :graf[node]) {
            if(!visited[v]) {
                cout << node << " " << v << "\n";
                q.push(v);
                visited[v] = true;
                level[v] = 1 + level[node];
            }
        }
    }
}

int main(){
    read();
    vector<vector<int>> distante;
    int nodCurent = 1;
    level.assign(n+1, -1);
    visited.resize(n+1);
    f >> s;
    bfs(s);

//    afisareGraf();l
    return 0;
}
