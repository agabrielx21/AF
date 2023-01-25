#include <bits/stdc++.h>
using namespace std;

int n, max_flow;
vector<vector<int>> lista;
int graf[300][300];
vector <int> parinte;
ifstream f("harta.in");
ofstream g("harta.out");

bool bfs() {
    parinte = vector<int>(2 * n + 2, 0);
    vector<bool>visited(2 * n + 2);
    queue <int> q;
    q.push(0);
    visited[0] = true;
    while (!q.empty()) {
        int nod = q.front();
        q.pop();
        for (auto nodCurent : lista[nod]) {
            if (graf[nod][nodCurent] > 0 && !visited[nodCurent]) {
                parinte[nodCurent] = nod;
                if (nodCurent == 2 * n + 1)
                    return true;
                visited[nodCurent] = true;
                q.push(nodCurent);
            }
        }
    }
    return false;
}

int flow() {
    while (bfs()) {
        int current_flow = INT_MAX;
        int i = 2 * n + 1;
        while (i != 0) {
            current_flow = min(current_flow, graf[parinte[i]][i]);
            i = parinte[i];
        }

        i = 2 * n + 1;
        while (i != 0) {
            graf[parinte[i]][i] -= current_flow;
            graf[i][parinte[i]] += current_flow;
            i = parinte[i];
        }

        max_flow += current_flow;
    }
    return max_flow;
}

int main()
{
    int x, y;
    f >> n;
    lista = vector<vector<int>>(2*n+2);
    parinte = vector<int>(2*n+2, 0);

    for(int i=1;i<=n;i++)
        for (int j = n + 1;j <= 2 * n;j++) {
            if (i != j - n) {
                lista[i].push_back(j);
                lista[j].push_back(i);
                graf[i][j] = 1;
            }
        }
    for (int i = 1;i <= n;i++)
    {
        f >> x >> y;
        lista[0].push_back(i);
        lista[i].push_back(0);
        lista[2 * n + 1].push_back(i+n);
        lista[i+n].push_back(2 * n + 1);
        graf[0][i] = x;
        graf[i+n][2*n+1] = y;
    }
    g << flow() << endl;
    for (int i = 1;i <= n;i++)
        for (int j = n + 1;j <= 2 * n;j++)
            if (graf[j][i])
                g << i << " " << j - n << endl;
    return 0;
}