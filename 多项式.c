#include <stdio.h>

typedef struct node  {
	int a;
	int b;
	struct node *next;
}Node;

/*创建链表*/
Node * create_list(Node *pHead) {
	Node *pNew = NULL, *pEnd = pHead;
	int a, b;

	while(1) {
		printf("Input coefficient and index (0 to exit):\n");
		scanf("%d %d", &a, &b);

		if(!a) {  //结束
			pNew -> next = NULL;
			return pHead;
		}

		pNew = (Node *)malloc(Node);
		if(pNew == NULL) {
			printf("malloc error\n");
			return ;
		}
		pNew -> a = a;
		pNew -> b = b;

		pEnd -> next = pNew;
		pEnd = pNew;
		pNew -> next = NULL;
	}
}

int add_polynomial(Node *pHead1, Node *pHead2) {  //多项式相加
	Node *pHead = (Node *)malloc(Node);
	Node *p1 = pHead1 -> next;
	Node *p2 = pHead2 -> next;
	Noed *pNew = NULL, *ptmp1 = NULL, *ptmp2 = NULL;
	//int flag = 0;

	pHead -> next = NULL;

	while(p1 != NULL) {
		while(p2 != NULL) {
			//flag = 0;
			if(p1 -> b == p2 -> b) {
				pNew = (Node *)malloc(sizeof(Node));
				pNew -> a = p1 -> a + p2 -> a;
				pNew -> b = p1 -> b;
				//flag = 1;
			} else if(p1 -> b < p2 -> b) {
				ptmp1 = p1 -> next;//保存p1后的节点
				p1 -> next = p2;
	
				ptmp2 = p2 -> next;//保存p2后的节点
				p2 -> next = ptmp1;
	
				p2 = ptmp2;//p2指向第二个链表的下一个节点
			} else {  //p2插入到p1之前
				
			}
		}

		/*if(!flag) {
			ptmp1 = p1 -> next;//保存p1后的节点
			p1 -> next = p2;

			ptmp2 = p2 -> next;//保存p2后的节点
			p2 -> next = ptmp1;

			p2 = ptmp2;//p2指向第二个链表的下一个节点
		}*/
	}

}


int main (void) {
	//新建两个多项式的链表
	Node *pHead1 = (Node *)malloc(Node);
	Node *pHead2 = (Node *)malloc(Node);

	create_list(pHead1);
	create_list(pHead2);




	return 0;
}
