#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int mergeSize = 0;

void printArr(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void printMerge(int arr[], int left, int right)
{
	if (left == 0 && right == 0) {
		for (int i = 0; i < mergeSize; i++)
			printf("%d ", arr[i]);
	}
	else {
		for (int i = 0; i < mergeSize; i++) {
			if (i == left) printf("## ");
			printf("%d ", arr[i]);
			if (i == right) printf("## ");
		}
	}
	printf("\n");
}

void merge(int arr[], int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = left;
	int l;
	int *temp = (int*)malloc(mergeSize * sizeof(int));

	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}
	if (i > mid)
		for (l = j; l <= right; l++)
			temp[k++] = arr[l];
	else
		for (l = i; l <= mid; l++)
			temp[k++] = arr[l];

	for (l = left; l <= right; l++)
		arr[l] = temp[l];

	printMerge(arr, left, right); printf("\n");

	free(temp);
}

void mergeSort(int arr[], int left, int right) {
	if (left >= right) return;
	else {
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

void heapify(int arr[], int size, int mid) {
	int parent = mid;
	int left = parent * 2 + 1;
	int right = parent * 2 + 2;
	int largest = parent;
	int temp;

	if (left < size && arr[left] > arr[largest])
		largest = left;

	if (right < size && arr[right] > arr[largest])
		largest = right;

	if (parent != largest) {
		printf("index[%d] = %d <---> index[%d] = %d\n\n", parent+1, arr[parent], largest+1, arr[largest]);
		temp = arr[largest];
		arr[largest] = arr[parent];
		arr[parent] = temp;
	
		heapify(arr, size, largest);
	}
}

void buildHeap(int arr[], int size)
{
	int mid = size / 2 - 1;

	for (mid; mid >= 0; mid--)
		heapify(arr, size, mid);
}

void heapSort(int arr[], int size)
{
	printf("\n===============================\n");
	printf("�ʱ� �� ���� ����\n");
	printf("===============================\n");
	buildHeap(arr, size);

	printf("==============================================\n");
	printf("�ʱ� ��: ");
	printArr(arr, size);
	printf("==============================================\n");

	int temp;
	while (size > 1) {
		temp = arr[0];
		arr[0] = arr[size - 1];
		arr[size - 1] = temp;

		size--;
		heapify(arr, size, 0);
		printf("### �߰� ���: ");
		for (int i = 0; i < size + 1; i++)
			printf("%d ", arr[i]);
		printf("###\n\n");
	}
}

int main(void)
{
	int sel, *arr, heapSize, exit = 0;

	while (1) {
		printf("1. ��������  2.������  3. ����  => ");
		scanf("%d", &sel); printf("\n");
		switch (sel)
		{
		case 1:
			exit = 1;
			printf("�Է��� ���� ����: ");
			scanf("%d", &mergeSize);
			arr = (int*)malloc(mergeSize * sizeof(int));

			printf("\n���� %d�� �Է�: ", mergeSize);
			for (int i = 0; i < mergeSize; i++)
				scanf("%d", &arr[i]);
			
			printf("\n<<<<<< �������� ���� >>>>>>\n");
			mergeSort(arr, 0, mergeSize - 1); printf("���� ���: ");
			printArr(arr, mergeSize); printf("\n");
			break;
		case 2:
			exit = 1;
			printf("�Է��� ���� ����: ");
			scanf("%d", &heapSize);
			arr = (int*)malloc(heapSize * sizeof(int));

			printf("\n���� %d�� �Է�: ", heapSize);
			for (int i = 0; i < heapSize; i++)
				scanf("%d", &arr[i]);

			heapSort(arr, heapSize); printf("���� ���: ");
			printArr(arr, heapSize); printf("\n");
			break;
		default:
			if(exit == 1)
				free(arr);
			return 0;
		}
	}
	return 0;
}