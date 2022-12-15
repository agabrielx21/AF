//#include <iostream>
//#include <vector>
//using namespace std;
//class Solution{
//public:
//    vector<int> internalG(2001, 0);
//    vector<int> order;
//    vector<bool> visited(2001, false);
//    vector<vector<int>> lista(2001);
//    int n;
//
//    void DFS(int root){
//        visited[root] = true;
//        order.push_back(root);
//        for(int i=0; i<lista[root].size();i++){
//            internalG[lista[root][i]]--;
//            if(!visited[lista[root][i]] && internalG[lista[root][i]] == 0)
//                DFS(lista[root][i]);
//        }
//    }
//
//    vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
//
//        for (auto &m: prerequisites){
//            lista[m[1]].push_back(m[0]);
//            internalG[m[0]]++;
//        }
//
//        for(int i=0; i<n;i++){
//            if(!visited[i] && internalG[i] == 0)
//                DFS(i);
//        }
//
//        if(order.size() != n)
//            order.clear();
//        return order;
//    }
//};


#include <iostream>
#include <vector>
using namespace std;

vector<int> internalG(2001, 0);
vector<int> order;
vector<bool> visited(2001, false);
vector<vector<int>> lista(2001);
int n;

void DFS(int root){
    visited[root] = true;
    order.push_back(root);
    for(int i=0; i<lista[root].size();i++){
        internalG[lista[root][i]]--;
        if(!visited[lista[root][i]] && internalG[lista[root][i]] == 0)
            DFS(lista[root][i]);
    }
}

vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {

    for (auto &m: prerequisites){
        lista[m[1]].push_back(m[0]);
        internalG[m[0]]++;
    }

    for(int i=0; i<n;i++){
        if(!visited[i] && internalG[i] == 0)
            DFS(i);
    }

    if(order.size() != n)
        order.clear();
    return order;
}


int main(){
    //Incepem sa parcurgem cu DFS de la primul nod care are gradul intern 0
    //(primul curs care nu depinde de alte cursuri ( nu trebuie sa aiba inaintea sa alt curs )
    //Apoi parcurgem si celelalte noduri si adaugam in lista de ordine a cursurilor
    //un nod doar in momentul in care gradul lui intern e 0 ( i se micsoreaza gradul cu 1 in fiecare moment in care il gasim in lista de adiacenta a altor noduri)
    //Acest lucru ne asigura ca toate nodurile adaugate in lista de ordine nu vor fi restrictionate
    //de alte noduri si nu va aparea un curs inaintea altuia care il restrictioneaza
    n = 4;
    vector<vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};
    vector<int> v = findOrder(n,prerequisites);
    cout << "[";
    for(int i=0;i<v.size();i++) {
        cout << v[i];
        if(i!=v.size()-1)
            cout << ",";
    }
    cout << "]";
}