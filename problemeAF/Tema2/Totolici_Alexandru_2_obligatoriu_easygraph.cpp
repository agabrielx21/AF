//Vom afla suma maxima a unui lant pornind cu DFS din primul nod
//In vectorul S vom retine sumele maxime pentru un lant care include nodul i
//Actualizam vectorul S in timp ce parcurgem cu DFS, astfel S[i]=max(S[i], S[lantul parcurs pana in nodul curent] + v[i] (suma nodului curent))
//La final pentru un test alegem maximul din vectorul S ca fiind lantul cu suma cea mai mare

#include<bits/stdc++.h>
using namespace std;
ifstream f("easygraph.in");
ofstream g("easygraph.out");

int t, n, m;
vector<long long> v;
vector<vector<int>> graf;
vector<long long> S;
vector<bool> vizitat;

void read(){
    v.clear();
    graf.clear();
    vizitat.clear();
    S.clear();
    f>>n>>m;
    v.resize(n+1);
    graf.resize(n+1);
    vizitat.resize(n+1, false);
    S.resize(n+1, -1000000);

    for(int i=1; i<=n; i++){
        f>>v[i];
    }
    for(int i=0; i<m; i++){
        int x, y;
        f>>x>>y;
        graf[x].push_back(y);
    }
}

void dfs(int nod){
    vizitat[nod] = true;
    S[nod] = max(S[nod], v[nod]);
    for(auto fiu: graf[nod]){
        if(!vizitat[fiu])
            dfs(fiu);
        S[nod] = max(S[nod], v[nod] + S[fiu]);
    }
}

int main(){
    f>>t;
    while(t--){
        read();
        long long ans = -1000000;
        for(int i = 1; i <= n; i++){
            if(!vizitat[i])
                dfs(i);
            ans = max(ans, S[i]);
        }
        g << ans << "\n";
    }
}

