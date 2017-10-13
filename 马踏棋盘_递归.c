#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAP_X 6
#define MAP_Y 6
#define MAXSIZE (MAP_X * MAP_Y)

int map[MAP_X][MAP_Y] = {0};
int next[8][2] = {  {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, 
                    {2, -1}, {1, -2}, {-1, -2}, {-2, -1} };
int num;

//存储路径
typedef struct {
    int data[MAP_X * MAP_Y][2];
    int top;
}STACK;

/*初始化*/
STACK * init(STACK *S) {
    S = (STACK *)malloc(sizeof(STACK));
    if(!S) {
        printf("malloc error\n");
        exit(1);
    }

    S -> top = -1;
    return S;
}

STACK * Push(STACK *S, int x, int y) {
    if(S->top == MAP_X * MAP_Y - 1) {
        printf("error: stack full\n");
        exit(1);
    }

    S->top++;
// printf("111\n");
    S->data[S->top][0] = x;
// printf("777\n");
    S->data[S->top][1] = y;

    return S;
}

STACK *Pop(STACK *S) {
    if(S->top == -1) {
        printf("error: stack empty\n");
        exit(1);
    }

    S->top--;
    return S;
}

int print(STACK *S) {
    int loop, loop1;
    int path[MAP_X][MAP_Y] = {0};  //以图的形式存储路径

    printf("\npath %d:\n", ++num);
    for(loop = 0; loop < MAXSIZE; loop++) {
        path[ S->data[loop][0] ][ S->data[loop][1] ] = loop + 1;
    }

    for(loop = 0; loop < MAP_X; loop++) {
        for(loop1 = 0; loop1 < MAP_Y; loop1++) {
            printf("%4d", path[loop][loop1]);
        }
        printf("\n");
    }
}

void dfs(STACK *path, int x, int y) {
    int tx, ty, loop;
     
    if(path->top == MAXSIZE - 1) {
        print(path);
        return ;
    }

    for(loop = 0; loop < 8; loop++) {
        tx = x + next[loop][0];  //下一步所在位置
        ty = y + next[loop][1];


        if(tx >= 0 && ty >= 0 && tx < MAP_X && ty < MAP_Y && !map[tx][ty]) {  //未越界
            Push(path, tx, ty);
// printf("tx = %d, ty = %d, top = %d\n", tx, ty, path->top);

            map[tx][ty] = 1;  //设置该点已经走过

            dfs(path, tx, ty);  //递归

            Pop(path);  //出栈，回退到上个位置
// printf("x = %d, y = %d, top = %d, loop = %d\n", tx, ty, path->top, loop);
            map[tx][ty] = 0;  //设置该点未走过
        }
    }
}

int main (void) {
    STACK *path;
    int x, y, flag = 0;
    path = init(path);

    do {
        printf("Please input the starting position:\n");
        scanf("%d%d", &x, &y);

        if(x < 0 || y < 0 || x >= MAP_X || y >= MAP_Y) {
            printf("ERROR: inputing out of range\n");
            sleep(2);
            system("clr");
        } else {
            flag = 1;
        }
    }while(!flag);

    map[x][y] = 1;
    Push(path, x, y);

    dfs(path, x, y);

    return 0;
}
