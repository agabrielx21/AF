#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;
ifstream f("ctc.in");
ofstream g("ctc.out");
int n,m,n1,n2,numberCTC;
vector<int> G[100001],GT[100001],CTC[100001];
stack<int> stck;
vector<int> visited(100001);

void read(){
    for(int i=0;i<m;i++){
        f>>n1>>n2;
        G[n1].push_back(n2);
        GT[n2].push_back(n1);
    }
}

void DFS_G(int root){
    visited[root] = 1;
    for(int i=0;i<G[root].size();i++){
        int nodCurent = G[root][i];
        if(!visited[nodCurent])
            DFS_G(nodCurent);
    }
    stck.push(root);
}

void DFS_GT(int root){
    visited[root] = 2;
    CTC[numberCTC].push_back(root);
    for(int i=0;i<GT[root].size();i++){
        int nodCurent = GT[root][i];
        if(visited[nodCurent]==1)
            DFS_GT(nodCurent);
    }
}

int main() {
    //Utilizand algoritmul lui Kosaraju determinam graful transpus grafului dat
    //Aplicam DFS pe graful dat si adaugam descrescator in stiva nodurile in functie de timpii de finalizare ( momentul in care gasim nodul parcurgand cu DFS )
    //Aplicam DFS pe graful transpus in ordinea nodurile adaugate pe stiva la pasul precedent
    //Componentele tare conexe sunt date de nodurile din subarborii de parcurgere dupa ce aplicam DFS in graful transpus
    f>>n>>m;
    read();

    for(int i=1;i<=n;i++)
        if(!visited[i])
            DFS_G(i);
    while(!stck.empty()){
        int nodCurent = stck.top();
        if(visited[nodCurent] == 1) {
            numberCTC++;
            DFS_GT(nodCurent);
        }
        stck.pop();
    }
    g << "\n" << numberCTC<<"\n";
    for(int i=1;i<=numberCTC;i++){
        for(int j=0;j<CTC[i].size();j++)
            g<<CTC[i][j]<<" ";
        g<<"\n";
    }
}