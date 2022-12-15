#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

ifstream f("graf.in");

vector<vector<int>> graf;
vector<int> level;
int n, m;


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

void bfs(int node) {
    queue<int> q;
    q.push(node);
    level[node] = 0;

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(auto v :graf[node]) {
            if(level[v] == -1) {
                q.push(v);
                level[v] = 1 + level[node];
            }
        }
    }
}

int main(){

    ////Cautam cu BFS nivelul de la noduri spre cele n noduri "puncte de control"
    ////Apoi comparam vectorii de nivel si alegem distanta de la un nod la cel mai apropiat punct de control

    read();


    int control[1001];
    int k=0;
    while(!f.eof()){
        f>>control[k++];
    }

    vector<vector<int>> distante;
    level.assign(n+1, -1);

    for(int i=0;i<k;i++) {
        bfs(control[i]);
        distante.push_back(level);
        level.assign(n + 1, -1);
    }

    level.assign(n + 1, 2e9);
    for(int i = 1; i <= n; i++) {
        for(int j=0; j < k; j++)
            level[i] = min(distante[j][i], level[i]);
        cout << level[i] << " ";
    }

    return 0;
}

