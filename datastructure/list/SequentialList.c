/**
 * 线性表的顺序储存, 
 * 线性表的顺序储存指的是用一组地址连续的储存单元依次储存线性表的数据对象, 也成为线性表的顺序表
 * 
 * 特点是逻辑上相邻的数据元素, 其物理次序上也是相邻的
 * 只要确定了顺序储存的线性表的起始位置, 线性表的任一数据都可随机存取, 所以线性表的顺序储存结构是 随机存取 的储存结构
 */


// 1. 线性表的也可以使用复杂数据类型
// typedef struct {
//     float coef;
//     int expn;
// } Polynomial;
// typedef Polynomial ElemType;
// typedef struct {
//     ElemType *elem;
//     int length;
// } SqList;

#include <stdio.h>
#include <string.h>

// 状态
#define Status int
#define OK 1
#define ERROR 0

// 2. 线性表的数据类型
#define ElemType int
// 线性表的最大储存容量
#define MAXSIZE 100

typedef struct {
    ElemType elem[MAXSIZE];  // 元素的起始位置
    int length;  // 线性表的长度
} SqList;

// 以下是一些操作

// 顺序表的初始化
Status InitList(SqList *l) {
    memset(l->elem, 0, sizeof(ElemType)*MAXSIZE);
    l->length = 0;
    return OK;
}

// 根据下标取值, 复杂度为O(1)
Status GetElem(SqList *l, int i, ElemType *e) {
    // 1. 判断位置是否正确, 小与0或者大于长度
    // 因为数组下表是从0开始的, 而实际使用的是从1开始的
    if(i < 1 || i > l->length) {
        return ERROR;
    }
    *e = l->elem[i-1];
    return OK;
}

// 查找, 
unsigned int LocateElem(SqList *l, ElemType e) {
    // 1. 线性表必须存在, 
    if(!l) {
        return ERROR;
    }
    int j;
    for(j = 0; j < l->length; j++) {
        if(e == l->elem[j]) {
            // 实际返回的下标加1
            return j+1;
        }
    }
    // 0 表示没找到
    return 0;
}

// 插入, 
Status ListInsert(SqList *l, int i, ElemType e) {
    // 1. 首先判断, 当前下标是否符合要求:
    //    1. 当前插入的下标小于1
    //    2. 当前的元素已经满了
    if(i < 1 || l->length == MAXSIZE) {
        return ERROR;
    }
    int j;
    for(j = l->length;j >= i; j--) {
        l->elem[j] = l->elem[j-1];
    }
    l->elem[j] = e;
    // 最后将长度加一
    ++(l->length);
    return OK;
}

// 删除
Status ListDelete(SqList *l, int i, ElemType *e) {
    // 1. 首先判断要删除的下标是否符合要求
    //    2. 当前要删除的下标小于1
    //    3. 当前要删除的下标大于线性表最大的长度
    if(i < 1 || i > l->length) {
        return ERROR;
    }
    int j;
    for(j = i; j <= l->length; j++) {
        l->elem[j-1] = l->elem[j];
    }
    --(l->length);
    *e = l->elem[j];
    return OK;
}

// 展示
void ListDisplay(SqList *l) {
    for(int i = 0; i<l->length; i++) {
        printf("l->elem[%d] = %d\n", i, l->elem[i]);
    }
}

// 测试
int main() {
    SqList sl;
    InitList(&sl);
    // ListDisplay(&sl);

    for(int i=1;i<=10; i++) {
        ListInsert(&sl, i, i);
    }

    ListInsert(&sl, 5, 50);
    ListDisplay(&sl);

    printf("val:50 index = %d\n", LocateElem(&sl, 50));

    ElemType delVal;
    ListDelete(&sl, 9, &delVal);
    printf("del val: %d\n", delVal);
    ListDisplay(&sl);
    return 0;
}