///disjoint - pentru fiecare operatie 1, voi construi un arbore care sa contina
///elementele cerute, sau daca acestea fac parte deja din alti arbori, voi cauta radacinile
///acestora si le voi uni in arborele curent
///pentru fiecare operatie 2, caut radacinile arborilor care contin elementele cerute
///si verific daca sunt egale
// O abordare eficienta este aceea de a reprezenta fiecare multime ca pe un arbore cu radacina. Astfel pentru fiecare operatie de tip 2 parcurgem arborele in sus din ambele elemente si daca la sfarsit ajungem in aceeasi radacina atunci elementele noastre se afla in aceeasi multime. Atunci cand vrem sa unim 2 multimi determinam radacinile celor 2 arbori si le conectam printr-o muchie.

#include <bits/stdc++.h>
using namespace std;
ifstream f("disjoint.in");
ofstream g("disjoint.out");
int n, m;
vector <int> tata;

int radacina(int nod) {
    if(tata[nod] == 0) 
        return nod;
    tata[nod] = radacina(tata[nod]);
    return tata[nod];
}

void unire(int x, int y) {
    if(radacina(x)!= radacina(y))
        tata[radacina(x)] = radacina(y);
}

int main()
{
    f >> n >> m;
    tata.resize(n + 1, 0);
    for (int i = 1; i <= m; i++) {
        int cod, x, y;
        f >> cod >> x >> y;
        switch(cod){
            case 1:
                unire(x,y);
                break;
            case 2:
                if (radacina(x) == radacina(y))
                    g << "DA\n";
                    
                else
                    g << "NU\n";
                break;
        }
    }
    f.close();
    g.close();
    return 0;
}
