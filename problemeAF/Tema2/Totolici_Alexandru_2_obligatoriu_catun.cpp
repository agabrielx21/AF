#include <bits/stdc++.h>

using namespace std;

ifstream f("catun.in");
ofstream g("catun.out");

int fortarete[36001];
int dist[36001];
vector<pair<int, int>> graf[36001]; 
priority_queue<pair<int, int>> q;
int n, m, k;

void read(){
    f >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        dist[i] = INT_MAX;

    for (int i = 1; i <= k; i++) {
        int x;
        f >> x;
        fortarete[x] = x;
        q.push({ 0, x });
        //Citim si adaugam fortaretele in coada pentru a pleca cu dijkstra incepand cu ele si a calcula distanta pana la catune
        dist[x] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int x, y, z;
        f >> x >> y >> z;
        graf[x].push_back({y, z});
        graf[y].push_back({x, z});
    }
}

void dijkstra() {
    while (!q.empty()) {
        int nod = q.top().second;
        q.pop();
        for (auto& v : graf[nod]) {
            if (dist[nod] + v.second < dist[v.first]) {
                dist[v.first] = dist[nod] + v.second;
                q.push(make_pair(-dist[v.first], v.first ));
                fortarete[v.first] = fortarete[nod];

            }
            else if (dist[nod] + v.second == dist[v.first]) {
                fortarete[v.first] = min(fortarete[v.first], fortarete[nod]);

            }
        }
    }
}
int main() {

    read();
    dijkstra();
    for (int i = 1; i <= n; i++)
        if (fortarete[i] == i)
            g << 0 << " ";
        else
            g << fortarete[i] << " ";
    return 0;
}
