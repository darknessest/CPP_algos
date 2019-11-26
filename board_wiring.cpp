//
// Created by Alexey on 26/11/2019.
//

#include<iostream>
#include<cstdlib>
#include<queue>

#define MAXSIZE 100
using namespace std;

typedef struct point {
  int x;
  int y;
} point;

point startP, endP;                    //起点，终点
int n;                              //大小
int graph[MAXSIZE][MAXSIZE];        //二维矩阵
int total = 0;                        //总步数

void input();                       //输入
bool find();                        //计算
void output();                      //输出

int main() {
    input();
    find();
    output();
    return 0;
}

void input() {
    cin >> n;
    cin >> startP.x >> startP.y;
    cin >> endP.x >> endP.y;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> graph[i][j];                                             //1表示墙，0表示空
        }
    }
}

bool find() {
    if (startP.x == endP.x && startP.y == endP.y) {
        total = 0;
        return true;
    }
    queue<point> q;
    graph[startP.x][startP.y] = 2;
    point top;
    top.x = startP.x;
    top.y = startP.y;
    point temp;
    temp.x = 0;
    temp.y = 0;
    int numberOfDirection = 4;
    point direction[4];
    direction[0].y = 1;
    direction[0].x = 0;
    direction[1].y = 0;
    direction[1].x = 1;
    direction[2].y = -1;
    direction[2].x = 0;
    direction[3].y = 0;
    direction[3].x = -1;
    do {
        for (int i = 0; i < numberOfDirection; i++) {
            temp.x = top.x + direction[i].x;
            temp.y = top.y + direction[i].y;
            if (graph[temp.x][temp.y] == 0 && temp.x >= 1 && temp.x <= n && temp.y >= 1 && temp.y <= n) {
                graph[temp.x][temp.y] = graph[top.x][top.y] + 1;
                if (temp.x == endP.x && temp.y == endP.y) {
                    break;
                }
                q.push(temp);
            }

        }
        if (temp.x == endP.x && temp.y == endP.y) {
            break;
        }
        if (q.empty()) {
            return false;
        }
        top = q.front();
        q.pop();
    } while (1);
    total = graph[endP.x][endP.y] - 2;
    return true;
}

void output() {
    cout << total << endl;
}
/*
input
7
3 2
4 6
0 0 1 0 0 0 0
0 0 1 1 0 0 0
0 0 0 0 1 0 0
0 0 0 1 1 0 0
1 0 0 0 1 0 0
1 1 1 0 0 0 0
1 1 1 0 0 0 0

output
9
*/