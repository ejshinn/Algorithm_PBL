#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void selectionSort(int arr[], int n) {
	int least, temp, cnt = 0, cntSum = 0;

	for (int i = 0; i < n - 1; i++) {
		least = i;

		for (int j = i + 1; j < n; j++) {
			cnt++;
			if (arr[j] < arr[least])
				least = j;
		}
		cntSum += cnt;
		printf("\n가장 작은 수 %d 찾음\n", arr[least]);

		printf("최솟값을 arr[%d]인 %d와(과) 교환\n", i, arr[i]);
		temp = arr[i];
		arr[i] = arr[least];
		arr[least] = temp;
		
		printf("현재: ");
		for (int k = 0; k < n; k++) {
			if(k == i+1)
				printf("| ");
			printf("%d ", arr[k]);
		}
		printf("\n비교 횟수: %d\n", cnt);
		cnt = 0;
	}
	printf("\n전체 비교 횟수: %d\n", cntSum);
}

typedef struct ListNode {
	int data;
	struct ListNode *link;
}ListNode;

ListNode* insert_first(ListNode *head, int value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

void print_list(ListNode* head)
{
	for (ListNode *p = head; p != NULL; p = p->link)
		printf("%d ", p->data);
	printf("\n");
}

void selectionSort_list(ListNode *head)
{
	int i = 0, k = 0, cnt = 0, cntSum = 0;
	ListNode *p = head;

	while (p->link) {
		ListNode *min = p;
		ListNode *r = p->link;

		while (r) {
			cnt++;
			if (min->data > r->data)
				min = r;
			r = r->link;
		}
		cntSum += cnt;
		printf("\n가장 작은 수 %d 찾음\n", min->data);

		printf("최솟값을 %d와(과) 교환\n", p->data);
		int x = p->data;
		p->data = min->data;
		min->data = x;
		p = p->link;

		printf("현재: ");
		for (ListNode *t = head; t != NULL; t = t->link) {
			printf("%d ", t->data);
			if (k == i)
				printf("| ");
			k++;
		}
		printf("\n");
		printf("비교 횟수: %d\n", cnt);
		cnt = 0, k = 0, i++;
	}
	printf("\n전체 비교 횟수: %d\n", cntSum);
}

int main(void)
{
	int sel, size, *arr, num;
	ListNode *head = NULL;

	while (1) {
		printf("1.선택정렬(배열)  2.선택정렬(연결리스트)  3.종료  => ");
		scanf("%d", &sel); printf("\n");
		switch (sel)
		{
		case 1:
			printf("입력할 수의 개수: ");
			scanf("%d", &size);

			arr = (int*)malloc(size * sizeof(int));

			printf("\n정수 %d개를 입력하세요.\n", size);
			for (int i = 0; i < size; i++)
				scanf("%d", &arr[i]);

			selectionSort(arr, size);
			printf("정렬 후: ");
			for (int i = 0; i < size; i++)
				printf("%d ", arr[i]);
			printf("\n\n");
			break;
		case 2:
			printf("입력할 수의 개수: ");
			scanf("%d", &size);

			printf("\n정수 %d개를 입력하세요.\n", size);
			for (int i = 0; i < size; i++) {
				scanf("%d", &num);
				head = insert_first(head, num);
			}
			printf("정렬 전: ");
			print_list(head);
			selectionSort_list(head);
			printf("정렬 후: ");
			print_list(head); printf("\n");
			head = NULL;
			break;
		default:
			return 0;
		}
	}
	return 0;
}