/**
 * 顺序表（静态分配）
 * 408 数据结构 - 线性表的插入与删除
 */
#include <stdio.h>
#define MaxSize 10

typedef struct {
    int data[MaxSize];
    int length;
} SeqList;

// 初始化
void InitList(SeqList *L) {
    L->length = 0;
}

// 插入：在位序 i（1~length+1）插入元素 e
// 时间复杂度：最好 O(1)，最坏 O(n)，平均 O(n)
int Insert(SeqList *L, int i, int e) {
    if (i < 1 || i > L->length + 1) return 0;  // 位序不合法
    if (L->length >= MaxSize) return 0;          // 表满
    for (int j = L->length; j >= i; j--)         // 后移
        L->data[j] = L->data[j - 1];
    L->data[i - 1] = e;
    L->length++;
    return 1;
}

// 删除：删除位序 i 的元素，用 e 返回
// 时间复杂度：最好 O(1)，最坏 O(n)，平均 O(n)
int Delete(SeqList *L, int i, int *e) {
    if (i < 1 || i > L->length) return 0;       // 位序不合法
    *e = L->data[i - 1];
    for (int j = i; j < L->length; j++)          // 前移
        L->data[j - 1] = L->data[j];
    L->length--;
    return 1;
}

// 按值查找，返回位序（0 表示未找到）
int LocateElem(SeqList L, int e) {
    for (int i = 0; i < L.length; i++)
        if (L.data[i] == e) return i + 1;
    return 0;
}

// 打印
void PrintList(SeqList L) {
    for (int i = 0; i < L.length; i++)
        printf("%d ", L.data[i]);
    printf("\n");
}

int main() {
    SeqList L;
    InitList(&L);

    Insert(&L, 1, 10);
    Insert(&L, 2, 20);
    Insert(&L, 3, 30);
    Insert(&L, 2, 15);  // 在位序2插入15
    printf("插入后：");
    PrintList(L);        // 10 15 20 30

    int e;
    Delete(&L, 3, &e);   // 删除位序3的元素
    printf("删除的元素：%d，删除后：", e);
    PrintList(L);        // 10 15 30

    printf("查找 20 的位序：%d\n", LocateElem(L, 20));  // 0（已删除）
    printf("查找 15 的位序：%d\n", LocateElem(L, 15));  // 2

    return 0;
}
