//
// Created by Alexey on 03/11/2019.
//

#include <stdio.h>
#include <string.h>

//#define N 50

//int table[N][N][3] = {0};


int iteration(int ***table, const int *size) {
    int j;
    for (int a = 1; a < *size; a++)
        for (int b = 0; b < *size - a; b++) {
            j = b + a;
            for (int c = b; c < j; c++) {
                table[b][j][0] +=
                    table[b][c][2]*table[c + 1][j][0] + (table[b][c][0] + table[b][c][1])*table[c + 1][j][2];
                table[b][j][1] +=
                    table[b][c][0]*table[c + 1][j][0] + (table[b][c][0] + table[b][c][1])*table[c + 1][j][1];
                table[b][j][2] +=
                    table[b][c][1]*table[c + 1][j][0] + table[b][c][2]*(table[c + 1][j][1] + table[c + 1][j][2]);
            }
        }
    return table[0][*size - 1][0];
}
int main() {
    int n = 10;
    char ch[100];
    gets(ch);
    n = strlen(ch);
    int table[n][n][3] = {0};

    for (int i = 0; i <= n; i++)
        table[i][i][int(ch[i] - 'a')] = 1;

    printf("%d", iteration(table, n));
}