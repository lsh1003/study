
#ifndef __SingleListedList_h__
#define __SingleListedList_h__

// 以下是头文件的内容, 主要包括类型(type), 位置(position)， 函数的原型定义在.h头文件中

#define Status int
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

// 定义链表以及链表的一些操作
typedef int ElemType;
typedef struct Node{
    ElemType data;  // 数据域
    struct Node *next;  // 指针域, 指向后继元素
} Node, *SingleLinkedList;

// 1. 链表初始化
Status InitList(SingleLinkedList *list);

// 2. 判断链表是否为空, 通过判断头节点的指针域是否为空
int ListIsEmpty(SingleLinkedList list);

// 销毁链表
void DestroyList(SingleLinkedList *list);

// 清空链表, 保留头结点, 将其他元素都清空
void MakeEmpty(SingleLinkedList *list);

// 根据下标来取值
Status GetElem(SingleLinkedList list, int index, ElemType *e);

// 按值查找, 返回下标
int LocateElem(SingleLinkedList list, ElemType e);

// 按值查找, 返回结点
Node *LocateElemGetNode(SingleLinkedList list, ElemType e);

// 插入
Status InsertElem(SingleLinkedList list, int index, ElemType e);

// 根据下标来删除
Status DeleteElemByIndex(SingleLinkedList list, int index);

// 通过值来删除 结点
Status DeleteElemByElem(SingleLinkedList list, ElemType e);

// 头插入
Status CreateListByHead(SingleLinkedList *list, int n);

// 尾插入
Status CreateListByLast(SingleLinkedList *list, int n);

// 翻转链表
void ReverseList(SingleLinkedList *list);

#endif