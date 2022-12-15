class Solution {
public:
    vector<pair<int, pair<int, int>>> graf;
    int parinte[1000], h[10000];

int findReprezentant(int nod)
{
	int prev = nod;
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
	//Reuniune ponderata dupa inaltime
}

int minCostConnectPoints(vector<vector<int>>& points) {
    	int n = points.size();
    	for (int i = 1; i <= n; ++i){
        parinte[i] = i;
        h[i] = 1;
        } //Initializare kruskall
   
    	for(int i = 0; i < n; i++){
        	for(int j = i + 1; j < n; j++){
            		int weight = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            		graf.push_back({weight, {i, j}});
      		}
    	}
    
    	sort(graf.begin(), graf.end());
    	
    	int sum = 0;
    	for(int i = 0; i < graf.size(); i++)   {
        	int a = findReprezentant(graf[i].second.first); 
        	int b = findReprezentant(graf[i].second.second);
        	if(a != b){ // daca nu inchide un ciclu adaugam muchia cu cost minim, updatam suma si construim apm-ul in continuare
            		sum += graf[i].first;
            		reuneste(a, b);
        		}
    		}
    	return sum;
    }
};
