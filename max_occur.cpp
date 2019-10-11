#include <iostream>
#include <cmath>

using std::cin;
using std::cout;

int set(const int &n) {
    int count = 1;
    if (n > 1)
        for (int i = 1; i <= floor(n/2.0); i++)
            count += set(i);
    return count;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int number = 0;
    cin >> number;
    cout << set(number);
}