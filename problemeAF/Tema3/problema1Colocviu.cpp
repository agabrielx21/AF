#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

ifstream f("C:\\Users\\Alex\\CLionProjects\\untitled\\cmake-build-debug\\date.in");

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

void afisareGraf(){
    for(int i=1; i<=n; i++) {
        for (auto &node: graf[i])
            cout << "(" << i << "," << node << ")\n";
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
    read();
    vector<vector<int>> distante;
    int nodCurent = 1;
    level.assign(n+1, -1);
//    bfs(1);
//    for(int i=1; i<=n; i++){
//        if(level[i] == -1){
//            bfs(i);
//            graf[i].push_back(1);
//            graf[1].push_back(i);
//            cout << "(" << i << "," << 1 << ")\n";
//        }
//    }
    for(int i=1; i<=n; i++){
        if(level[i] == -1){
            bfs(i);
            graf[i].push_back(nodCurent);
            graf[nodCurent].push_back(i);
            if(nodCurent!=i)
                cout << "(" << i << "," << nodCurent << ")\n";
            nodCurent = i;
        }
    }
//    afisareGraf();
    int s,maxi = 0;
    f >> s;
    level.assign(n+1, -1);
    bfs(s);
    for(int i=1;i<=n;i++){
        if(level[i]>maxi)
            maxi = level[i];
    }
    cout << maxi;
    return 0;
}

//Pentru a lega muchie intre 2 componente neconexe putem pleca cu un DFS din nodul 1, vedem pana unde putem ajunge iar
//cand gasim un nod nevizitat => avem un nou dintr-o cc. dif si va trebui sa il legam cu componenta conexa anterioara
//Metoda 2: Plecam cu un BFS din 1. apoi verificam vectorul de nivele si cand gasim un nod cu nivel -1 => Nu am ajuns
//cu BFS pe acolo => o noua cc. => va trebui sa il legam de nodul anterior si sa plecam cu un nou BFS din nodul curent