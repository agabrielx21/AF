///retea2 - am considerat centralele si blocurile ca fiind noduri ale unui graf si am
///ales sa construiesc muchiile astfel incat graful obtinut sa fie de cost minim
///initial, am verificat care este distanta minima dintre oricare bloc si o centrala
///apoi, am verificat daca exista blocuri care sunt mai aproape de alte blocuri deja conectate
///la o centrala decat de centrala la care sunt conectate
#include <bits/stdc++.h>
#define INF 1000000000
using namespace std;

ifstream f("retea2.in");
ofstream g("retea2.out");

int n,m;

vector<pair<double,double>> centrale;
vector<pair<double,double>> blocuri;
vector<double> dist;
vector<bool> conect;

///functia care calculeaza distanta dintre 2 puncte
double distanta(pair<double,double> a, pair<double,double> b)
{
    return sqrt(double((a.first-b.first)*(a.first-b.first))+double((a.second-b.second)*(a.second-b.second)));
}


void read(){
    f>>n>>m;
    dist.resize(m);
    for(int i=0;i<n;i++){
        int x,y;
        f>>x>>y;
        centrale.push_back(make_pair(x,y));
    }
    for(int i=0;i<m;i++){
        int x,y;
        f>>x>>y;
        blocuri.push_back(make_pair(x,y));
        dist[i]=MAX;
    }
}

int main()
{
    ///calculez care este cea mai apropiata centrala de fiecare bloc
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            dist[i] = min(dist[i],distanta(blocuri[i],centrale[j]));
        }
    }
    double cost=0;
    conect.resize(m,false);
    for(int i=0;i<m;i++){
        int indexbloc=-1;
        double minim=INF;
        ///caut blocul care are cea mai mica distanta de la o centrala
        for(int j=0;j<m;j++){
            if(dist[j]<minim && !conect[j]){
                minim=dist[j];
                indexbloc=j;
            }
        }
        cost += dist[indexbloc];
        conect[indexbloc]=true;
        ///verific daca exista blocuri care sunt mai aproape de alte blocuri deja conectate
        for(int j=0;j<m;j++)
            if(!conect[j])
                dist[j] = min(dist[j],distanta(blocuri[indexbloc],blocuri[j]));
    }
    g<<fixed<<setprecision(6)<<cost;
    return 0;
}
