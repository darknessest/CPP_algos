////
//// Created by Alexey on 26/11/2019.
////
//
//#include <iostream>
//
//using namespace std;
//
//int arr[20][20];
//
//int minCables = 999999;
//
//int bestPemute[20];
//
//int mapped_val(const int x, const int y) {
//
//    if (x <= y) {
////        cout << "1) (x, y): (" << x << ", " << y << ") = " << arr[x - 1][y - x - 1] << "\n";
//        return arr[x - 1][y - x - 1];
//
//    } else {
////        cout << "2) (x, y): (" << y << ", " << x << ") = " << arr[y - 1][x - y - 1] << "\n";
//        return arr[y - 1][x - y - 1];
//    }
//}
//
//void printArr(int a[], int n) {
//    int cablesCount = 0;
//
//    for (int i = 0; i < n - 1; i++) {
////        cout << a[i] << " ";
//        for (int j = i + 1; j < n; ++j) {
////            cout << a[j] << " ";
//            cablesCount += mapped_val(a[i], a[j])*(j - i);
//        }
////        cout << " | ";
//    }
//    if (cablesCount < minCables) {
//        minCables = cablesCount;
//        copy(a, a + n, bestPemute);
////        memset(bestPemute, a, n*sizeof(int));
//    }
//
////    cout << " CablesCount: " << cablesCount << "\n-------------------\n";
//
////    printf(" cables\n");
//}
//
//// Generating permutation using Heap Algorithm
//void heapPermutation(int a[], int size, int n) {
//    // if size becomes 1 then prints the obtained
//    // permutation
//    if (size == 1) {
//        printArr(a, n);
//        return;
//    }
//
//    for (int i = 0; i < size; i++) {
//        heapPermutation(a, size - 1, n);
//
//        // if size is odd, swap first and last
//        // element
//        if (size%2 == 1)
//            swap(a[0], a[size - 1]);
//
//            // If size is even, swap ith and last
//            // element
//        else
//            swap(a[i], a[size - 1]);
//    }
//}
//
//int main() {
//    int n = 0;
//    cin >> n;
////    int arr[20][20];
//    int linear[20];
//
//    for (int i = 0; i < n - 1; ++i)
//        for (int j = 0; j < n - 1 - i; ++j)
//            cin >> arr[i][j];
////    for (int i = 0; i < n - 1; ++i) {
////        for (int j = 0; j < n - 1 - i; ++j)
////            cout << arr[i][j] << ' ';
////        cout << '\n';
////    }
//
//    for (int k = 1; k <= n; ++k)
//        linear[k - 1] = k;
//
//    heapPermutation(linear, n, n);
//
////    cout << "THE BEST:\n";
//    cout << minCables << '\n';
//    for (int l = 0; l < n; ++l)
//        cout << bestPemute[l] << ' ';
//}
/*
3
2 3
3


 4
 4 5 6
 9 6
 3

 8
5 7 2 14 17 11 13
18 13 4 3 14 5
14 3 10 3 5
19 0 9 4
5 15 6
19 12
16
 */
#include <iostream>

using namespace std;

int n;

int len(int **conn, const int x[], const int &width) {
    int sum = 0;
    for (int i = 1; i <= width; i++) {
        for (int j = i + 1; j <= width; j++) {
            int dist = x[i] > x[j] ? x[i] - x[j] : x[j] - x[i];
            sum += conn[i][j]*dist;
        }
    }

    return sum;
}

void swap(int x[], const int &i, const int &j) {
    int tmp;
    tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
}

void backtrack(int **arr, int best_perm[], int perm[], const int &t, int &bestlen) {

    if (t == n) {
        int tmp = len(arr, perm, t);
        if (tmp < bestlen) {
            bestlen = tmp;
            for (int j = 1; j <= n; j++)
                best_perm[j] = perm[j];
        }
    } else {
        for (int j = t; j <= n; j++) {
            swap(perm, t, j);
            backtrack(arr, best_perm, perm, t + 1, bestlen);
            swap(perm, t, j);  // swap back
        }
    }
}

int main() {
    int **arr;
    int *perm, *best_perm;
    int best_len = 1000000;

    cin >> n;

    perm = new int[n + 1];
    best_perm = new int[n + 1];
    arr = new int *[n + 1];

    for (int i = 0; i < n + 1; ++i)
        arr[i] = new int[n + 1];

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        perm[i] = i;
    }
    backtrack(arr, best_perm, perm, 1, best_len);

    cout << best_len << '\n';
    for (int i = 1; i <= n; i++)
        cout << best_perm[i] << " ";
}