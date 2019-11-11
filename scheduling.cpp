//
// Created by Alexey on 11/11/2019.
//
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pi;

void emplace_list(vector<list<pi>> &x, pi thing) {
    list<pi> first;
    first.push_back(thing);
    x.push_back(first);
}

int main() {
    int n, a, b;
    bool isInserted = false;
    pi tmp;
    priority_queue<pi, vector<pi>, greater<>> times;    // min heap of pairs of time
    vector<list<pi>> rooms;             // graph represented as array of linked lists


    cin >> n;

    // O(n*logn)
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        times.push(make_pair(a, b));
    }

    tmp = times.top();
    times.pop();
    emplace_list(rooms, tmp);

    // O(n*n)
    while (!times.empty()) {
        tmp = times.top();
        times.pop();
        for (list<pi> &x: rooms) {
            if (x.back().second < tmp.first) {
                x.push_back(tmp);
                isInserted = true;
                break;
            }
        }
        if (!isInserted)
            emplace_list(rooms, tmp);

        isInserted = false;
    }
    cout << rooms.size();

}

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