#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int a, int b) {
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int partition1(int A[], int p, int r)
{
	int x = A[r]; //기준원소
	int i = p - 1;

	for (int a = p; a <= r; a++) {
		if (a == r)
			printf("[ %d ]", A[a]);
		else
			printf("%d ", A[a]);
	}
	printf("\n");

	for (int j = p; j < r; j++) {
		if (A[j] <= x)
			swap(A, ++i, j);
	}
	swap(A, i + 1, r);

	printf("변경: ");
	for (int a = p; a <= r; a++) {
		if (a == i+1)
			printf("[ %d ] ", A[a]);
		else
			printf("%d ", A[a]);
	}
	printf("\n\n");

	return i + 1;
}

int partition2(int A[], int left, int right)
{
	int pivot;
	int low, high;

	low = left;
	high = right + 1;
	pivot = A[left];

	for (int a = left; a <= right; a++) {
		if (a == left)
			printf("[ %d ] ", A[a]);
		else
			printf("%d ", A[a]);
	}
	printf("\n");

	do {
		do
			low++;
		while (A[low] < pivot);
		do
			high--;
		while (A[high] > pivot);
		if (low < high)
			swap(A, low, high);
	} while (low < high);

	swap(A, left, high);

	printf("변경: ");
	for (int a = left; a <= right; a++) {
		if (a == high)
			printf("[ %d ] ", A[a]);
		else
			printf("%d ", A[a]);
	}
	printf("\n\n");

	return high;
}

int partition3(int A[], int begin, int end)
{
	//int pivot = (begin + end) / 2;
	int mid = (begin + end) / 2; //중간값의 인덱스 선택
	swap(A, begin, mid); //중간값의 인덱스를 왼쪽 데이터와 교환

	int pivot = begin; //피봇 설정
	int L = begin;
	int R = end;

	for (int a = begin; a <= end; a++) {
		if (a == pivot)
			printf("[ %d ] ", A[a]);
		else
			printf("%d ", A[a]);
	}
	printf("\n");

	while (L < R)
	{
		while (A[L] < A[pivot] && L < R) {
			L++;
		}
		while (A[R] >= A[pivot] && L < R) {
			R--;
		}
		if (L < R) {
			swap(A, L, R);
		}
	}
	printf("pivot: %d\n", A[pivot]);
	printf("변경: ");
	for (int a = begin; a <= end; a++) {
		if (a == pivot)
			printf("[%d] ", A[a]);
		else
			printf("%d ", A[a]);
	}
	printf("\n\n");

	return R;
}

void quickSort1(int A[], int p, int r)
{
	if (p >= r) return;
	else {
		int q = partition1(A, p, r);
		quickSort1(A, p, q - 1);
		quickSort1(A, q + 1, r);
	}
}

void quickSort2(int A[], int p, int r)
{
	if (p >= r) return;
	else {
		int q = partition2(A, p, r);
		quickSort2(A, p, q - 1);
		quickSort2(A, q + 1, r);
	}
}

void quickSort3(int A[], int p, int r)
{
	if (p >= r) return;
	else {
		int q = partition3(A, p, r);
		quickSort3(A, p, q - 1);
		quickSort3(A, q + 1, r);
	}
}

int main(void)
{
	int sel, *arr, size;

	while (1) {
		printf("1.피봇 맨 마지막  2.피봇 맨 앞  3.피봇 가운데  => ");
		scanf("%d", &sel); printf("\n");
		switch (sel)
		{
		case 1:
			printf("입력할 수의 개수: ");
			scanf("%d", &size);		
			arr = (int*)malloc(size * sizeof(int));

			printf("\n정수 %d개 입력: ", size);
			for (int i = 0; i < size; i++)
				scanf("%d", &arr[i]);

			quickSort1(arr, 0, size - 1); printf("정렬 결과: ");
			for (int i = 0; i < size; i++)
				printf("%d ", arr[i]);
			printf("\n\n");
			break;
		case 2:
			printf("입력할 수의 개수: ");
			scanf("%d", &size);
			arr = (int*)malloc(size * sizeof(int));

			printf("\n정수 %d개 입력: ", size);
			for (int i = 0; i < size; i++)
				scanf("%d", &arr[i]);

			quickSort2(arr, 0, size - 1); printf("정렬 결과: ");
			for (int i = 0; i < size; i++)
				printf("%d ", arr[i]);
			printf("\n\n");
			break;
		case 3:
			printf("입력할 수의 개수: ");
			scanf("%d", &size);
			arr = (int*)malloc(size * sizeof(int));

			printf("\n정수 %d개 입력: ", size);
			for (int i = 0; i < size; i++)
				scanf("%d", &arr[i]);

			quickSort3(arr, 0, size - 1); printf("정렬 결과: ");
			for (int i = 0; i < size; i++)
				printf("%d ", arr[i]);
			printf("\n\n");
			break;
		default:
			free(arr);
			return 0;
		}
	}
	return 0;
}