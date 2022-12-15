#include <bits/stdc++.h>
using namespace std;
ifstream f("apm2.in");
ofstream g("apm2.out");
vector<pair<int, pair<int, int>>> graf;
vector<pair<int, int>> drumuri;
vector<int> parinte, h, taxa;
int n, m, q;

int findReprezentant(int nod)
{
    while (parinte[nod] != nod)
        nod = parinte[nod];
    return parinte[nod];
}

void reuneste(int x, int y)
{
    if (h[x] > h[y])
        parinte[y] = x;
    else {
        parinte[x] = y;
        if (h[x] == h[y])
            ++h[y];
    }
    //Reuniune ponderata dupa inaltime : arborele cu înălţimea mai mică devine subarbore al
    //rădăcinii celuilalt arbore
}
int main() {
    f >> n >> m >> q;
    h.resize(n+1);
    parinte.resize(n+1);
    taxa.resize(q+1);

    for (int i = 0; i < m; i++){
        int x, y, cost;
        f >> x >> y >> cost;
        graf.push_back({cost, {x, y}});
    }
    sort(graf.begin(), graf.end());

    for (int i = 0; i < q; i++){
        int x,y;
        f >> x >> y ;
        drumuri.push_back({x, y});
    }
    for (int i = 1; i <= n; ++i){
        parinte[i] = i;
        h[i] = 1;
    }
    //Initializam Kruskal

    for (int i = 0; i < m; i++) {
        if (graf[i].first != graf[i - 1].first)
            for (int j = 0; j < q; j++)
                if (findReprezentant(drumuri[j].first) != findReprezentant(drumuri[j].second))
                    taxa[j] = graf[i].first - 1;
        if (findReprezentant(graf[i].second.first) != findReprezentant(graf[i].second.second))
            reuneste(findReprezentant(graf[i].second.first), findReprezentant(graf[i].second.second));
    }
    for (int i = 0; i < q; ++i)
        g << taxa[i] << '\n';
    return 0;
}
