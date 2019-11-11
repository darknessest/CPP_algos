//
// Created by Alexey on 27/10/2019.
//
#include <vector>
#include <queue>
// #include <pair>
#include <iostream>
using namespace std;
const int INF = 1000000000;

typedef pair<int, int> pi;

int main() {
    int n, dist;
    cin >> n;
    vector < vector <pi> > g (n);
    for (int i=0; i<n; ++i){
    	for (int j = 0; j <= i; ++j)
    	{
    		cin >> dist;
    		g[i][j] = make_pair(dist, i+j);
    	}
    	for(int j=i+1; j<n; ++j){
    		g[i][j] = make_pair(0, i+j);
    	}
    }
    int s = 0; // стартовая вершина

    vector<int> d (n, INF),  p (n);
    d[s] = 0;

    //priority_queue <pi, vector<pi>, greater<pi>> q;	//maxheap
    priority_queue <pi> q; 			//minheap
    q.push (make_pair (0, s));
    while (!q.empty()) {
        int v = q.top().second, cur_d = -q.top().first;
        q.pop();
        if (cur_d > d[v])  continue;

        for (size_t j=0; j<g[v].size(); ++j) {
            int to = g[v][j].first,
                len = g[v][j].second;
            if (d[v] + len < d[to]) {					//> for the max len
                d[to] = d[v] + len;
                p[to] = v;
                q.push (make_pair (-d[to], to));
            }
        }
    }
}