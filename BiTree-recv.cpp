/*************************************************************************
	> File Name: BiTree.cpp
	> Author: wang liang
	> Mail: sdwllinux@gmail.com
	> Created Time: 2017年11月09日 星期四 14时35分33秒
 ************************************************************************/

#include<iostream>
using namespace std;

typedef struct Node {
	char data;
	struct Node *LChild;
	struct Node *RChild;
}BiNode, *BiTree;

void Visit(char data) {
	cout << data << ' ';
}

void preOrder(BiTree root) {
	if(!root)
		return ;
	Visit(root->data);
	preOrder(root->LChild);
	preOrder(root->RChild);
}

void inOrder(BiTree root) {
	if(!root)
		return ;
	inOrder(root->LChild);
	Visit(root->data);
	inOrder(root->RChild);
}

void postOrder(BiTree root) {
	if(!root)
		return ;
	postOrder(root->LChild);
	postOrder(root->RChild);
	Visit(root->data);
}

void levelOrder {
	
}

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

int main() {
	BiTree root;

	CreateBiTree(&root);

	cout << "preOrder : ";
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

