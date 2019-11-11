#include <iostream>

using std::cout;
using std::cin;

int main() {
    int n;
    cin >> n;

    int cost[n][n];
    int min_arr[n];

    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            cin >> cost[i][j];

    min_arr[1] = 0;
    int min;

    for (int i = 2; i <= n; i++) {
        min = cost[1][i];
        for (int j = 1; j <= i - 1; j++)
            // first go down (vertical), otherwise go right 1 step and then down again
            if (cost[j][i] != 0 && min_arr[j] + cost[j][i] < min)
                min = min_arr[j] + cost[j][i];

        min_arr[i] = min;
    }
    cout << min_arr[n];
}