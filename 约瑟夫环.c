#include <stdio.h>
#include <stdlib.h>

typedef struct people{
    int num;
    int passwd;
    struct people *next;
}Node;

int number; //剩余人数

/*创建链表，存储密码等信息*/
int getPasswd(Node *pHead) {
    int i;
    Node *pNew = NULL ,*pEnd = pHead;
    int password;

    printf("Input the number of people:\n");
    scanf("%d", &number);

    printf("Input initial password: ");
    scanf("%d", &password);

    for(i = 0; i < number; i++) {
        pNew = (Node *)malloc(sizeof(Node));

        pNew -> num = i+1;
        printf("Input No.%d passwd:\n", i+1);
        scanf("%d", &pNew -> passwd);

        pEnd -> next = pNew;
        pEnd = pNew;
    }

    pNew -> next = pHead -> next; //循环链表

    return password;
}

void deleteNode(Node *pHead, int passwd) {
    int n, i;
    Node *p = pHead, *pre, *q;

    printf("\nDelete order:\n");

    //只有一人时直接
    if(number == 1) {
        printf("1 ");
        return;
    }

    while(passwd--) {
        pre = p;
        p = p -> next;
    }

    printf("%d ", p -> num);
    pre -> next = p -> next;
    n = p -> passwd;
    p = p -> next;
    number--;

    while(number-- > 0) {
        while(--n) {
            pre = p;
            p = p -> next;
        }

        printf("%d ", p -> num);
        n = p -> passwd; //保存密码

        pre -> next = p -> next; //删除
        q = p; //暂存被删除节点，用于释放
        p = p -> next;
        free(q);

        //只剩一人时
        if(number == 1) {
            printf("%d\n", p -> num);
            return ;
        }
    }
}

int main (void) {
    Node *pHead = NULL;
    pHead = (Node *)malloc(sizeof(Node));
    pHead -> next = NULL;
    int passwd;

    passwd = getPasswd(pHead);
    deleteNode(pHead, passwd);
    
    return 0;
}
