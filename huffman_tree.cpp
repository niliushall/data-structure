#include<iostream>
#include<string>
using namespace std;

#define N 30 //哈夫曼树的叶子结点数

typedef struct  {
    int value;
    int parent, lchild, rchild;
}HTNode, huffmanTree[2 * N - 1];

void Select(huffmanTree ht, int n, int & x1, int & x2) {
    int i, min, _min;
    _min = 9999999;  //存储次小值 (x2存储次小值位置)
    min = 9999999;  //存储最小值 (x1存储最小值位置)
    x1 = x2 = 0;

    for(i = 0; i < n; i++) {
        if(!ht[i].parent) {    
            if(min >= ht[i].value) {
                _min = min;
                min = ht[i].value;
                x2 = x1;
                x1 = i;
            } else if (_min > ht[i].value) {
                _min = ht[i].value;
                x2 = i;
            }
        }
    }
}

// 创建哈夫曼树
void create_huffmantree(huffmanTree ht, int v[], int n) {
    int i, m = 2*n-1;
    int x1, x2;

    for(i = 0; i < n; i++)
        ht[i] = {v[i], 0, 0 , 0};
    for( ; i < m; i++)
        ht[i] = {0, 0, 0 , 0};

    for(i = n; i < m; i++) {
        Select(ht, i, x1, x2);

        ht[i].value = ht[x1].value + ht[x2].value;
        ht[i].lchild = x1;
        ht[i].rchild = x2;
        ht[x1].parent = i;
        ht[x2].parent = i;
    }
}

//获取哈夫曼编码
void create_huffmanCode(huffmanTree ht, string huffmanCode[], int n) {
    string tmp, rev;
    int start, p, j, k, current;

    for(int i = 0; i < n; i++) {
        tmp = rev = "";
        p = ht[i].parent;
        current = i;
        k = 0;

        while(p) {
            if(ht[p].lchild == current)
                tmp +=  '0';
            else if(ht[p].rchild == current)
                tmp += '1';
            current = p;
            p = ht[p].parent;
        }

        for(int i = tmp.size() - 1; i >= 0; i--)
            rev += tmp[i];

        huffmanCode[i] = rev;
    }
}

//读取权值数组
void get_value(int value[], int n) {
    cout << "Please input values :\n";
    
    for(int i = 0; i < n; i++) {
        cin >> value[i];
    }
}

void showHuffmanCode(huffmanTree ht, string huffmanCode[], int n) {
    for(int i =0 ; i < n ;i++) {
        cout << ht[i].value << " : ";
        cout << huffmanCode[i] << endl;
    }
}

int main() {
    int n;
    int value[N];
    huffmanTree ht;

    cout << "Please input the number of value:" << endl;
    cin >> n;
    string huffmanCode[n];

    get_value(value, n);
    create_huffmantree(ht, value, n);
    create_huffmanCode(ht, huffmanCode, n);
    showHuffmanCode(ht, huffmanCode, n);

    return 0;
}

// int find_even(BiTree root) {
//     int count_l = 0, count_r = 0;
//     int count = 0;

//     if(!root->lchild || !root->rchild)
//         return 0;
//     count_l = find_even(root->lchild);
//     count_r = find_even(root->rchild);

//     return (count_l + count_r);
// }

// void swapTree(BiTree root) {
//     Bitree temp;

//     if(!root)
//         return;
//     tmp = root->lchild;
//     root->lchild = root->rchild;
//     root->rchild = temp;

//     swapTree(root->lchild);
//     swapTree(root->rchild);
// }