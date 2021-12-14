/**
 * c语言实现向量
 */

#define OK 1
#define ERROR 0
#define Status int
#define TRUE 1
#define FALSE 0

#define InitLen 10

typedef int ElemType;

typedef struct {
    ElemType *data;  // 元素(数组形式)
    unsigned int length;  // 向量的长度
} Vector;

// 1. 创建向量
Status CreateInstance(Vector *vector);

// 2. 插入元素
Status InsertElem(Vector *vector, ElemType elem);

// 3. 删除
// 3.1 (根据下标删除), 通过ElemType指针变量deletedElem来返回已经删除的元素
Status DeleteElemByIdx(Vector *vector, int index, ElemType *deletedElem);

// 3.2 根据元素来删除
Status DeleteElemByElem(Vector *vector, ElemType elem);

// 4. 判断向量是否存在某元素
Status Contain(Vector *vector, ElemType elem);

// 5. 向量与向量之间的并集
Status UnionVector(Vector *v1, Vector *v2, Vector *v3);

// 6. 向量与向量之间的交集
Status InterSection(Vector *v1, Vector *v2, Vector *v3);

// 7. 销毁
Status DestroyInstance(Vector *vector);

// 8. 向量中查找某元素的下标
unsigned int Search(Vector *vector, ElemType elem);