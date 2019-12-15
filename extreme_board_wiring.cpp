//#include <algorithm>
//#include <iostream>
//#include <queue>
//#include <cstring>
//
//using namespace std;
//
//int n, m;
//
//int bestx[21];
//
//int **B;
//
//class BoardNode {
// public:
//    int x[21];
//    int low[21];
//    int high[21];
//    int s;
//    int cd;
//
//    BoardNode() {
//        memset(this->x, 0, sizeof(int)*21);
//        memset(this->low, 0, sizeof(int)*21);
//        memset(this->high, 0, sizeof(int)*21);
//        this->cd = 0;
//        this->s = 0;
//    }
//
//    friend bool operator<(const BoardNode &a, const BoardNode &b);
//
//    int len() {
//        int tmp = 0;
//        for (int k = 1; k <= m; k++)
//            if (low[k] <= n && high[k] > 0 && tmp < high[k] - low[k])
//                tmp = high[k] - low[k];
//
//        return tmp;
//    }
//};
//
//bool operator<(const BoardNode &a, const BoardNode &b) {
//    return a.cd > b.cd;
//}
//
//int FIFOBoards();
//
//int main() {
//
//    cin >> n >> m;
//
//    B = new int *[n + 1];
//    for (int i = 0; i < n + 1; ++i)
//        B[i] = new int[m + 1];
//
//    for (int i = 1; i <= n; i++)
//        for (int j = 1; j <= m; j++)
//            cin >> B[i][j];
//
//    int bestd = FIFOBoards();
//
//    cout << bestd << "\n";
//
//    for (int i = 1; i <= n; i++)
//        cout << bestx[i] << ' ';
//}
//
//int FIFOBoards() {
//    priority_queue<BoardNode> pq;
//    BoardNode E;
//
////    E.s = 0;
////    E.cd = 0;
//
//    for (int i = 0; i <= m; i++) {
//        E.high[i] = 0;
//        E.low[i] = n + 1;
//    }
//
//    for (int i = 0; i <= n; i++)
//        E.x[i] = i;
//
//    int bestd = n + 1;
//
//    while (true) {
//        if (E.s == n - 1) {
//            for (int j = 1; j <= m; j++)
//                if (B[E.x[n]][j] > 0 && n > E.high[j]) E.high[j] = n;
//            int ld = E.len();
//            if (ld < bestd) {
//                copy(E.x, E.x + 21, bestx);
//                bestd = ld;
//            }
//        } else {
//            int curr = E.s + 1;
//            for (int i = E.s + 1; i <= n; i++) {
//                BoardNode N;
//
//                for (int j = 1; j <= m; j++) {
//                    N.low[j] = E.low[j];
//                    N.high[j] = E.high[j];
//
//                    if (B[E.x[i]][j] > 0) {
//                        if (curr < N.low[j]) N.low[j] = curr;
//                        if (curr > N.high[j]) N.high[j] = curr;
//                    }
//                }
//                N.cd = N.len();
//                if (N.cd < bestd) {
//                    N.s = E.s + 1;
//                    for (int j = 1; j <= n; j++)
//                        N.x[j] = E.x[j];
//
//                    N.x[N.s] = E.x[i];
//                    N.x[i] = E.x[N.s];
//
//                    pq.push(N);
//                }
//            }
//        }
//        if (E.cd >= bestd)
//            break;
//        else {
////            if (pq.empty())
////                break;
//            E = pq.top();
//            pq.pop();
//        }
//    }
//
//    return bestd;
//}
/*
8 5
1 1 1 1 1
0 1 0 1 0
0 1 1 1 0
1 0 1 1 0
1 0 1 0 0
1 1 0 1 0
0 0 0 0 1
0 1 0 0 1
 */

/*
 4
 5 4 3 1 6 2 8 7
 */
#include <iostream>

using namespace std;

const int INF = 1000000;

const int MAX = 22;

int p[MAX][MAX];

int bestx[MAX];

int x[MAX];

int minLen = INF;

int n, m;

int low[MAX];

int heigh[MAX];

int len(const int &a) {
    int i;
    for (i = 1; i <= m; i++) {
        low[i] = INF;
        heigh[i] = 0;
    }

    for (i = 1; i <= a; i++)
        for (int j = 1; j <= m; j++)
            if (p[x[i]][j] > 0) {
                if (i < low[j])
                    low[j] = i;
                if (i > heigh[j])
                    heigh[j] = i;
            }

    int max = 0;
    for (i = 1; i <= m; i++)
        if (heigh[i] > 0 && low[i] < INF && heigh[i] - low[i] > max)
            max = heigh[i] - low[i];

    return max;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void backtrack(const int &i) {
    if (i == n) {
        int ld = len(i);
        if (ld < minLen) {
            minLen = ld;
            for (int j = 1; j <= n; j++)
                bestx[j] = x[j];
        }
    } else
        for (int r = i; r <= n; r++) {
            swap(x[i], x[r]);
            if (len(i) < minLen)
                backtrack(i + 1);
            swap(x[i], x[r]);
        }
}

int main() {

    cin >> n;

    cin >> m;
    int i, j;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            cin >> p[i][j];
        }
    }

    for (i = 1; i <= n; i++)
        x[i] = i;
    backtrack(1);

    cout << minLen << '\n';

    for (i = 1; i <= n; i++)
        cout << bestx[i] << " ";
}
