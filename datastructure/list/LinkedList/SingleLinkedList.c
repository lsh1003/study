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

// 判断链表是否为空; 通过判断链表的头节点的指针域是否为空
int ListIsEmpty(SingleLinkedList list) {
    return list->next == NULL;
}

/**
 * 取值, 根据下标来取值
 * list: 单链表
 * index: 位置; 从1开始, 而实际下标为index-1
 * e: 返回找到的元素
 */
Status GetElem(SingleLinkedList list, int index, ElemType *e) {
    // 计数器, 表示链表中第几个元素
    unsigned int j = 1;
    Node *p = list->next;
    while(p && j<index) {
        p = p->next;
        ++j;
    }

    if(!p || j >= index) {
        return ERROR;
    }
    e = p->data;
    return OK;
}

/**
 * 按值查找
 * list: 要查找的链表
 * e: 查找的值
 * 返回值: 查找的值在当前链表中的位置
 */
unsigned int LocateElem(SingleLinkedList list, ElemType e) {
    unsigned int returnVal = -1, j = 1;
    // 首元结点
    Node *p = list->next;
    // 未结束, p存在; 并且p的数据域不等于e, 则执行循环体
    while(p && p->data != e) {
        p = p->next;
        j++;
    }
    
    if(p && j>0) {
        returnVal = j;
    }
    return returnVal;
}

Status InsertElem(SingleLinkedList list, int index, ElemType e) {
    int j = 1;
    Node *p = list->next;
    while(p && j < index) {
        j++;
        p = p->next;
    }

    // 1, 插入位置不合法, 返回ERROR
    if(!p || j >= index) {
        return ERROR;
    }
    
    // 2. 插入元素
    Node *insertedNode = (Node*)malloc(sizeof(Node));
    if(!insertedNode) {
        // 申请失败
        return ERROR;
    }

    insertedNode->data = e;
    insertedNode->next = p->next;
    p->next = insertedNode;
    return OK;
}

int main() {
    SingleLinkedList list = NULL;
    InitList(&list);
    return 0;
}
