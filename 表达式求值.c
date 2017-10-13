#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSIZE_OPSET 100
#define MAXSIZE_DATA 50

/*运算符栈*/
typedef struct  {
    char opset[MAXSIZE_OPSET];
    int top;
}OPTR;

/*操作数栈*/
typedef struct {
    int data[MAXSIZE_DATA];
    int top;
}OPRD;

/*运算符相关函数*/
int push_optr(OPTR *S, char ch) {

    if(S -> top == MAXSIZE_OPSET - 1) {
        printf("error: stack full\n");
        exit(1);
    }

    S->top++;

    S->opset[S->top] = ch;

    return 0;
}

int pop_optr(OPTR *S, char *ch) {
    if(S->top == -1) {
        printf("error: stack empty\n");
        exit(1);
    }

    *ch = S->opset[S->top--];
    return 0;
}

/*操作数相关函数*/

int push_oprd(OPRD *S, int e) {
    if(S -> top == MAXSIZE_DATA - 1) {
        printf("error: stack full\n");
        exit(1);
    }

    S->data[++S->top] = e;
    return 0;
}

int pop_oprd(OPRD *S, int *e) {
    if(S->top == -1) {
        printf("error: stack empty\n");
        exit(1);
    }

    *e = S->data[S->top--];
    return 0;
}

/*优先级比较*/
int comp(char a, char b) {
    int m, n; //m存储a对应坐标，n存储b对应坐标
    char opset[7][7] = {
        {'>','>','<','<','<','>','>'},  
        {'>','>','<','<','<','>','>'},  
        {'>','>','>','>','<','>','>'},  
        {'>','>','>','>','<','>','>'},  
        {'<','<','<','<','<','=','0'},  
        {'>','>','>','>','0','>','>'},  
        {'<','<','<','<','<','0','='}};
    
    switch(a) {
        case '+': m = 0; break;
        case '-': m = 1; break;
        case '*': m = 2; break;
        case '/': m = 3; break;
        case '(': m = 4; break;
        case ')': m = 5; break;
        case '#': m = 6; break;
    }
    switch(b) {
        case '+': n = 0; break;
        case '-': n = 1; break;
        case '*': n = 2; break;
        case '/': n = 3; break;
        case '(': n = 4; break;
        case ')': n = 5; break;
        case '#': n = 6; break;
    }

    return opset[m][n];
}

/*运算*/
int operate(int a, int b, char opset) {
    switch(opset) {
        case '+' : return (a + b);
        case '-' : return (a - b);
        case '*' : return (a * b);
        case '/' : return (a / b);
    }
}

/*获取下一个数字(多位)或字符, 数字返回0, 字符返回1*/
int get_next(int *n) {
    char ch;
    *n = 0;
    while((ch = getchar()) == ' ') //跳过空格
        ;

    if(!isdigit(ch)) {
        *n = ch;
        return 1;
    }

    while(isdigit(ch)) {  //是数字
        *n = *n * 10 + (ch - '0');  //多位数字
        ch = getchar();
    }

    ungetc(ch, stdin);//将读出来的多余字符放回输入缓冲区

    return 0;
}

/*表达式的解析*/
int explain_expression(void) {
    int num, flag; //flag标记读到的是字符还是数据
    int m, n;//出栈的两个操作数
    char c;
    OPTR *optr;//运算符栈
    OPRD *oprd;//运算数栈

    /*初始化*/
    optr = (OPTR *)malloc(sizeof(OPTR));
    if(optr == NULL) {
        printf("malloc error\n");
        exit(1);
    }
    optr->top = -1;

    /*初始化*/
    oprd = (OPRD *)malloc(sizeof(OPRD));
    if(oprd == NULL) {
        printf("malloc error\n");
        exit(1);
    }
    oprd->top = -1;

    get_next(&num);//读取掉第一个#
    push_optr(optr, '#');

    flag = get_next(&num);

    while(num != '#' || optr->opset[optr->top] != '#') {
        if(!flag){  //是数字
            push_oprd(oprd, num);
            flag = get_next(&num);
        } else {  //是字符
            switch(comp(optr->opset[optr->top], num)) {
                case '>':  //栈顶元素优先级高
                    pop_oprd(oprd, &n);  //操作数出栈
                    pop_oprd(oprd, &m);
                    pop_optr(optr, &c);  //操作符出栈
                    push_oprd(oprd, operate(m, n, c));  //计算结果压栈
                    break;
                case '=':
                    pop_optr(optr, &c);
                    flag = get_next(&num);
                    break;
                case '<':
                    push_optr(optr, num);
                    flag = get_next(&num);
                    break;
            }
        }
    }
    return oprd->data[oprd->top];
}

int main(void) {
    printf("Please input a expression:\n");
    printf("\n\nResult = %d\n", explain_expression());

    return 0;
}
