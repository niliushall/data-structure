#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct {
    int row, col, value;
}Triple;

typedef struct {
    Triple data[MAXSIZE + 1];
    int rows, cols, nums;
}TSMatrix;

int fast_transpose_TSMatrix(TSMatrix *A, TSMatrix *B) {
    int num[MAXSIZE] = {0}, position[MAXSIZE] = {0};
    int loop, t, q;

    //对B初始化
    B->rows = A->cols;
    B->cols = A->rows;
    B->nums = A->nums;

    if(!B->nums)
        return 1;

    for(loop = 1; loop <= A->nums; loop++)
        num[A->data[loop].col]++;

    position[1] = 1;
    for(loop = 2; loop <= MAXSIZE; loop++)
        position[loop] = position[loop - 1] + num[loop - 1];

    for(loop = 1; loop <= A->nums; loop++) {
        t = A->data[loop].col;
        q = position[t];
        B->data[q].row = A->data[loop].col;
        B->data[q].col = A->data[loop].row;
        B->data[q].value = A->data[loop].value;
        position[t]++;

    }

}

int print(TSMatrix *B) {
    int i, j, k = 1;
    for(i = 1; i <= B->rows; i++) {
        for(j = 1; j <= B->cols; j++) {
            if(i == B->data[k].row && j == B->data[k].col) {
                printf("%-5d", B->data[k].value);
                k++;
            } else { 
                printf("0    ");
            }
        }
        printf("\n");
    }
}

int main (void) {
    int row, col, i, j, k = 0;
    int array[10][10];
    TSMatrix *A = (TSMatrix *)malloc(sizeof(TSMatrix));
    TSMatrix *B = (TSMatrix *)malloc(sizeof(TSMatrix));

    printf("Please input array`s row, col:\n");
    scanf("%d%d", &row, &col);

    A->rows = row;
    A->cols = col;

    printf("Please input array(%d * %d):\n");
    for(i = 1; i <= row; i++)
        for(j = 1; j <= col; j++) {
            scanf("%d", &array[i][j]);
            if(array[i][j]) {
                A->data[++k].col = j;
                A->data[k].row = i;
                A->data[k].value = array[i][j];
            }
        }

    A->nums = k;

    fast_transpose_TSMatrix(A, B);
    print(B);

    return 0;
}
