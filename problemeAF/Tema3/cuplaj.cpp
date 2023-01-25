#include <bits/stdc++.h>
using namespace std;

ifstream f("cuplaj.in");
ofstream g("cuplaj.out");

int leftSize, rightSize, edges, s, sink;

vector<bool> corespondent;
vector<pair<int, int>> parinte;
vector<pair<int, int>> rightNodes;
vector<vector<pair<int, pair<int, int>>>> graf;
queue<int> q;

bool bfs() {
    vector<bool> visited(sink + 1);
    q.push(s);
    visited[s] = true;
    parinte[s] = {-1, -1};

    while (!q.empty()) {
        int nodCurent = q.front();
        q.pop();
        if (nodCurent == sink) continue;

        int c = 0;
        for (auto node: graf[nodCurent]) {
            int a, b;
            a = node.first;
            b = node.second.first;
            if (!visited[a] && b) {
                parinte[a] = {nodCurent, c};
                visited[a] = true;
                q.push(a);
            }
            c++;
        }
    }
    return visited[sink];
}

long int maxFlow() {

    long int max_flow = 0;

    while (bfs()) {
        for (auto node: rightNodes) {
            int u, v, x, y, min_path = 1;
            parinte[sink] = node;
            v = sink;
            while (parinte[v].first != -1) {
                u = parinte[v].first;
                x = parinte[v].second;
                min_path = min(min_path, graf[u][x].second.first);
                v = u;
            }
            v = sink;
            while (parinte[v].first != -1) {
                u = parinte[v].first;
                x = parinte[v].second;
                y = graf[u][x].second.second;
                graf[u][x].second.first -= min_path;
                graf[v][y].second.first += min_path;
                v = u;
            }
            max_flow += min_path;
        }
    }
    return max_flow;
}

void adaugaM(int u, int v) {
    graf[u].push_back({v, {1, graf[v].size()}});
    graf[v].push_back({u, {0, graf[u].size() - 1}});
    if (v == sink)
        rightNodes.emplace_back(u, graf[u].size() - 1);
}

int main() {

    f >> leftSize >> rightSize >> edges;

    s = 0;
    sink = leftSize + rightSize + 1;

    corespondent.resize(rightSize + 1);
    parinte.resize(sink + 1);
    graf.resize(sink + 1);

    for (int i = 1; i <= leftSize; i++)
        adaugaM(s, i);

    for (int i = 1; i <= edges; i++) {
        int u, v;
        f >> u >> v;
        adaugaM(u, leftSize + v);
        corespondent[v] = true;
    }

    for (int i = 1; i <= rightSize; i++) {
        if (corespondent[i])
            adaugaM(leftSize + i, sink);
    }

    g << maxFlow() << '\n';
    for (int u = 1; u <= leftSize; u++)
        for (auto node: graf[u]) {
            int v, c;
            v = node.first;
            c = node.second.first;
            if (v && c == 0 && v != sink)
                g << u << " " << v - leftSize << '\n';
        }
    return 0;
}