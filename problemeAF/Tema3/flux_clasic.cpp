#include <fstream>
#include <bits/stdc++.h>
using namespace std;
ifstream f("maxflow.in");
ofstream g("maxflow.out");

int n, m, s, t, u, v, c;
vector <vector<int>> graf, capacitate;
vector<int> parinte, visited;

bool bfs() {
    parinte.assign(n + 1, 0);
    visited.assign(n + 1, 0);
    queue<int> q;
    q.push(s);
    visited[s] = 1;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (auto const &neighbor: graf[node]) {
            if (capacitate[node][neighbor] > 0 && !visited[neighbor]) {
                parinte[neighbor] = node;
                visited[neighbor] = 1;
                q.push(neighbor);
            }
            if (node == t)
                return true;
        }
    }
    return false;
}

int max_flow() {
    int maxFlow = 0;
    while (bfs()) {
        for (auto const &node: graf[n]) {
            if (capacitate[node][n] > 0 && visited[node]) {
                int minFlow = capacitate[node][n];
                int i = node;
                while (parinte[i]) {
                    minFlow = min(minFlow, capacitate[parinte[i]][i]);
                    i = parinte[i];
                }
                i = node;
                capacitate[node][n] -= minFlow;
                capacitate[n][node] += minFlow;
                while (parinte[i]) {
                    capacitate[parinte[i]][i] -= minFlow;
                    capacitate[i][parinte[i]] += minFlow;
                    i = parinte[i];
                }
                maxFlow += minFlow;
            }
        }
    }
    return maxFlow;
}

void findMinCut(){
    bfs(); // Parcurgem iar graful cu BFS pentru a vedea nodurile accesibile din nodul sursa
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (visited[i] && !visited[j] && graf[i][j]) // Afisam toate muchiile dintre un nod accesibil si un nod inaccesibil din sursa
                cout << i << " - " << j << '\n';
}

int main() {
    f >> n >> m;
    s = 1;
    t = n;
    graf.resize(n + 1);
    parinte.resize(n + 1);
    capacitate.resize(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; ++i) {
        f >> u >> v >> c;
        graf[u].push_back(v);
        graf[v].push_back(u);
        capacitate[u][v] = c;
    }
    cout << max_flow() << endl;
    findMinCut();
    return 0;
}


