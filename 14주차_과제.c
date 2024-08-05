#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES1 6
#define MAX_VERTICES2 8
#define INF 10000

typedef struct GraphNode {
	int vertex;
	struct GraphNode *link;
} GraphNode;

typedef struct GraphType1 {
	int n;
	GraphNode *adj_list[MAX_VERTICES1];
} GraphType1;

#define MAX_STACL_SIZE 6
int visited[MAX_VERTICES1];

typedef int element;
typedef struct {
	element stack[MAX_STACL_SIZE];
	int top;
} StackType;

//스택 초기화 함수
void init(StackType *s)
{
	s->top = -1;
}

//공백 상태 검출 함수
int is_empty(StackType *s)
{
	return (s->top == -1);
}

//포화 상태 검출 함수
int is_full(StackType *s)
{
	return (s->top == (MAX_STACL_SIZE - 1));
}

//삽입함수
void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}

//삭제함수
element pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}

void graph_init(GraphType1 *g)
{
	g->n = 0;
	for (int v = 0; v < MAX_VERTICES1; v++) {
		g->adj_list[v] = NULL;
	}
}

void insert_vertex(GraphType1 *g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES1) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType1 *g, int u, int v)
{
	GraphNode *node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void DFS(GraphType1* g, StackType *s, int v)
{
	visited[v] = TRUE;
	GraphNode* node;
	for (node = g->adj_list[v]; node != NULL; node = node->link) {
		if (node && !visited[node->vertex])
			DFS(g, s, node->vertex);
	}
	printf("스택에 %d 삽입\n", v);
	push(s, v);
}

void topo_sort(GraphType1 *g, int v)
{
	StackType s;
	init(&s);

	for (int i = v; v < g->n; v++) {
		if (!visited[v]) {
			printf("\nv: %d\n", v);
			DFS(g, &s, v);
		}
	}
	
	int keep = 0;
	
	while (1) {
		for (int i = 0; i < g->n; i++) {
			if (visited[i] == FALSE) {
				keep = 1;
				v = i;
				break;
			}
		}
		if (keep == 1) {
			for (; v < g->n; v++) {
				if (!visited[v]) {
					printf("\nv: %d\n", v);
					DFS(g, &s, v);
				}
				keep = 0;
			}
		}
		else
			break;
	}

	printf("\n");
	while (!is_empty(&s)) {
		int w = pop(&s);
		printf("정점 %d ->", w);
	}
	printf("\n");
}

typedef struct GraphType2 {
	int n;
	int weight[MAX_VERTICES2][MAX_VERTICES2];
} GraphType2;

int distance[MAX_VERTICES2];
int found[MAX_VERTICES2];

int choose(int distance[], int n, int found[])
{
	int min = INT_MAX;
	int minpos = -1;
	for (int i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
int step = 1;
void print_status(GraphType2* g)
{
	printf("# STEP %d #\n", step++);
	printf("dist[] = ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf("[ *] ");
		else
			printf("[%2d] ", distance[i]);
	}
	printf("\n");
	printf("prev[] = ");
	for (int i = 0; i < g->n; i++) {
		printf("[%2d] ", found[i]);
	}
	printf("\n\n");
}

void shortest_path(GraphType2* g, int start)
{
	int u;
	for (int i = 0; i < g->n; i++) {
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;
	distance[start] = 0;
	for (int i = 0; i < g->n; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (int w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
				}
	}
}

int main(void)
{
	int sel, v;
	GraphType1 g1;

	graph_init(&g1);
	insert_vertex(&g1, 0);
	insert_vertex(&g1, 1);
	insert_vertex(&g1, 2);
	insert_vertex(&g1, 3);
	insert_vertex(&g1, 4);
	insert_vertex(&g1, 5);


	insert_edge(&g1, 0, 2);
	insert_edge(&g1, 0, 3);
	insert_edge(&g1, 0, 5);

	insert_edge(&g1, 1, 0);

	insert_edge(&g1, 2, 3);

	insert_edge(&g1, 4, 2);
	insert_edge(&g1, 4, 5);

	insert_edge(&g1, 5, 3);

	GraphType2 g2 = { 8,
	{{0, 4, 7, 10, INF, INF, INF, INF },
	{INF, 0, INF, INF, 20, 8, INF, INF },
	{INF, 2, 0, 2, INF, INF, 8, INF },
	{INF, INF, INF, 0, INF, INF, 8, INF},
	{INF, INF, INF, INF, 0, 3, INF},
	{INF, INF, 12, INF, INF, 0, INF, 7 },
	{0, INF, INF, INF, INF, INF, 0, 12 },
	{INF, INF, INF, INF, 4, INF, INF, 0} }
	};

	while (1) {
		printf("1.1번  2.2번  3.종료  => ");
		scanf("%d", &sel); printf("\n");
		switch (sel) {
		case 1:
			for (int i = 0; i < MAX_VERTICES1; i++)
				visited[i] = FALSE;

			printf("시작 정점 선택(0~5): ");
			scanf("%d", &v);
			topo_sort(&g1, v);
			printf("\n");
			break;
		case 2:
			printf("시작 정점 선택(0~7): ");
			scanf("%d", &v);
			printf("\n");
			shortest_path(&g2, v);
			step = 1;
			break;
		default:
			return 0;
		}
	}
	return 0;
}