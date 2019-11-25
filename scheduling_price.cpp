//
// Created by Alexey on 22/11/2019.
//
#include <iostream>

using namespace std;

int MIN = 999999999;

int n = 0;

int a[21][21], visited[21] = {0};

void DFS(const int index, const int sum) {
    if (sum > MIN)
        return;
    if (index == n) {
        MIN = (sum < MIN ? sum : MIN);
        return;
    }
    for (int j = 0; j < n; j++) {
        if (!visited[j]) {
            visited[j] = 1;
            DFS(index + 1, sum + a[index][j]);
            visited[j] = 0;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];

    DFS(0, 0);
    cout << MIN;
}

/*
3
10 2 3
2 3 4
3 4 5
*/