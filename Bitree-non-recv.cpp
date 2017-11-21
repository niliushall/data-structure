/*************************************************************************
	> File Name: Bitree-non-recv.cpp
	> Author: wang liang
	> Mail: sdwllinux@gmail.com
	> Created Time: 2017年11月09日 星期四 16时08分23秒
 ************************************************************************/

#include<iostream>
using namespace std;

#define MAX 50

typedef struct Node {
	char data;
	struct Node *LChild;
	struct Node *RChild;
}BiNode, *BiTree;

typedef struct node {
	BiTree stack[MAX];
	int top;
}SeqStack;

SeqStack *InitStack(SeqStack **S) {
	*S = (SeqStack *)malloc(sizeof(SeqStack));
	if(!(*S)) {
		cout << "Malloc error\n";
		exit(0);
	}

	(*S)->top = -1;

	return *S;
}

SeqStack *Push(SeqStack *S, BiTree p) {
	if(S->top == MAX - 1)
		return NULL;
	S->top++;
	S->stack[S->top] = p;

	return S;
}

SeqStack *Pop(SeqStack *S, BiTree *p) {
	if(S->top == -1)
		return NULL;
	*p = S->stack[S->top];
	S->top--;

	return S;
}

int isEmpty(SeqStack *S) {
	if(S->top == -1)
		return 1;
	else
		return 0;
}

void Top(SeqStack *S, BiTree *p) {
	if(S->top == -1)
		*p = NULL;
	else 
		*p = S->stack[S->top];
}

//访问节点
void Visit(char data) {
	cout << data << ' ';
}

//创建二叉树
// void createBiTree(BiTree root) {
// 	char ch;
// 	BiTree p = root;
// 	BiTree pre = root;

// 	while(cin.get(ch)) {
// 		// if(ch == '\n')
// 		// 	break;
		
// 		if(ch == '^') {
// 			p = NULL;
// 		} else {
			
// 		}
// 	}
// }


void CreateBiTree(BiTree *root) {
	char ch;
	ch = cin.get();

	if(ch == '^') {
		*root = NULL;
	} else {
		*root = (BiTree)malloc(sizeof(BiNode));
		(*root)->data = ch;
		CreateBiTree(&((*root)->LChild));
		CreateBiTree(&((*root)->RChild));
	}
}

void preOrder(BiTree root) {
	SeqStack *S;
	BiTree p;
	InitStack(&S);
	p = root;

	while(p != NULL || !isEmpty(S)) {
		while(p != NULL) {
			Visit(p->data);
			Push(S, p);
			p = p->LChild;
		}

		if(!isEmpty(S)) {
			Pop(S, &p);
			p = p->RChild;
		}
	}
}

void inOrder(BiTree root) {
	SeqStack *S;
	BiTree p;
	InitStack(&S);
	p = root;

	while(p != NULL || !isEmpty(S)) {
		while(p != NULL) {
			Push(S, p);
			p = p->LChild;
		}
		if(!isEmpty(S)) {
			Pop(S, &p);
			Visit(p->data);
			p = p->RChild;
		}
	}
}

void postOrder(BiTree root) {
	SeqStack *S;
	BiTree p, q;
	InitStack(&S);
	p = root;
	q = NULL;
	
	while(p != NULL || !isEmpty(S)) {
		while(p != NULL) {
			Push(S, p);
			p = p->LChild;
		}

		if(!isEmpty(S)) {
			Top(S, &p);
			p = p->RChild;
			if(p == NULL || p == q) {
				Pop(S, &p);
				Visit(p->data);
				q = p;
				p = NULL;
			}
		}
	}
}

int main() {
	BiTree root;
	CreateBiTree(&root);

	cout << "preOrder : \n";
	preOrder(root);
	cout << endl;

	cout << "inOrder : ";
	inOrder(root);
	cout << endl;

	cout << "postOrder : ";
	postOrder(root);
	cout << endl;

    return 0;
}
