#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int cnt = 0;
int Recursion_BinarySearch(int arr[], int low, int high, int key)
{
	int mid = 0;

	if (low > high)
		return -1;

	mid = (low + high) / 2;
	printf("\n검색 범위: [%d - %d]\n", low, high);
	printf("중간 위치: %d\n", mid);
	printf("비교 값: %d\n", arr[mid]);
	cnt++;

	if (arr[mid] == key)
		return mid;
	else if (key < arr[mid])
		return Recursion_BinarySearch(arr, low, mid - 1, key);
	else
		return Recursion_BinarySearch(arr, mid + 1, high, key);
}

int Iteration_BinarySearch(int arr[], int low, int high, int key)
{
	int mid = 0;

	while (low <= high) {
		mid = (low + high) / 2;
		printf("\n검색 범위: [%d - %d]\n", low, high);
		printf("중간 위치: %d\n", mid);
		printf("비교 값: %d\n\n", arr[mid]);
		cnt++;

		if (key == arr[mid])
			return mid;
		else if (key > arr[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}

	return -1;
}

int cnt2 = 0;
int Fibonacci(int n)
{
	cnt2++;
	printf("Fibonacci(%d) 호출\n", n);
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main(void)
{
	int sel, fiboNum, key, result = 0, n, RecursionSum = 0, IterationSum = 0, max = 0;
	int arr[30] = {
		0, 3, 5, 7, 11, 16, 17, 19, 20, 23,
		27, 29, 33, 37, 41, 42, 46, 49, 51, 53,
		54, 57, 60, 66, 70, 73, 77, 79, 81, 89
	};

	while (1) {
		printf("1.이진검색(재귀)  2.이진검색(반복)  3. 평균(재귀)  4. 평균(반복)  5.피보나치 수열  => ");
		scanf("%d", &sel); printf("\n");

		switch (sel) {
		case 1:
			for (int i = 0; i < 30; i++)
				printf("%d ", arr[i]);
			printf("\n찾는 값: "); scanf("%d", &key);
			result = Recursion_BinarySearch(arr, 0, 29, key);

			if (result == -1)
				printf("\n검색 실패\n");
			else
				printf("\n검색 성공\n");
			printf("비교 횟수: %d\n\n", cnt);
			cnt = 0;
			break;
		case 2:
			for (int i = 0; i < 30; i++)
				printf("%d ", arr[i]);
			printf("\n찾는 값: "); scanf("%d", &key);
			result = Iteration_BinarySearch(arr, 0, 29, key);

			if (result == -1)
				printf("\n검색 실패\n");
			else
				printf("\n검색 성공\n");
			printf("비교 횟수: %d\n\n", cnt);
			cnt = 0;
			break;
		case 3:
			printf("평균 n개 입력: "); scanf("%d", &n);
			for (int i = 0; i < n; i++) {
				Recursion_BinarySearch(arr, 0, n - 1, arr[i]);
				printf("\n< arr[%d]의 비교 횟수: %d >\n", i, cnt);
				if (max < cnt)
					max = cnt;
				RecursionSum += cnt;
				cnt = 0;
			}
			printf("\n평균 비교 횟수(재귀): %.2f\n", (double)RecursionSum / n);
			printf("최악의 경우(재귀): %d번\n\n", max);
			RecursionSum = 0, max = 0;
			break;
		case 4:
			printf("평균 n개 입력: "); scanf("%d", &n);
			for (int i = 0; i < n; i++) {
				Iteration_BinarySearch(arr, 0, n - 1, arr[i]);
				printf("\n< arr[%d]의 비교 횟수: %d >\n", i, cnt);
				if (max < cnt)
					max = cnt;
				IterationSum += cnt;
				cnt = 0;
			}
			printf("\n평균 비교 횟수(반복): %.2f\n", (double)IterationSum / n);
			printf("최악의 경우(반복): %d번\n\n", max);
			IterationSum = 0, max = 0;
			break;
		case 5:
			printf("피보나치 수 입력: "); scanf("%d", &fiboNum);
			printf("결과: %d\n", Fibonacci(fiboNum));
			printf("\n함수 호출 %d번\n\n", cnt2);
			cnt2 = 0;
			break;
		default:
			return 0;
		}
	}
	return 0;
}