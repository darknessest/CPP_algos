////
//// Created by Alexey on 11/11/2019.
////
//#include <iostream>
//#include <vector>
//#include <list>
//#include <queue>
//
//using namespace std;
//
//typedef pair<int, int> pi;
//
//void emplace_list(vector<list<pair<int, int> > > &x, pi thing) {
//    list<pi> first;
//    first.push_back(thing);
//    x.push_back(first);
//}
//
//int main() {
//    int n, a, b;
//    bool isInserted = false;
//    pi tmp;
//    priority_queue<pi, vector<pi>, greater<pi> > times;    // min heap of pairs of time
//    vector<list<pi> > rooms;             // graph represented as array of linked lists
//
//    cin >> n;
//    if (n > 0) {
//        // O(n*logn)
//        for (int i = 0; i < n; ++i) {
//            cin >> a >> b;
//            times.push(make_pair(a, b));
//        }
//
//        tmp = times.top();
//        times.pop();
//        emplace_list(rooms, tmp);
//
//        // O(n*n)
//        while (!times.empty()) {
//            tmp = times.top();
//            times.pop();
////            for (list<pi> x = rooms.begin(); ) {
//            for (auto &x: rooms) {
//                if (x.back().second < tmp.first) {
//                    x.push_back(tmp);
//                    isInserted = true;
//                    break;
//                }
//            }
//            if (!isInserted)
//                emplace_list(rooms, tmp);
//
//            isInserted = false;
//        }
//        cout << rooms.size();
//    } else
//        cout << 0;
//    return 0;
//}

/*
7
29 49
1 23
12 28
25 35
48 60
27 80
36 50
 */

// better solution
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
  int t;
  bool f;
};

bool cmp(point x, point y) {
    return x.t < y.t;
}

int greedy(vector<point> x) {
    int max = 0, cur = 0, n = x.size();
    sort(x.begin(), x.end(), cmp);
    for (int i = 0; i < n; i++) {
        if (x[i].f)
            cur++;
        else
            cur--;
        if ((i == n - 1 || x[i].t < x[i + 1].t) && cur > max)
            max = cur;
    }
    return max;
}

int main() {
    vector<point> x;
    int n, i;
    point temp;
    cin >> n;
    for (i = 0; i < n; i++) {
        temp.f = true;
        cin >> temp.t;
        x.push_back(temp);
        temp.f = false;
        cin >> temp.t;
        x.push_back(temp);
    }
    cout << greedy(x);
    x.clear();

    return 0;
}
