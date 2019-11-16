//
// Created by Alexey on 16/11/2019.
//
#include <iostream>
#include <vector>
#include <algorithm>
//#include <iomanip>

using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    return (a.first*a.second < b.first*b.second);
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int n = 0, a = 0, b = 0, sum_b = 0;
    cin >> n;
    vector<pair<int, int> > progs;

    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        // emplace_back mb better
        progs.push_back(make_pair(a, b));
        sum_b += b;
    }


    // can be improved by using radixsort
    // O(n*logn)
    sort(progs.begin(), progs.end(), cmp);
    double t = 0, tmp = 0;
    // O(n*n), actually a bit smaller
    for (int i = 0; i < n; ++i) {
        tmp = 0;
        for (int j = 0; j <= i; ++j) {
            tmp += progs[j].first*progs[j].second*1.0/sum_b;
        }

        t += tmp;
    }
    // set precision mb needed
    cout << t;
}
