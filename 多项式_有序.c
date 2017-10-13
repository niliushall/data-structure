#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int a;
    int b;
    struct node *next;
}Node;

void create_list(Node *pHead) {
    Node *pre = pHead, *pNew = NULL;
    int a, b;
    printf("Input coefficient and index (0 to exit):\n");

    while(1) {
        scanf("%d %d", &a, &b);
        
        if(!a) {  //输入结束
            return;
        }

        pNew = (Node *)malloc(sizeof(Node));
        if(pNew == NULL) {  //内存客空间申请失败
            printf("malloc error\n");
            return;
        }

        //尾插法
        pNew -> a = a;
        pNew -> b = b;
        pre ->  next = pNew;
        pre = pNew;
    }
    pNew -> next = NULL;
    printf("\n");
}

//多项式相乘时相同项的处理，采用插入法
void insert(Node *pHead, int ta, int tb) {
    Node *p = pHead -> next, *pNew, *pEnd = pHead;

    while(p != NULL) {
        if(p -> b == tb) {
            p -> a += ta;
            return;
        }
        pEnd = p;
        p = p -> next;
    }

    //尾插
    pNew = (Node *)malloc(sizeof(Node));
    pNew -> a = ta;
    pNew -> b = tb;
    pEnd -> next = pNew;

    pNew -> next = NULL;
}

//合并多项式，加、减
void Merge(Node *pHead1, Node *pHead2, int choice) {
    Node *p1 = pHead1 -> next, *p2 = pHead2 -> next, *p = pHead1;
    Node *ptmp1 = NULL, *ptmp2 = NULL;
    
    while(p1 != NULL && p2 != NULL) {
        if(p1 -> b > p2 -> b) {  //p2插到p1前面
            ptmp1 = p -> next;
            p -> next = p2;

            ptmp2 = p2 -> next;
            p2 -> next = p1;

            p2 = ptmp2;
            p1 = ptmp1;
            p = p -> next;
        } else if(p1 -> b == p2 -> b) {
            if(choice == 1)
                p1 -> a += p2 -> a;
            else if(choice == 2)
                p1 -> a -= p2 -> a;
            p2 = p2 -> next;
        } else  {
            p = p -> next;
            p1 = p1 -> next;
        }
    }

    if(p1 == NULL)  {
        p -> next = p2;
    }
}

//多项式相乘
Node * Multiply(Node *pHead1, Node *pHead2) {
    Node *p1 = pHead1 -> next, *p2 = pHead2 -> next, *pNew;
    Node *pHead = (Node *)malloc(sizeof(Node));
    pHead -> next = NULL;

    while(p1 != NULL) {
        p2 = pHead2 -> next;

        while(p2 != NULL) {
            pNew = (Node *)malloc(sizeof(Node));
            if(pNew == NULL) {  //申请内存出错
                printf("malloc error\n");
                exit(0);
            }

            pNew -> a = p1 -> a * p2 -> a;
            pNew -> b = p1 -> b + p2 -> b;

            insert(pHead, pNew -> a, pNew -> b);
            p2 = p2 -> next;
        }
        p1 = p1 -> next;
    }

    return pHead;
}

/*多项式求导*/
int deri(Node * pHead) {
    Node *p = pHead -> next;
    while(p != NULL) {
        if(!p -> b) {
            p -> a = 0;
        } else {
            p->a *= p->b;
            p->b--;
            printf("=%d=\n", p->b);
        }
        p = p -> next;
    }
}


//输出多项式
void print_list(Node *pHead) {
    Node *p = pHead -> next;
    int n = 0;

    printf("Result:\n");

    while(p != NULL) {
        if(!p -> a && p -> next == NULL) {
            printf("0\n");
            return ;
        }
        if(!p -> a) { //系数为0
            p = p -> next;
            continue;
        }
        if(!p -> b) { //指数为0
            printf("%d ", p -> a);
        } else {
            if(p -> a == 1) {
                printf("X");
            } else if(p -> a < 0) {
                printf("%dX", p -> a);
            } else {
                if(!n) {
                    printf("%dX", p -> a);
                } else {
                    printf("+%dX", p -> a);
                }
            }

            if(p->b != 1) //指数不为1
                printf("^%d", p -> b);
        }

        n++;
        p = p -> next;
    }
    
    printf("\n");
}

int getChoice(void) {
    int choice;

    while(1) {
        printf("================================\n");
        printf("====        1.add           ====\n");
        printf("====        2.subtract      ====\n");
        printf("====        3.multiply      ====\n");
        printf("====        4.derivation    ====\n");
        printf("====        0.exit          ====\n");
        printf("================================\n");
        printf("\nInput choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        if(choice == 1 || choice == 2 || choice == 3 || choice == 4 || !choice) {
            return choice;
        } else {
            printf("input error, press [enter] to continue...\n");
            getchar();
            getchar();
        }
    }
}

int main (void) {
    Node *pHead1 = (Node *)malloc(sizeof(Node));
    Node *pHead2 = (Node *)malloc(sizeof(Node));
    Node *pHead_deri = NULL; //存储求导后链表
    pHead1 -> next = NULL;
    pHead2 -> next = NULL;
    int choice;

    choice = getChoice();
    switch(choice) {
        case 1 :
        case 2 :create_list(pHead1);
                create_list(pHead2);
                Merge(pHead1, pHead2, choice); break;
        case 3 :create_list(pHead1);
                create_list(pHead2);
                pHead1 = Multiply(pHead1, pHead2); break;
        case 4 :create_list(pHead1);print_list(pHead1);
                deri(pHead1);break;
    }

    print_list(pHead1);
    return 0;
}