/**
 * 二叉树
 * 408 数据结构 - 链式存储 + 先序/中序/后序/层序遍历
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 先序遍历（根左右）
void PreOrder(BiTree T) {
    if (!T) return;
    printf("%d ", T->data);
    PreOrder(T->lchild);
    PreOrder(T->rchild);
}

// 中序遍历（左根右）
void InOrder(BiTree T) {
    if (!T) return;
    InOrder(T->lchild);
    printf("%d ", T->data);
    InOrder(T->rchild);
}

// 后序遍历（左右根）
void PostOrder(BiTree T) {
    if (!T) return;
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    printf("%d ", T->data);
}

// 层序遍历（借助队列）
void LevelOrder(BiTree T) {
    if (!T) return;
    BiTNode *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = T;
    while (front != rear) {
        BiTNode *p = queue[front++];
        printf("%d ", p->data);
        if (p->lchild) queue[rear++] = p->lchild;
        if (p->rchild) queue[rear++] = p->rchild;
    }
}

// 求树的深度
int TreeDepth(BiTree T) {
    if (!T) return 0;
    int l = TreeDepth(T->lchild);
    int r = TreeDepth(T->rchild);
    return (l > r ? l : r) + 1;
}

// 统计结点数
int NodeCount(BiTree T) {
    if (!T) return 0;
    return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

// 统计叶子结点数
int LeafCount(BiTree T) {
    if (!T) return 0;
    if (!T->lchild && !T->rchild) return 1;
    return LeafCount(T->lchild) + LeafCount(T->rchild);
}

// 创建新结点
BiTNode *NewNode(int e) {
    BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
    p->data = e;
    p->lchild = p->rchild = NULL;
    return p;
}

// 释放
void FreeTree(BiTree T) {
    if (!T) return;
    FreeTree(T->lchild);
    FreeTree(T->rchild);
    free(T);
}

/*
 * 手动建树：
 *         1
 *        / \
 *       2   3
 *      / \   \
 *     4   5   6
 */
BiTree BuildSampleTree() {
    BiTree T = NewNode(1);
    T->lchild = NewNode(2);
    T->rchild = NewNode(3);
    T->lchild->lchild = NewNode(4);
    T->lchild->rchild = NewNode(5);
    T->rchild->rchild = NewNode(6);
    return T;
}

int main() {
    BiTree T = BuildSampleTree();

    printf("先序遍历：");
    PreOrder(T);
    printf("\n");

    printf("中序遍历：");
    InOrder(T);
    printf("\n");

    printf("后序遍历：");
    PostOrder(T);
    printf("\n");

    printf("层序遍历：");
    LevelOrder(T);
    printf("\n");

    printf("树的深度：%d\n", TreeDepth(T));
    printf("结点总数：%d\n", NodeCount(T));
    printf("叶子结点数：%d\n", LeafCount(T));

    FreeTree(T);
    return 0;
}
