#include <bits/stdc++.h>
using namespace std;
ifstream f("online.in");
ofstream g("online.out");
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

int doKruskal(){
    int s=0;
    vector<pair<int, pair<int, int>>> apm;
    for (int i = 1; i <= n; ++i){
        parinte[i] = i;
        h[i] = 1;
    }
    sort(graf.begin(), graf.end());
    for (int i = 0; i < (int)graf.size(); i++){
        int r1 = findReprezentant(graf[i].second.first);
        int r2 = findReprezentant(graf[i].second.second);
        if (r1 != r2){
            reuneste(r1, r2);
            s+=graf[i].first;
            apm.push_back(graf[i]);
            //Kruskal clasic in care salvam in s pentru fiecare graf suma costurilor muchiilor din APM
        }
    }
    graf = apm;
    //La fiecare pas graful se transforma in APM-ul grafului anterior
    return s;
}

int main() {
    f >> n >> m;
    h.resize(n+1);
    parinte.resize(n+1);

    for (int i = 0; i < m; i++){
        int x, y, cost;
        f >> x >> y >> cost;
        graf.push_back({cost, {x, y}});
    }
    g << doKruskal() << '\n';
    // Aflam suma costurilor muchiilor APM-ului grafului dat, apoi citim urmatoarele k muchii care se vor adauga grafului initial
    int k;
    f >> k;
    for (int i = 0; i < k; i++) {
        int x, y, cost;
        f >> x >> y >> cost;
        graf.push_back({cost, {x, y}});
        g << doKruskal() << '\n';
        //Dupa ce se construieste un nou APM dupa graful anterior + muchia curenta, afisam suma curenta a costurilor muchiilor APM-ului
        //Apoi graful se transforma in APM-ul trecut,se adauga o noua muchie, si se repeta acelasi proces
    }
}
