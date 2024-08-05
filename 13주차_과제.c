#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define equal(item1, item2) (item1.key == item2.key))
#define TABLE_SIZE1 13
#define TABLE_SIZE2 11

typedef struct
{
	int key;
	int empty;
}element;

struct list {
	element item;
	struct list *link;
};

element hash_table1[TABLE_SIZE1];
element hash_table2[TABLE_SIZE2];
struct list *hash_table3[TABLE_SIZE2];

void init_table1(element ht[])
{
	for (int i = 0; i < TABLE_SIZE1; i++) {
		ht[i].key = 0;
		ht[i].empty = -1;
	}
}

void init_table2(element ht[])
{
	for (int i = 0; i < TABLE_SIZE2; i++) {
		ht[i].key = 0;
		ht[i].empty = -1;
	}
}

int hash_function1(int key)
{
	return key % TABLE_SIZE1;
}

int hash_function2(int key)
{
	return key % TABLE_SIZE2;
}

int hash_function2_1(int key)
{
	return (1 + (key % 11));
}

int hash_function2_2(int key)
{
	return (7 - (key % 7));
}

void hash_lp_add1(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function1(item.key);
	printf("### key: %d ###\n", item.key);
	while (ht[i].empty == 1) {
		printf("hash address: %d 충돌\n", i);
		if (item.key == ht[i].key) {
			fprintf(stderr, "탐색키가 중복되었습니다.\n");
			exit(1);
		}
		i = (i + 1) % TABLE_SIZE1;
	}
	item.empty = 1;
	printf("hash address: %d 삽입\n\n", i);
	ht[i] = item;
}

void hash_lp_add2(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function2(item.key);
	printf("### key: %d ###\n", item.key);
	while (ht[i].empty == 1) {
		printf("hash address: %d 충돌\n", i);
		if (item.key == ht[i].key) {
			fprintf(stderr, "탐색키가 중복되었습니다.\n");
			exit(1);
		}
		i = (i + 1) % TABLE_SIZE2;
	}
	item.empty = 1;
	printf("hash address: %d 삽입\n\n", i);
	ht[i] = item;
}

void hash_qp_add1(element item, element ht[])
{
	int i, hash_value, inc = 1;
	hash_value = i = hash_function1(item.key);
	printf("### key: %d ###\n", item.key);
	while (ht[i].empty == 1) {
		printf("hash address: %d 충돌\n", i);
		if (item.key == ht[i].key) {
			fprintf(stderr, "탐색키가 중복되었습니다.\n");
			exit(1);
		}
		i = (hash_value + inc * inc) % TABLE_SIZE1;
		inc = inc + 1;
	}
	item.empty = 1;
	printf("hash address: %d 삽입\n\n", i);
	ht[i] = item;
}

void hash_qp_add2(element item, element ht[])
{
	int i, hash_value, inc = 1;
	hash_value = i = hash_function2(item.key);
	printf("### key: %d ###\n", item.key);
	while (ht[i].empty == 1) {
		printf("hash address: %d 충돌\n", i);
		if (item.key == ht[i].key) {
			fprintf(stderr, "탐색키가 중복되었습니다.\n");
			exit(1);
		}
		i = (hash_value + inc * inc) % TABLE_SIZE2;
		inc = inc + 1;
	}
	item.empty = 1;
	printf("hash address: %d 삽입\n\n", i);
	ht[i] = item;
}

void hash_dh_add1(element item, element ht[])
{
	int i, hash_value, inc, j = 0;
	hash_value = i = hash_function1(item.key);
	inc = hash_function2_1(item.key);
	printf("### key: %d ###\n", item.key);
	while (ht[i].empty == 1) {
		printf("hash address: %d 충돌\n", i);
		if(j == 0)
			printf("f(%d) = %d\n", item.key, inc);
		if (item.key == ht[i].key) {
			fprintf(stderr, "탐색키가 중복되었습니다.\n");
			exit(1);
		}
		i = (i + inc) % TABLE_SIZE1;
		j++;
	}
	item.empty = 1;
	printf("hash address: %d 삽입\n\n", i);
	ht[i] = item;
}

