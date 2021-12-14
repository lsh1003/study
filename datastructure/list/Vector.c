#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./Vector.h"

static unsigned int dataLen = 0;

/**
 * 创建一个向量
 * malloc申请空间内存
 */
Status CreateInstance(Vector *vector) {
    unsigned int size = InitLen * sizeof(ElemType);
    dataLen = InitLen;

    // malloc 之后一定要free掉
    // 1. 申请初始容量个元素的长度
    ElemType* tmp = (ElemType*)malloc(size);

    if(!tmp) {
        return ERROR;
    }
    vector->data = tmp;
    memset(vector->data, 0, size);

    // 2. 数据的长度初始为0
    vector->length = 0;
    return OK;
}

/**
 * 销毁
 */
Status DestroyInstance(Vector *vector) {
    free(vector->data);
    vector = NULL;
    return OK;
}

/**
 * 插入元素
 * 1. 首先判断是否有剩余的空间可以插入, 如果没有剩余的空间了, 则需要使用realloc动态扩容,
 */
Status InsertElem(Vector *vector, ElemType elem) {
    if(vector->length == dataLen) {
        // 表示现在已申请的内容区域已经满了, 不够插入了, 则需要扩容
        unsigned int growLen = InitLen, capcity;
        ElemType* tmp = NULL;
        // 如果未申请到想要的内存(比如硬盘空间不足), 并且增长量不能为0, 则继续申请, 将容量缩小一倍
        while(!tmp && growLen) {
            growLen = growLen/2;
            capcity = InitLen + growLen;
            tmp = (ElemType*)realloc(vector->data, capcity * sizeof(ElemType));
        }
        
        dataLen += growLen;
        // 如果申请到了, 则赋值给原有的数组
        vector->data = tmp;
    }

    // 够用, 则直接添加
    vector->data[vector->length] = elem;
    ++vector->length;

    return OK;
}

// 3.1 (根据下标删除)
Status DeleteElemByIdx(Vector *vector, int index, ElemType *deletedElem) {
    // 1. 当给定删除的下标小于0或者大于向量的长度时, 报错
    // 2. 给定删除的下标是从1开始的, 标志着是第几个元素. 所以在使用时需要减去1
    if(index <= 0 || index > vector->length) {
        return ERROR;
    }

    // 将删除的元素返回
    *deletedElem = vector->data[index-1];

    // 当前循环变量
    unsigned int j, len;
    for(j = index, len = vector->length; j < len; ++j) {
        vector->data[j-1] = vector->data[j];
    }
    // 长度减一
    --vector->length;
    return OK;
}

// 根据元素来删除
Status DeleteElemByElem(Vector *vector, ElemType elem) {
    unsigned int index = Search(vector, elem);

    if(index < 0) {
        // 未找到
        return ERROR;
    }

    ElemType deletedElem;
    return DeleteElemByIdx(vector, index, &deletedElem);
}

// 查找某元素的下标
int Search(Vector *vector, ElemType elem) {
    unsigned int i;
    for(i = 0; i < vector->length; i++) {
        if(vector->data[i] == elem) {
            break;
        }
    }

    if(i >= vector->length) {
        // 未找到
        return -1;
    }

    // 表示第几个元素
    return i + 1;
}

Status Contain(Vector *vector, ElemType elem) {
    int index = Search(vector, elem);
    return index <= 0 ? FALSE : TRUE;
}

Status UnionVector(Vector *v1, Vector *v2, Vector *v3) {
    // 并集
    // i: 当前循环的下标, idx: 当前添加的个数
    unsigned int i, idx = 0;
    for(i = 0; i < v1->length; i++) {
        InsertElem(v3, v1->data[i]);
    }

    for(i = 0; i < v2->length; i++) {
        // v1中不包含
        if(!Contain(v1, v2->data[i])) {
            InsertElem(v3, v2->data[i]);
            ++idx;
        }
    }
    return OK;
}

Status InterSection(Vector *v1, Vector *v2, Vector *v3) {
    // 交集
    unsigned int i, idx = 0;
    for(i = 0; i < v1->length; i++) {
        if(Contain(v2, v1->data[i])) {
            InsertElem(v3, v1->data[i]);
            ++idx;
        }
    }
    return OK;
}

int main() {
    // 第一步:
    // Vector v;

    // // 1. 创建一个vector
    // CreateInstance(&v);
    // InsertElem(&v, 9);
    // InsertElem(&v, 8);
    // InsertElem(&v, 7);
    // InsertElem(&v, 6);

    // // ElemType de;
    // // DeleteElemByIdx(&v, 2, &de);
    // // printf("%d\n", de);

    // DeleteElemByElem(&v, 7);
    // InsertElem(&v, 5);
    // // 最后一步销毁
    // DestroyInstance(&v);


    // 测试2
    Vector v1, v2, v3;
    CreateInstance(&v1);
    CreateInstance(&v2);
    CreateInstance(&v3);

    InsertElem(&v1, 1);
    InsertElem(&v1, 2);
    InsertElem(&v1, 3);
    InsertElem(&v1, 4);
    InsertElem(&v1, 5);

    InsertElem(&v2, 3);
    InsertElem(&v2, 4);
    InsertElem(&v2, 5);
    InsertElem(&v2, 6);
    InsertElem(&v2, 7);

    InterSection(&v1, &v2, &v3);

    DestroyInstance(&v1);
    DestroyInstance(&v2);
    DestroyInstance(&v3);
}