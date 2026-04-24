/**
 * 单链表（带头结点）
 * 408 数据结构 - 链表的插入与删除
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

// 初始化（带头结点）
LinkList InitList() {
    LNode *head = (LNode *)malloc(sizeof(LNode));
    head->next = NULL;
    return head;
}

// 尾插法建表
LinkList TailInsert(LinkList L, int arr[], int n) {
    LNode *tail = L;
    for (int i = 0; i < n; i++) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = arr[i];
        s->next = NULL;
        tail->next = s;
        tail = s;
    }
    return L;
}

// 头插法建表（结果逆序）
LinkList HeadInsert(LinkList L, int arr[], int n) {
    for (int i = 0; i < n; i++) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = arr[i];
        s->next = L->next;
        L->next = s;
    }
    return L;
}

// 按位序查找，返回第 i 个结点（1 开始）
LNode *GetElem(LinkList L, int i) {
    if (i < 0) return NULL;
    LNode *p = L;
    int j = 0;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    return p;
}

// 按值查找
LNode *LocateElem(LinkList L, int e) {
    LNode *p = L->next;
    while (p && p->data != e)
        p = p->next;
    return p;
}

// 在位序 i 插入元素 e
// 时间复杂度 O(n)（找位置） + O(1)（插入）
int Insert(LinkList L, int i, int e) {
    LNode *p = GetElem(L, i - 1);  // 找前驱
    if (!p) return 0;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 1;
}

// 删除位序 i 的元素，用 e 返回
// 时间复杂度 O(n)（找位置） + O(1)（删除）
int Delete(LinkList L, int i, int *e) {
    LNode *p = GetElem(L, i - 1);  // 找前驱
    if (!p || !p->next) return 0;
    LNode *q = p->next;
    *e = q->data;
    p->next = q->next;
    free(q);
    return 1;
}

// 打印
void PrintList(LinkList L) {
    LNode *p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 释放
void FreeList(LinkList L) {
    LNode *p = L, *q;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
}

int main() {
    LinkList L = InitList();
    int arr[] = {10, 20, 30, 40, 50};

    // 尾插法建表
    TailInsert(L, arr, 5);
    printf("尾插法建表：");
    PrintList(L);           // 10 20 30 40 50

    // 插入
    Insert(L, 3, 25);       // 在位序3插入25
    printf("位序3插入25：");
    PrintList(L);           // 10 20 25 30 40 50

    // 删除
    int e;
    Delete(L, 4, &e);       // 删除位序4
    printf("删除位序4的元素 %d：", e);
    PrintList(L);           // 10 20 25 40 50

    // 按值查找
    LNode *p = LocateElem(L, 40);
    printf("查找 40：%s\n", p ? "找到了" : "未找到");

    // 头插法演示（单独建一个）
    LinkList L2 = InitList();
    HeadInsert(L2, arr, 5);
    printf("头插法建表：");
    PrintList(L2);          // 50 40 30 20 10

    FreeList(L);
    FreeList(L2);
    return 0;
}
