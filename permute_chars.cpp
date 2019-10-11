#include <iostream>

using std::cin;
using std::cout;

int total_num = 0;

inline void swap(char *a, const int &i, const int &j) {
    char s = a[i];
    a[i] = a[j];
    a[j] = s;
}
bool NextSet(char *a, const int &n) {
    int j = n - 2;
    while (j != -1 && a[j] >= a[j + 1]) j--;
    if (j == -1)
        return false; //no more permutations
    int k = n - 1;
    while (a[j] >= a[k]) k--;
    swap(a, j, k);
    int l = j + 1, r = n - 1; //sorting the rest
    while (l < r)
        swap(a, l++, r--);
    return true;
}
void Print(const char *a, const int &n) {
    total_num++;
    for (int i = 0; i < n; i++)
        cout << a[i];
    cout << '\n';
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int n = 0;
    char *a;
    cin >> n;
    a = new char[n];
    cin >> a;

    Print(a, n);
    while (NextSet(a, n))
        Print(a, n);
    cout << total_num;

}