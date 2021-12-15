/**
 * 以下是单链表的实现
 * 因为线性表的顺序存储插入和删除一个元素时都需要移动多个元素, 所以为了减少插入和删除的开销, 我们可以使得表的元素不连续存储
 * 
 * 
 * 链表就是由一组任意的储存单元来储存线性表的数据元素, 每个数据元素称之为 结点
 * 每个结点中包含两部分: 一是当前数据, 二是保存后继元素的地址(next指针); 就这样, 单链表就是由一个一个的指针彼此连接起来
 * 
 * 
 * 如果链表 List指针 直接指向第一个元素, 那么*List表示第一个元素, *(List->next) 表示第二个元素, 为了将两者保持一致, 通常在初始化链表时, 会添加一个头结点
 * 
 * 头结点的好处: 1. 可以使用头结点的数据域来保存链表的长度
 *              2. 可以使得第一个元素和第二个元素的获取方式都保持一致(使用next域)
 * 
 * 添加头结点后, 我们一般将第一个元素称之为 首元结点
 */
#include <stdlib.h>
#include <stdio.h>

#include "SingleLinkedList.h"

// 初始化, 这里必须传入单链表的指针, 否则改变的只是函数中的副本, 无法改变原值. 
Status InitList(SingleLinkedList *list) {
    // 初始化一个头结点, 并将头指针 指向头结点
    // 注意在这里使用malloc, 到时候一定要记得使用free释放 TODO
    Node* node = (Node*)malloc(sizeof(Node));
    if(!node) {
        return ERROR;
    }

    // 将头结点的指针域初始化为NULL
    node->next = NULL;
    *list = node;
    return OK;
}

// 判断链表是否为空; 
// 带头结点的单链表, 通过判断链表的头节点的指针域是否为空
// 不带头结点的单链表, 通过判断头指针是否指向NULL 来判断是否是空表
int ListIsEmpty(SingleLinkedList list) {
    return list->next == NULL;
}

/**
 * 取值, 根据下标来取值
 * list: 单链表(头指针)
 * index: 位置; 从1开始
 * e: 返回找到的元素
 */
Status GetElem(SingleLinkedList list, int index, ElemType *e) {
    // 计数器
    unsigned int curIdx = 1;
    Node *curNode = list->next;
    while(curNode && curIdx < index) {
        curNode = curNode->next;
        curIdx++;
    }

    // curNode为NULL, 说明到头了
    if(!curNode || curIdx >= index) {
        return ERROR;
    }

    *e = curNode->data;
    return OK;
}

/**
 * 按值查找
 * list: 要查找的链表
 * e: 查找的值
 * 返回值: 查找的值在当前链表中的位置
 */
unsigned int LocateElem(SingleLinkedList list, ElemType *e) {
    // 计数器
    unsigned int returnVal = -1;
    unsigned int curIdx = 1;
    Node *curNode = list->next;

    while(curNode && (curNode->data != *e)) {
        curNode = curNode->next;
        curIdx++;
    }

    // curNode为NULL, 说明到头了, 还未找到
    if(curNode && (curNode->data == *e)) {
        returnVal = curIdx;
    }

    return returnVal;
}

/**
 * 按值查找
 * list: 要查找的链表
 * e: 查找的值
 * 返回值: 值相同的结点地址
 */
Node *LocateElemGetNode(SingleLinkedList list, ElemType *e) {
    Node *curNode = list->next;
    while(curNode && (curNode->data != *e)) {
        curNode = curNode->next;
    }

    return curNode;
}

/**
 * 任意位置插入
 */
Status InsertElem(SingleLinkedList list, int index, ElemType *e) {
    // 首先要找到 index-1 位置上的结点(该位置的前驱结点)
    unsigned int curIdx = 0;
    Node *curNode = list;

    while(curNode && curIdx < index-1) {
        curNode = curNode->next;
        curIdx++;
    }

    if(!curNode || curIdx > index-1) {
        return ERROR;
    }

    Node *tmp = (Node*)malloc(sizeof(Node));
    if(!tmp) {
        return ERROR;
    }

    // 新结点的指针域 指向 老的index位置的结点
    tmp->next = curNode->next;
    // index-1位置上的结点的指针域指向 新结点
    curNode->next = tmp;
    return OK;
}

/**
 * 根据下标来删除
 */
Status DeleteElemByIndex(SingleLinkedList list, int index) {
    // 首先找到index位置的前驱结点
    // 从头结点开始找
    unsigned int curIdx = 0;
    Node *curNode = list;
    while(curNode && (curIdx < index-1)) {
        curNode = curNode->next;
        curIdx++;
    }

    if(!curNode || curIdx > index-1) {
        return ERROR;
    }

    // 此时 curNode就是 位置index 的前驱结点
    Node *tmp = curNode->next;
    curNode->next = tmp->next;
    free(tmp);
    return OK;
}

/**
 * 根据值来删除
 */
Status DeleteElemByElem(SingleLinkedList list, ElemType *e) {
    // 首先找到值为*e的 前驱结点
    unsigned int curIdx = 0;
    Node *curNode = list;
    // 比较的是下一结点
    while(curNode->next && (curNode->next->data != *e)) {
        curNode = curNode->next;
        curIdx++;
    }

    if(!curNode->next) {
        return ERROR;
    }

    Node *tmp = curNode->next;
    curNode->next = tmp->next;
    free(tmp);
    return OK;
}

void DestroyList(SingleLinkedList *list) {
    Node *curNode = NULL;
    while(*list) {
        curNode = *list;
        *list = curNode->next;
        free(curNode);
    }
}

int main() {
    SingleLinkedList list = NULL;
    // 1. 初始化单链表
    InitList(&list);

    printf("%d\n", ListIsEmpty(list));
}