void hash_dh_add2(element item, element ht[])
{
	int i, hash_value, inc, j = 0;
	hash_value = i = hash_function2(item.key);
	inc = hash_function2_2(item.key);
	printf("### key: %d ###\n", item.key);
	while (ht[i].empty == 1) {
		printf("hash address: %d 충돌\n", i);
		if (j == 0)
			printf("f(%d) = %d\n", item.key, inc);
		if (item.key == ht[i].key) {
			fprintf(stderr, "탐색키가 중복되었습니다.\n");
			exit(1);
		}
		i = (i + inc) % TABLE_SIZE2;
		j++;
	}
	item.empty = 1;
	printf("hash address: %d 삽입\n\n", i);
	ht[i] = item;
}

void hash_print1(element ht[])
{
	int i;
	printf("\n========================\n");
	for (i = 0; i < TABLE_SIZE1; i++) {
		printf("[%d] ", i);
		if (ht[i].key != 0)
			printf("%d\n", ht[i].key);
		else
			printf("\n");
	}
	printf("========================\n\n");
}

void hash_print2(element ht[])
{
	int i;
	printf("\n========================\n");
	for (i = 0; i < TABLE_SIZE2; i++) {
		printf("[%d] ", i);
		if (ht[i].key != 0)
			printf("%d\n", ht[i].key);
		else
			printf("\n");
	}
	printf("========================\n\n");
}

void hash_chain_add(element item, struct list *ht[])
{
	int hash_value = hash_function2(item.key);
	struct list *ptr;
	struct list *node = ht[hash_value];

	for (; node; node = node->link) {
		if (node->item.key == item.key) {
			fprintf(stderr, "이미 탐색키가 저장되어 있음\n");
			return;
		}
	}

	node = ht[hash_value];
	ptr = (struct  list *)malloc(sizeof(struct list));
	ptr->item = item;
	ptr->link = NULL;

	ht[hash_value] = ptr;
	if (node)
		ptr->link = node;
}

void hash_chain_print(struct list *ht[])
{
	struct list *node;
	printf("\n===============================\n");
	for (int i = 0; i < TABLE_SIZE2; i++) {
		printf("[%d]->", i);
		for (node = ht[i]; node; node = node->link) {
			printf("%d->", node->item.key);
		}
		printf("\n");
	}
	printf("===============================\n");
}

int main(void)
{
	int sel;
	int elements1[] = { 10, 20, 30, 40, 33, 46, 50, 60 };
	int elements2[] = { 12, 44, 13, 88, 23, 94, 11, 39, 20, 16, 5 };
	element e;

	int elementsSize1 = sizeof(elements1) / sizeof(int);
	int elementsSize2 = sizeof(elements2) / sizeof(int);

	while (1) {
		printf("1.1번  2.2번  3.종료  => ");
		scanf("%d", &sel); printf("\n");
		switch (sel) {
		case 1:
			printf("======== 선형 조사 ========\n");
			init_table1(hash_table1);
			for (int i = 0; i < elementsSize1; i++) {
				e.key = elements1[i];
				hash_lp_add1(e, hash_table1);
			}
			hash_print1(hash_table1);

			printf("======== 이차원 조사 ========\n");
			init_table1(hash_table1);
			for (int i = 0; i < elementsSize1; i++) {
				e.key = elements1[i];
				hash_qp_add1(e, hash_table1);
			}
			hash_print1(hash_table1);

			printf("======== 더블 해싱 ========\n");
			init_table1(hash_table1);
			for (int i = 0; i < elementsSize1; i++) {
				e.key = elements1[i];
				hash_dh_add1(e, hash_table1);
			}
			hash_print1(hash_table1);
			break;
		case 2:
			printf("======== 선형 조사 ========\n");
			init_table2(hash_table2);
			for (int i = 0; i < elementsSize2; i++) {
				e.key = elements2[i];
				hash_lp_add2(e, hash_table2);
			}
			hash_print2(hash_table2);

			printf("======== 이차원 조사 ========\n");
			init_table2(hash_table2);
			for (int i = 0; i < elementsSize2; i++) {
				e.key = elements2[i];
				hash_qp_add2(e, hash_table2);
			}
			hash_print2(hash_table2);

			printf("======== 더블 해싱 ========\n");
			init_table2(hash_table2);
			for (int i = 0; i < elementsSize2; i++) {
				e.key = elements2[i];
				hash_dh_add2(e, hash_table2);
			}
			hash_print2(hash_table2);

			printf("======== 체이닝 ========\n");
			for (int i = 0; i < elementsSize2; i++) {
				e.key = elements2[i];
				hash_chain_add(e, hash_table3);
			}
			hash_chain_print(hash_table3);
			printf("\n");
			break;
		default:
			return 0;
		}
	}
	return 0;
}