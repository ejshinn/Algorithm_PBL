#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
int visited[MAX_VERTICES];

typedef struct QNode {
	int data;
	struct QNode *link;
} QNode;

typedef struct {
	QNode *front, *rear;
} QueueType;

void InitQueue(QueueType *queue) {
	queue->front = queue->rear = NULL;
}

int isEmpty(QueueType *LQ) {
	if (LQ->front == NULL) {
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *LQ, int item) {
	QNode *newNode = (QNode *)malloc(sizeof(QNode));
	newNode->data = item;
	newNode->link = NULL;
	if (LQ->front == NULL) {
		LQ->front = newNode;
		LQ->rear = newNode;
	}
	else {
		LQ->rear->link = newNode;
		LQ->rear = newNode;
	}
}

int deQueue(QueueType *LQ) {
	QNode *old = LQ->front;
	int item;
	if (isEmpty(LQ)) return 0;
	else {
		item = old->data;
		LQ->front = LQ->front->link;
		if (LQ->front == NULL)
			LQ->rear = NULL;
		free(old);
		return item;
	}
}

typedef struct MGraphType {
	int n; //정점의 개수
	int adj_max[MAX_VERTICES][MAX_VERTICES];
} MGraphType;

void init_m(MGraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_max[r][c] = 0;
}

//정점 삽입 연산
void insert_vertex_m(MGraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

//간선 삽입 연산
void insert_edge_m(MGraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_max[start][end] = 1;
	g->adj_max[end][start] = 1;
}

//인접 행렬 출력
void print_adj_max(MGraphType* g)
{
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_max[i][j]);
		}
		printf("\n");
	}
}

void dfs_mat(MGraphType* g, int v)
{
	visited[v] = TRUE; //정점 v의 방문 표시
	printf("정점 %d -> ", v); //방문한 정점 출력
	for (int w = 0; w < g->n; w++)
		if (g->adj_max[v][w] && !visited[w])
			dfs_mat(g, w); //정점 w에서 DFS 새로 시작
}

void bfs_mat(MGraphType* g, int v)
{
	int w;
	QueueType q;

	InitQueue(&q); //큐 초기화
	visited[v] = TRUE; //정점 v의 방문 표시
	printf("%d 방문 -> ", v);
	enQueue(&q, v);
	while (!isEmpty(&q)) {
		v = deQueue(&q); //큐에 정점 추출
		for (w = 0; w < g->n; w++) //인접 정점 탐색
			if (g->adj_max[v][w] && !visited[w]) {
				visited[w] = TRUE; //방문 표시
				printf("%d 방문 -> ", w);
				enQueue(&q, w); //방문한 정점을 큐에 저장
			}
	}
}

typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct LGraphType {
	int n; //정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} LGraphType;

void init_l(LGraphType* g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

//정점 삽입 연산
void insert_vertex_l(LGraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void D_insert_edge_l(LGraphType* g, int u, int v)
{
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void ND_insert_edge_l(LGraphType* g, int u, int v)
{
	GraphNode* start, *end;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	start = (GraphNode*)malloc(sizeof(GraphNode));
	end = (GraphNode*)malloc(sizeof(GraphNode));

	start->vertex = v;
	start->link = g->adj_list[u];
	g->adj_list[u] = start;
	end->vertex = u;
	end->link = g->adj_list[v];
	g->adj_list[v] = end;
}

void print_adj_list(LGraphType* g)
{
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		printf("정점 %d의 인접 리스트 ", i);
		while (p != NULL) {
			printf("-> %d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}

void dfs_helper(LGraphType* adjList, int currVertex) {
	for (GraphNode* temp = adjList->adj_list[currVertex]; temp; temp = temp->link) {
		int adjVertex = temp->vertex;
		if (visited[adjVertex] == FALSE) {
			visited[adjVertex] = TRUE;
			printf("[%d]->", adjVertex);
			dfs_helper(adjList, adjVertex);
		}
	}
}

void dfs_list(LGraphType* adjList) {
	for (int i = 0; i < adjList->n; i++) {
		if (visited[i] == FALSE) {
			visited[i] = TRUE;
			printf("\n[%d]->", i);
			dfs_helper(adjList, i);
		}
	}
}

void bfs_list(LGraphType* adjList) {
	QueueType queue;
	InitQueue(&queue);

	for (int i = 0; i < adjList->n; i++) {
		if (visited[i] == FALSE) {
			enQueue(&queue, i);
			visited[i] = TRUE;
		}
		if (!isEmpty(&queue)) {
			int currVertex = deQueue(&queue);
			printf("[%d]->", currVertex);
			for (GraphNode* temp = adjList->adj_list[currVertex]; temp; temp = temp->link) {
				int adjVertex = temp->vertex;
				if (visited[adjVertex] == FALSE) {
					visited[adjVertex] = TRUE;
					enQueue(&queue, adjVertex);
				}
			}
		}
	}
}

int main(void)
{
	MGraphType *G1;
	G1 = (MGraphType *)malloc(sizeof(MGraphType));
	init_m(G1);
	for (int i = 0; i < 6; i++)
		insert_vertex_m(G1, i);
	insert_edge_m(G1, 0, 1);
	insert_edge_m(G1, 0, 2);
	insert_edge_m(G1, 0, 4);
	insert_edge_m(G1, 1, 0);
	insert_edge_m(G1, 2, 0);
	insert_edge_m(G1, 2, 3);
	insert_edge_m(G1, 3, 4);
	insert_edge_m(G1, 3, 5);
	insert_edge_m(G1, 4, 0);
	insert_edge_m(G1, 5, 3);

	LGraphType *G2;
	G2 = (LGraphType *)malloc(sizeof(LGraphType));
	init_l(G2);
	for (int i = 0; i < 6; i++)
		insert_vertex_l(G2, i);
	ND_insert_edge_l(G2, 0, 1);
	ND_insert_edge_l(G2, 0, 2);
	ND_insert_edge_l(G2, 1, 3);
	ND_insert_edge_l(G2, 4, 5);

	LGraphType *G3;
	G3 = (LGraphType *)malloc(sizeof(LGraphType));
	init_l(G3);
	for (int i = 0; i < 6; i++)
		insert_vertex_l(G3, i);
	D_insert_edge_l(G3, 0, 3);
	D_insert_edge_l(G3, 3, 0);
	D_insert_edge_l(G3, 4, 3);
	D_insert_edge_l(G3, 1, 3);
	D_insert_edge_l(G3, 1, 5);
	D_insert_edge_l(G3, 3, 2);
	D_insert_edge_l(G3, 3, 5);

	int sel, num, num2;
	while (1) {
		printf("1. G1  2.G2  3.G3  4.종료  => ");
		scanf("%d", &sel); printf("\n");
		switch (sel) {
		case 1:
			printf("1.출력  2.깊이우선탐색  3.너비우선탐색  => "); scanf("%d", &num);
			if (num == 1) {
				printf("< G1 >\n");
				print_adj_max(G1); printf("\n\n");
			}
			else if (num == 2) {
				printf("정점 선택: "); scanf("%d", &num2);
				printf("\n< G1 깊이 우선 탐색> \n");
				dfs_mat(G1, num2);
				printf("\n\n");
			}
			else {
				printf("정점 선택: "); scanf("%d", &num2);
				printf("\n< G1 너비 우선 탐색 >\n");
				bfs_mat(G1, num2);
				printf("\n\n");
			}
			for (int i = 0; i < MAX_VERTICES; i++)
				visited[i] = FALSE;
			break;
		case 2:
			printf("1.출력  2.깊이우선탐색  3.너비우선탐색  => "); scanf("%d", &num);
			if (num == 1) {
				printf("< G2 >\n");
				print_adj_list(G2); printf("\n\n");
			}
			else if (num == 2) {
				printf("\n< G2 깊이 우선 탐색> \n");
				dfs_list(G2);
				printf("\n\n");
			}
			else {
				printf("\n< G2 너비 우선 탐색 >\n");
				bfs_list(G2);
				printf("\n\n");
			}
			for (int i = 0; i < MAX_VERTICES; i++)
				visited[i] = FALSE;
			break;
		case 3:
			printf("1.출력  2.깊이우선탐색  3.너비우선탐색  => "); scanf("%d", &num);
			if (num == 1) {
				printf("< G3 >\n");
				print_adj_list(G3); printf("\n\n");
			}
			else if (num == 2) {
				printf("\n< G3 깊이 우선 탐색> \n");
				dfs_list(G3);
				printf("\n\n");
			}
			else {
				printf("\n< G3 너비 우선 탐색 >\n");
				bfs_list(G3);
				printf("\n\n");
			}
			for (int i = 0; i < MAX_VERTICES; i++)
				visited[i] = FALSE;
			break;
		default:
			free(G1);
			free(G2);
			free(G3);
			return 0;
		}
	}
	return 0;
}