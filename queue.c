/**
 * 队列
 * 408 数据结构 - 顺序循环队列 & 链式队列
 */
#include <stdio.h>
#include <stdlib.h>

/*========== 顺序循环队列（牺牲一个空间判满） ==========*/
#define MaxSize 5

typedef struct {
    int data[MaxSize];
    int front, rear;  // front指向队首元素，rear指向队尾下一位置
} SqQueue;

void InitQueue(SqQueue *Q) {
    Q->front = Q->rear = 0;
}

int QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}

// 入队
int EnQueue(SqQueue *Q, int e) {
    if ((Q->rear + 1) % MaxSize == Q->front) return 0;  // 队满
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MaxSize;
    return 1;
}

// 出队
int DeQueue(SqQueue *Q, int *e) {
    if (Q->front == Q->rear) return 0;  // 队空
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MaxSize;
    return 1;
}

// 获取队首
int GetHead(SqQueue Q) {
    return Q.data[Q.front];
}

int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MaxSize) % MaxSize;
}

/*========== 链式队列（带头结点） ==========*/
typedef struct QNode {
    int data;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *front, *rear;
} LinkQueue;

void InitLinkQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->front->next = NULL;
}

int LinkQueueEmpty(LinkQueue Q) {
    return Q.front == Q.rear;
}

// 入队（尾插）
void LinkEnQueue(LinkQueue *Q, int e) {
    QNode *s = (QNode *)malloc(sizeof(QNode));
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
}

// 出队
int LinkDeQueue(LinkQueue *Q, int *e) {
    if (Q->front == Q->rear) return 0;
    QNode *p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) Q->rear = Q->front;  // 队列变空
    free(p);
    return 1;
}

void FreeLinkQueue(LinkQueue *Q) {
    QNode *p = Q->front, *q;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
}

/*========== 测试 ==========*/
int main() {
    printf("=== 顺序循环队列 ===\n");
    SqQueue Q;
    InitQueue(&Q);

    EnQueue(&Q, 10);
    EnQueue(&Q, 20);
    EnQueue(&Q, 30);
    printf("入队 10,20,30，队列长度：%d\n", QueueLength(Q));

    int e;
    DeQueue(&Q, &e);
    printf("出队：%d，队首：%d\n", e, GetHead(Q));

    EnQueue(&Q, 40);
    EnQueue(&Q, 50);
    printf("入队 40,50，队列长度：%d\n", QueueLength(Q));

    // 再入队一个会满（MaxSize=5，牺牲一个位置，最多存4个）
    printf("再入队 60：%s\n", EnQueue(&Q, 60) ? "成功" : "队满");

    printf("\n=== 链式队列 ===\n");
    LinkQueue LQ;
    InitLinkQueue(&LQ);

    LinkEnQueue(&LQ, 100);
    LinkEnQueue(&LQ, 200);
    LinkEnQueue(&LQ, 300);
    printf("入队 100,200,300\n");

    LinkDeQueue(&LQ, &e);
    printf("出队：%d\n", e);

    LinkEnQueue(&LQ, 400);
    LinkDeQueue(&LQ, &e);
    printf("出队：%d\n", e);

    FreeLinkQueue(&LQ);
    return 0;
}
