#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int A[], int n)
{
	int temp;

	for (int last = n; last >= 2; last--) {
		for (int i = 0; i < last - 1; i++) {
			if (A[i] > A[i + 1]) {
				temp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = temp;
			}
		}
	}
}

void merge1(int sortedArr1[], int sortedArr2[], int arr3[], int s1, int s2)
{
	int  p1 = 0, p2 = 0, p3 = 0;
	while (p1 < s1 && p2 < s2) {
		if (sortedArr1[p1] < sortedArr2[p2])
			arr3[p3++] = sortedArr1[p1++];
		else
			arr3[p3++] = sortedArr2[p2++];
	}
	while (p1 < s1) {
		arr3[p3++] = sortedArr1[p1++];
	}
	while (p2 < s2) {
		arr3[p3++] = sortedArr2[p2++];
	}
	for (int i = 0; i < p3; i++) {
		printf("%d ", arr3[i]);
	}
	printf("\n\n");
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

ListNode* merge2(ListNode* head1, ListNode* head2)
{
	ListNode *p = NULL;
	ListNode *head3 = NULL;

	while (head1 != NULL && head2 != NULL) {
		if (head3 == NULL) {
			if (head1->data < head2->data) {
				head3 = head1;
				p = head3;
				head1 = head1->link;
			}
			else if (head1->data > head2->data) {
				head3 = head2;
				p = head3;
				head2 = head2->link;
			}
		}
		else {
			if (head1->data < head2->data) {
				p->link = head1;
				p = head1;
				head1 = head1->link;
			}
			else if (head1->data > head2->data) {
				p->link = head2;
				p = head2;
				head2 = head2->link;
			}
		}
		p->link = NULL;
	}
	if (head1 != NULL)
		p->link = head1;
	else if (head2 != NULL)
		p->link = head2;
	return head3;
}

int count = 0;
void hanoi_tower(int n, char from, char tmp, char to)
{
	if (n == 1) printf("원판 1을 %c에서 %c으로 옮긴다.\n", from, to);
	else {
		hanoi_tower(n - 1, from, to, tmp);
		printf("원판 %d을 %c에서 %c으로 옮긴다.\n", n, from, to);
		hanoi_tower(n - 1, tmp, from, to);
	}
	count++;
}

int main(void)
{
	int sel = 0;
	int sortedArr1[] = { 5, 7, 24, 56 };
	int sortedArr2[] = { 19, 45, 61, 79, 92 };
	int arr3[10];
	int s1 = 4, s2 = 5;
	int disk;

	ListNode *head1 = NULL;
	ListNode *head2 = NULL;

	while (1) {
		printf("1.버블정렬  2.병합(배열)  3.병합(연결리스트)  4.하노이타워  => "); scanf("%d", &sel); printf("\n");
		int arr[10] = { 0, 5, 9, 1, 4, 8, 3, 7, 2, 6 };
		switch (sel) {
		case 1:
			printf("[Before] ");
			for (int i = 0; i < 10; i++)
				printf("%d ", arr[i]);
			bubbleSort(arr, sizeof(arr) / sizeof(int));
			printf("\n[After] ");
			for (int i = 0; i < 10; i++)
				printf("%d ", arr[i]);
			printf("\n\n");
			break;
		case 2:
			printf("[Before]\n");
			printf("(1) ");
			for (int i = 0; i < s1; i++)
				printf("%d ", sortedArr1[i]);
			printf("\n(2) ");
			for(int i = 0; i < s2; i++)
				printf("%d ", sortedArr2[i]);
			printf("\n\n[After]\n");
			merge1(sortedArr1, sortedArr2, arr3, s1, s2);
			break;
		case 3:
			for (int i = s1 - 1; i >= 0; i--)
				head1 = insert_first(head1, sortedArr1[i]);

			for (int i = s2 - 1; i >= 0; i--)
				head2 = insert_first(head2, sortedArr2[i]);

			printf("[Before]\n");
			printf("(1) ");  print_list(head1);
			printf("(2) ");  print_list(head2);
			printf("\n[After]\n");
			print_list(merge2(head1, head2)); printf("\n");
			head1 = NULL;
			head2 = NULL;
			break;
		case 4:
			printf("디스크의 개수를 입력하세요: "); scanf("%d", &disk);
			hanoi_tower(disk, 'A', 'B', 'C');
			printf("옮긴 횟수: %d\n\n", count);
			count = 0;
			break;
		default:
			return 0;
		}
	}
	return 0;
}