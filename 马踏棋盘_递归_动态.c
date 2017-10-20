#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAP_X 5
#define MAP_Y 5
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
        exit (1);
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
    S->data[S->top][0] = x;
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

int print_dynamic(int x, int y, int state) {
    int i, j;

    system("clear");
    for(i = 0; i < MAP_X; i++) {
        for(j = 0; j < MAP_Y; j++) {
            if(i == x && j == y)
                printf("  ");
            else if(map[i][j])
                printf("\033[1;36m* \033[0m");
            else
                printf("- ");
        }
        printf("\n");
    }
    usleep(300000);

    system("clear");
    for(i = 0; i < MAP_X; i++) {
        for(j = 0; j < MAP_Y; j++) {
            if(i == x && j == y) {
                if(state)
                    printf("\033[1;36m* \033[0m");
                else
                    printf("\033[1;31m* \033[0m");
            }
            else if(map[i][j])
                printf("\033[1;36m* \033[0m");
            else
                printf("- ");
        }
        printf("\n");
    }
    usleep(300000);
}

void dfs(STACK *path, int x, int y, int choice) {
    int tx, ty, loop;
     
    if(path->top == MAXSIZE - 1) {
        if(choice == 1) {
            print(path);
            return ;
        } else if(choice == 2) {
            print_dynamic(x, y, 1);
            exit(0);
        }
    }

    for(loop = 0; loop < 8; loop++) {
        tx = x + next[loop][0];  //下一步所在位置
        ty = y + next[loop][1];


        if(tx >= 0 && ty >= 0 && tx < MAP_X && ty < MAP_Y && !map[tx][ty]) {  //未越界
            Push(path, tx, ty);

            map[tx][ty] = 1;  //设置该点已经走过

            if(choice == 2)
                print_dynamic(tx, ty, 1);

            dfs(path, tx, ty, choice);  //递归

            Pop(path);  //出栈，回退到上个位置
            map[tx][ty] = 0;  //设置该点未走过

            if(choice== 2)
                print_dynamic(x, y, 0);
        }
    }
}

int menu(void) {
    int choice;

    system("clear");
    printf("=================================\n");
    printf("===                           ===\n");
    printf("===       1.all path          ===\n");
    printf("===       2.print dynamicly   ===\n");
    printf("===                           ===\n");
    printf("=================================\n");
    printf("\nPlease input your choice:");
    scanf("%d", &choice);

    if(choice != 1 && choice != 2) {
        printf("input error\n");
        exit(0);
    }
    return choice;
}

int main (void) {
    STACK *path;
    int x, y, flag = 0, choice;
    path = init(path);

    choice = menu();

    do {
        printf("Please input the starting position:\n");
        scanf("%d%d", &x, &y);

        if(x < 0 || y < 0 || x >= MAP_X || y >= MAP_Y) {
            printf("ERROR: inputing out of range\n");
            sleep(2);
            system("clear");
        } else {
            flag = 1;
        }
    }while(!flag);

    map[x][y] = 1;
    Push(path, x, y);

    dfs(path, x, y, choice);

    return 0;
}