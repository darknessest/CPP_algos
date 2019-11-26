#include <iostream>
#include <list>
#include <stack>

using namespace std;

int n = 0, m = 0, k = 0, dstX = 0, dstY = 0, minTurns = 9999;

pair<int, int> prevMove = {-1, -1};

template<typename T>
T **AllocateDynamicArray(int nRows, int nCols) {
    T **dynamicArray;

    dynamicArray = new T *[nRows];
    for (int i = 0; i < nRows; i++)
        dynamicArray[i] = new T[nCols];

    return dynamicArray;
}

bool isValidMove(int **board, const int &X, const int &Y) {
    return X < n && Y < m && board[X][Y] != -1;
}
bool isTurn(int const prevX, int const prevY, int const nextX, int const nextY) {
    return prevX == nextX || prevY == nextY;
}

void BFS(int **board, const int curX, const int curY, int numOfSteps, int numOfTurns) {
    pair<int, int> nextMove;
    stack<pair<int, int> > moves;

    // adding aval moves
    if (isValidMove(board, curX - 1, curY - 1))
        moves.emplace(curX - 1, curY - 1);

    if (isValidMove(board, curX - 1, curY))
        moves.emplace(curX - 1, curY);

    if (isValidMove(board, curX - 1, curY + 1))
        moves.emplace(curX - 1, curY + 1);

    if (isValidMove(board, curX, curY + 1))
        moves.emplace(curX, curY + 1);

    if (isValidMove(board, curX + 1, curY + 1))
        moves.emplace(curX + 1, curY + 1);

    if (isValidMove(board, curX + 1, curY))
        moves.emplace(curX + 1, curY);

    if (isValidMove(board, curX + 1, curY - 1))
        moves.emplace(curX + 1, curY - 1);

    if (isValidMove(board, curX, curY - 1))
        moves.emplace(curX, curY - 1);


    // starting recursion
    while (!moves.empty()) {
        nextMove = moves.top();
        moves.pop();

        if (numOfSteps == (n*m - k - 1) && nextMove.first == dstX && nextMove.second == dstY) {
            minTurns = min(minTurns, numOfTurns);
            return;
        }

        board[curX][curY] = -1;
        if ((prevMove.first == -1 && prevMove.second == -1)
            || isTurn(prevMove.first, prevMove.second, nextMove.first, nextMove.second)) {
            prevMove = {curX, curY};
            BFS(board, nextMove.first, nextMove.second, numOfSteps + 1, numOfTurns + 1);
        } else {
            prevMove = {curX, curY};
            BFS(board, nextMove.first, nextMove.second, numOfSteps + 1, numOfTurns);

        }
        // restoring grid after pulling off
        board[curX][curY] = 1;
    }

}

// Driver program
int main() {
    int srcX = 0, srcY = 0;
    cin >> n >> m >> k;
    cin >> srcX >> srcY;
    cin >> dstX >> dstY;

    int **board = AllocateDynamicArray<int>(n, m);

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            board[j][i] = 1;
        }
    }
    for (int a = 0, b = 0, i = 0; i < k; ++i) {
        cin >> a >> b;
        board[a][b] = -1;
    }

    BFS(board, srcX, srcY, 0, 0);

}

/*
3 4 2
1 2
3 4
1 1
 */