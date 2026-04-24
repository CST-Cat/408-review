/**
 * 图
 * 408 数据结构 - 邻接矩阵 & 邻接表 + DFS + BFS
 */
#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 10

/*========== 邻接矩阵 ==========*/
typedef struct {
    int vex[MaxVertexNum];
    int edge[MaxVertexNum][MaxVertexNum];
    int vexNum, arcNum;
} MGraph;

// visited 数组
int visited[MaxVertexNum];

void InitMGraph(MGraph *G, int n) {
    G->vexNum = n;
    G->arcNum = 0;
    for (int i = 0; i < n; i++) {
        G->vex[i] = i;
        for (int j = 0; j < n; j++)
            G->edge[i][j] = 0;
    }
}

// 无向图加边
void AddEdge(MGraph *G, int v, int w) {
    G->edge[v][w] = 1;
    G->edge[w][v] = 1;
    G->arcNum++;
}

// DFS（邻接矩阵）
void DFS_Matrix(MGraph G, int v) {
    printf("%d ", G.vex[v]);
    visited[v] = 1;
    for (int w = 0; w < G.vexNum; w++)
        if (G.edge[v][w] && !visited[w])
            DFS_Matrix(G, w);
}

// BFS（邻接矩阵）
void BFS_Matrix(MGraph G, int v) {
    int queue[MaxVertexNum], front = 0, rear = 0;
    printf("%d ", G.vex[v]);
    visited[v] = 1;
    queue[rear++] = v;
    while (front != rear) {
        int cur = queue[front++];
        for (int w = 0; w < G.vexNum; w++) {
            if (G.edge[cur][w] && !visited[w]) {
                printf("%d ", G.vex[w]);
                visited[w] = 1;
                queue[rear++] = w;
            }
        }
    }
}

/*========== 邻接表 ==========*/
typedef struct ArcNode {
    int adjvex;
    struct ArcNode *next;
} ArcNode;

typedef struct {
    int data;
    ArcNode *first;
} VNode;

typedef struct {
    VNode vertices[MaxVertexNum];
    int vexNum, arcNum;
} ALGraph;

void InitALGraph(ALGraph *G, int n) {
    G->vexNum = n;
    G->arcNum = 0;
    for (int i = 0; i < n; i++) {
        G->vertices[i].data = i;
        G->vertices[i].first = NULL;
    }
}

// 无向图加边（头插法）
void ALAddEdge(ALGraph *G, int v, int w) {
    ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = w;
    p->next = G->vertices[v].first;
    G->vertices[v].first = p;

    ArcNode *q = (ArcNode *)malloc(sizeof(ArcNode));
    q->adjvex = v;
    q->next = G->vertices[w].first;
    G->vertices[w].first = q;

    G->arcNum++;
}

// DFS（邻接表）
void DFS_AdjList(ALGraph G, int v) {
    printf("%d ", G.vertices[v].data);
    visited[v] = 1;
    ArcNode *p = G.vertices[v].first;
    while (p) {
        if (!visited[p->adjvex])
            DFS_AdjList(G, p->adjvex);
        p = p->next;
    }
}

// BFS（邻接表）
void BFS_AdjList(ALGraph G, int v) {
    int queue[MaxVertexNum], front = 0, rear = 0;
    printf("%d ", G.vertices[v].data);
    visited[v] = 1;
    queue[rear++] = v;
    while (front != rear) {
        int cur = queue[front++];
        ArcNode *p = G.vertices[cur].first;
        while (p) {
            if (!visited[p->adjvex]) {
                printf("%d ", G.vertices[p->adjvex].data);
                visited[p->adjvex] = 1;
                queue[rear++] = p->adjvex;
            }
            p = p->next;
        }
    }
}

void ClearVisited() {
    for (int i = 0; i < MaxVertexNum; i++)
        visited[i] = 0;
}

void FreeALGraph(ALGraph *G) {
    for (int i = 0; i < G->vexNum; i++) {
        ArcNode *p = G->vertices[i].first, *q;
        while (p) {
            q = p->next;
            free(p);
            p = q;
        }
    }
}

/*========== 测试 ==========*
 * 图结构（无向图）：
 *   0 --- 1
 *   |   / |
 *   |  /  |
 *   2 --- 3
 */
int main() {
    printf("=== 邻接矩阵 ===\n");
    MGraph MG;
    InitMGraph(&MG, 4);
    AddEdge(&MG, 0, 1);
    AddEdge(&MG, 0, 2);
    AddEdge(&MG, 1, 2);
    AddEdge(&MG, 1, 3);
    AddEdge(&MG, 2, 3);

    printf("DFS：");
    ClearVisited();
    DFS_Matrix(MG, 0);
    printf("\n");

    printf("BFS：");
    ClearVisited();
    BFS_Matrix(MG, 0);
    printf("\n");

    printf("\n=== 邻接表 ===\n");
    ALGraph AG;
    InitALGraph(&AG, 4);
    ALAddEdge(&AG, 0, 1);
    ALAddEdge(&AG, 0, 2);
    ALAddEdge(&AG, 1, 2);
    ALAddEdge(&AG, 1, 3);
    ALAddEdge(&AG, 2, 3);

    printf("DFS：");
    ClearVisited();
    DFS_AdjList(AG, 0);
    printf("\n");

    printf("BFS：");
    ClearVisited();
    BFS_AdjList(AG, 0);
    printf("\n");

    FreeALGraph(&AG);
    return 0;
}
