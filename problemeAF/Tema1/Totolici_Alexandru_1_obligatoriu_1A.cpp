#include <iostream>
#include <vector>
#include <queue>
using namespace std;
bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
    queue<int> q;
    vector<int> level(n+1, 0);
    vector<bool> visited(n+1, false);
    vector<vector<int>> lista(n+1);
    for (auto &m: dislikes)
    {
        lista[m[0]].push_back(m[1]);
        lista[m[1]].push_back(m[0]);
    }

    for(int i=1; i<=n; i++){// aplicam BFS pe fiecare nod nevizitat al grafului, in cazul in care avem 2 componente conexe si nu e de ajuns sa parcurgem o data
        if(visited[i] == 0){
            q.push(i);
            while(!q.empty()){
                int nodCurent = q.front();
                q.pop();
                for(int i=0; i < lista[nodCurent].size(); i++){
                    if(visited[lista[nodCurent][i]] == 0){
                        q.push(lista[nodCurent][i]);
                        visited[lista[nodCurent][i]] = true;
                        level[lista[nodCurent][i]] = level[nodCurent] + 1;

                    }
                    else if (level[nodCurent] == level[lista[nodCurent][i]]) {
                        return false;
                        // conditia de oprire, din care reiese daca graful este bipartit sau nu,
                        // este data de relatia dintre doua noduri care au muchie intre ele,
                        // in cazul in care au acelasi nivel dupa o parcurgere BFS =>
                        // graful nu poate fi bipartit deoarece exista un ciclu => returnam false
                    }
                }
            }
        }
    }
    return true;
}

int main(){
    int n = 5;
    vector<vector<int>> dislikes = {{1,2},{1,3},{3,5},{4,2}};
    cout << possibleBipartition(n,dislikes);
}