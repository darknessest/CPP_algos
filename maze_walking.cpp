//#include <iostream>
//#include <list>
//#include <stack>
//
//using namespace std;
//
//int n = 0, m = 0, k = 0, dstX = 0, dstY = 0, minTurns = 9999;
//
//pair<int, int> prevMove = {-1, -1};
//
//template<typename T>
//T **AllocateDynamicArray(int nRows, int nCols) {
//    T **dynamicArray;
//
//    dynamicArray = new T *[nRows];
//    for (int i = 0; i < nRows; i++)
//        dynamicArray[i] = new T[nCols];
//
//    return dynamicArray;
//}
//
//bool isValidMove(int **board, const int &X, const int &Y) {
//    if (X < n && X >= 0 && Y < m && Y >= 0)
//        return X < n && Y < m && board[X][Y] != -1;
//    return false;
//}
//bool isTurn(int const prevX, int const prevY, int const nextX, int const nextY) {
//    return prevX == nextX || prevY == nextY;
//}
//
//void BFS(int **board, const int curX, const int curY, int numOfSteps, int numOfTurns) {
//    pair<int, int> nextMove;
//    stack<pair<int, int> > moves;
//
//    // adding aval moves
//    if (isValidMove(board, curX - 1, curY - 1))
//        moves.emplace(curX - 1, curY - 1);
//
//    if (isValidMove(board, curX - 1, curY))
//        moves.emplace(curX - 1, curY);
//
//    if (isValidMove(board, curX - 1, curY + 1))
//        moves.emplace(curX - 1, curY + 1);
//
//    if (isValidMove(board, curX, curY + 1))
//        moves.emplace(curX, curY + 1);
//
//    if (isValidMove(board, curX + 1, curY + 1))
//        moves.emplace(curX + 1, curY + 1);
//
//    if (isValidMove(board, curX + 1, curY))
//        moves.emplace(curX + 1, curY);
//
//    if (isValidMove(board, curX + 1, curY - 1))
//        moves.emplace(curX + 1, curY - 1);
//
//    if (isValidMove(board, curX, curY - 1))
//        moves.emplace(curX, curY - 1);
//
//
//    // starting recursion
//    while (!moves.empty()) {
//        nextMove = moves.top();
//        moves.pop();
//
//        if (numOfSteps == (n*m - k - 1) && nextMove.first == dstX && nextMove.second == dstY) {
//            minTurns = minTurns < numOfTurns ? minTurns : numOfTurns;
////            minTurns = min(minTurns, numOfTurns);
//            cout << "new: " << minTurns << '\n';
//            return;
//        }
//
//        board[curX][curY] = -1;
//        if ((prevMove.first == -1 && prevMove.second == -1)
//            || isTurn(prevMove.first, prevMove.second, nextMove.first, nextMove.second)) {
//            prevMove = {curX, curY};
//            BFS(board, nextMove.first, nextMove.second, numOfSteps + 1, numOfTurns + 1);
//
//        } else {
//            prevMove = {curX, curY};
//            BFS(board, nextMove.first, nextMove.second, numOfSteps + 1, numOfTurns);
//        }
//        // restoring grid after pulling off
//        board[curX][curY] = 1;
//    }
//
//}
//
//// Driver program
//int main() {
//    int srcX = 0, srcY = 0;
//    cin >> n >> m >> k;
//    cin >> srcX >> srcY;
//    cin >> dstX >> dstY;
//
//    int **board = AllocateDynamicArray<int>(n, m);
//
//    for (int j = 0; j < n; ++j) {
//        for (int i = 0; i < m; ++i) {
//            board[j][i] = 1;
//        }
//    }
//    for (int a = 0, b = 0, i = 0; i < k; ++i) {
//        cin >> a >> b;
//        board[a][b] = -1;
//    }
//    cout << "Starting BFS: " << minTurns << '\n';
//
//    BFS(board, srcX, srcY, 0, 0);
//    cout << minTurns;
//}

/*
3 4 2
1 2
3 4
1 1
2 2
 */

#include <iostream>

using namespace std;

int m, n, k;

int x, y;

int p, q, r, s;

int **board;

int *direction;

int level = 0;

int finalLevel = 0;

int **result;

int **path;

int minTurns = 999;

int pathsCount = 0;

int dirx[8] = {0, 0, 1, 1, 1, -1, -1, -1};

int diry[8] = {1, -1, -1, 0, 1, -1, 0, 1};

bool isValid() {
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (board[i][j] == 0)
                return false;
    return true;
}
bool recurse(const int a, const int b) {

    path[0][level] = a;
    path[1][level] = b;
    level++;
    board[a][b] = 1;

    if (a == r && b == s) {
        if (isValid()) {
            int count(0);
            for (int i = 1; i < level; i++)
                if (direction[i] != direction[i - 1]) count++;

            if (count < minTurns) {
                finalLevel = level;
                pathsCount = 1;
                minTurns = count;
                for (int i = 0; i < level; i++) {
                    result[0][i] = path[0][i];
                    result[1][i] = path[1][i];
                }
            } else if (count == minTurns)
                pathsCount++;
        }
        board[a][b] = 0;
        level--;
        return false;
    }

    for (int x1, y1, i = 0; i < 8; i++) {
        x1 = a + dirx[i];
        y1 = b + diry[i];
        if (board[x1][y1] == 0) {
            direction[level] = i;
            recurse(x1, y1);
        }
    }
    board[a][b] = 0;
    level--;
    return true;
}

int main() {
    int i, j;
    cin >> m >> n >> k;

    result = new int *[2];
    result[0] = new int[n*m];
    result[1] = new int[n*m];
    path = new int *[2];
    path[0] = new int[n*m];
    path[1] = new int[n*m];

    direction = new int[m*n];

    board = new int *[m + 2];
    for (i = 0; i < m + 2; i++)
        board[i] = new int[n + 2];

    for (i = 0; i < m + 2; i++)
        for (j = 0; j < n + 2; j++)
            board[i][j] = 0;

    for (i = 0; i < k; i++) {
        cin >> x >> y;
        board[x][y] = -1;
    }

    for (i = 0, j = 0; i < m + 2; i++)
        board[i][j] = 1;
    for (i = 0, j = 0; j < n + 2; j++)
        board[i][j] = 1;
    for (i = m + 1, j = 0; j < n + 2; j++)
        board[i][j] = 1;
    for (j = n + 1, i = 0; i < m + 2; i++)
        board[i][j] = 1;

    cin >> p >> q >> r >> s;

    direction[0] = -1;
    recurse(p, q);

    cout << minTurns - 1 << '\n';
    cout << pathsCount << '\n';
    for (i = 0; i < finalLevel; i++)
        board[result[0][i]][result[1][i]] = i + 1;

    for (i = 1; i < m + 1; i++) {
        for (j = 1; j < n + 1; j++)
            cout << board[i][j] << ' ';
        cout << endl;
    }
}
