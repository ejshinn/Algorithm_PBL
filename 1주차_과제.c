#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

int findMax1(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (max < arr[i]) {
			max = arr[i];
		}
	}
	return max;
}

int findMax2(int arr[], int n)
{
	if (n == 0)
		return arr[0];
	int max = findMax2(arr, n - 1);
	arr[n] = max < arr[n] ? arr[n] : max;
	return arr[n];
}

void convert1(int n, int b)
{
	int remain;
	int index = 0;
	char result[100];

	do
	{
		remain = n % b;

		if (remain > 9)
			remain = remain - 10 + 'A';
		else
			remain += '0';

		result[index++] = remain;

		n /= b;
	} while (n > 0);

	for (int i = index-1; i >= 0; i--)
		printf("%c", result[i]);
}

void convert2(int n, int b)
{
	int remain;

	remain = n % b;
	n /= b;
	if (n > 0) convert2(n, b);

	if (remain < 10) printf("%d", remain);
	else printf("%c", remain - 10 + 'A');
}

typedef struct Point {
	int x;
	int y;
}Point;

double distance1(Point p[], int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += sqrt(pow(p[i].x, 2) + pow(p[i].y, 2));
	}
	return sum / n;
}

double distance2(Point p[], int n)
{
	if (n == 0)
		return sqrt(pow(p[n].x, 2) + pow(p[n].y, 2));
	else
		return sqrt(pow(p[n].x, 2) + pow(p[n].y, 2)) + distance2(p, n - 1);
}

typedef struct ListNode {
	int x;
	int y;
	struct ListNode *link;
}ListNode;

ListNode* insert_first(ListNode *head, int x, int y)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->x = x;
	p->y = y;
	p->link = head;
	head = p;
	return head;
}

double distance3(ListNode *head, int n)
{
	double sum = 0;
	for (ListNode *p = head; p != NULL; p = p->link)
	{
		sum += sqrt(pow(p->x, 2) + pow(p->y, 2));
	}
	return sum/n;
}

double distance4(ListNode *head)
{
	if (head->link == NULL)
		return sqrt(pow(head->x, 2) + pow(head->y, 2));
	else
		return distance4(head->link) + sqrt(pow(head->x, 2) + pow(head->y, 2));
}

int main(void)
{
	int sel = 0;
	int arr[] = { 9,6,2,1,7,8,5,3,4,10 };
	int decimal = 0, num = 0;
	Point p[100];
	ListNode *head = NULL;
	int n=0;

	while (1)
	{
		printf("1.�ִ�  2.������ȯ  3.��հŸ�  => "); scanf("%d", &sel); printf("\n");

		switch (sel)
		{
		case 1:
			printf("�ݺ�: %d\n", findMax1(arr, 10));
			printf("��ȯ: %d\n\n", findMax2(arr, 9));
			break;
		case 2:
			printf("���� ���� �Է�: "); scanf("%d", &decimal);
			printf("��ȯ�� ������ �Է�: "); scanf("%d", &num);
			convert1(decimal, num); printf("(%d)\n", num);
			convert2(decimal, num); printf("(%d)\n\n", num);
			break;
		case 3:
			printf("��ǥ ���� �Է�: "); scanf("%d", &n);
			for (int i = 0; i < n; i++)
			{
				printf("(%d) x y: ", i + 1);
				scanf("%d %d", &p[i].x, &p[i].y);
				head = insert_first(head, p[i].x, p[i].y);
			}
			
			printf("\n�迭/�ݺ�: %.2f\n", distance1(p, n));
			printf("�迭/��ȯ: %.2f\n", distance2(p, n - 1) / n);
			printf("����/�ݺ�: %.2f\n", distance3(head, n));
			printf("����/��ȯ: %.2f\n\n", distance4(head) / n);
			head = NULL;
			break;
		default:
			return 0;
		}
	}
	return 0;
}