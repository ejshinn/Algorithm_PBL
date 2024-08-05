#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int n)
{
	int j, key, step = 1, cnt = 0, cntSum = 0;

	for (int i = 1; i < n; i++) {
		key = arr[i];

		for (j = i - 1; j >= 0; j--) {
			cnt++;
			if (arr[j] > key)
				arr[j + 1] = arr[j];
			else
				break;
		}
		arr[j + 1] = key;

		printf("%d단계: ", step++);
		for (int k = 0; k < n; k++) {
			printf("%d ", arr[k]);
			if (k == i)
				printf("| ");
		}
		printf("\n비교횟수: %d\n\n", cnt);
		cntSum += cnt; cnt = 0;
	}
	printf("전체 비교 횟수: %d\n", cntSum);
}

/*
void bubbleSort(int arr[], int n)
{
	int temp, step = 1, sorted = 0; // 중간에 정렬이 한 번도 이루어지지 않았다면 정렬이 된 것이므로 정렬 중단
	for (int last = n; last <= 2; n--) {
		if (sorted == 1)
			break;
		sorted = 1;
		printf("  %d단계>>\n", step++);
		for (int i = 1; i <= last - 1; i++) {
			if (arr[i] > arr[i + 1]) {         // 현재 요소의 값과 다음 요소의 값을 비교하여 큰 값을
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;            // 다음 요소로 보냄
				sorted = 0;
			}
		}
		printf("	");
		for (int k = 0; k < n; k++)
			printf("%d ", arr[k]);
		printf("\n");
	}
}*/
/*
void bubbleSort(int arr[], int n)
{
	int temp, step = 1, sorted = 0; // 중간에 정렬이 한 번도 이루어지지 않았다면 정렬이 된 것이므로 정렬 중단
	for (int i = n - 1; i >= 0; i--) {
		if (sorted == 1)
			break;
		sorted = 1;
		printf("  %d단계>>\n", step++);
		for (int j = 0; j < i; j++) {
			if (arr[j + 1] >= arr[j])
				continue;
			         // 현재 요소의 값과 다음 요소의 값을 비교하여 큰 값을
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;            // 다음 요소로 보냄
				sorted = 0;
		}
		printf("	");
		for (int k = 0; k < n; k++) {
			printf("%d ", arr[k]);
		}
		printf("\n");
	}
}*/

int cntSum2 = 0;
void bubbleSort(int arr[], int n)
{
	int temp, step = 1, sorted = 0, cnt = 0, b = 0;
	for (int i = n - 1; i >= 0; i--) {
		sorted = 1;
		for (int j = 0; j < i; j++) {
			cnt++;
			if (arr[j + 1] < arr[j]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				sorted = 0;
			}
			if (b == 0) {
				printf("  %d단계>>\n", step++);
				b++;
			}
			printf("	");
			for (int k = 0; k < n; k++) {
				printf("%d ", arr[k]);
			}
			printf("\n");
		}
		if(cnt != 0)
			printf("  비교횟수: %d\n\n", cnt);
		cntSum2 += cnt; cnt = 0; b = 0;
		if (sorted == 1)
			return;
	}
}

int main(void)
{
	int sel, size, *arr;
	while (1) {
		printf("1.삽입정렬  2.버블정렬  3.종료  => ");
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
			printf("\n<<<<< 삽입정렬 수행 >>>>>\n\n");
			insertionSort(arr, size);
			printf("\n");
			break;
		case 2:
			printf("입력할 수의 개수: ");
			scanf("%d", &size);

			arr = (int*)malloc(size * sizeof(int));

			printf("\n정수 %d개 입력: ", size);
			for (int i = 0; i < size; i++)
				scanf("%d", &arr[i]);
			printf("\n<<<<< 버블정렬 수행 >>>>>\n\n");
			bubbleSort(arr, size);
			printf("전체 비교 횟수: %d\n", cntSum2); cntSum2 = 0;
			printf("\n");
			break;
		default:
			return 0;
		}
	}
	return 0;
}