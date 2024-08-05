#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int cnt = 0;
int Recursion_BinarySearch(int arr[], int low, int high, int key)
{
	int mid = 0;

	if (low > high)
		return -1;

	mid = (low + high) / 2;
	printf("\n�˻� ����: [%d - %d]\n", low, high);
	printf("�߰� ��ġ: %d\n", mid);
	printf("�� ��: %d\n", arr[mid]);
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
		printf("\n�˻� ����: [%d - %d]\n", low, high);
		printf("�߰� ��ġ: %d\n", mid);
		printf("�� ��: %d\n\n", arr[mid]);
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
	printf("Fibonacci(%d) ȣ��\n", n);
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
		printf("1.�����˻�(���)  2.�����˻�(�ݺ�)  3. ���(���)  4. ���(�ݺ�)  5.�Ǻ���ġ ����  => ");
		scanf("%d", &sel); printf("\n");

		switch (sel) {
		case 1:
			for (int i = 0; i < 30; i++)
				printf("%d ", arr[i]);
			printf("\nã�� ��: "); scanf("%d", &key);
			result = Recursion_BinarySearch(arr, 0, 29, key);

			if (result == -1)
				printf("\n�˻� ����\n");
			else
				printf("\n�˻� ����\n");
			printf("�� Ƚ��: %d\n\n", cnt);
			cnt = 0;
			break;
		case 2:
			for (int i = 0; i < 30; i++)
				printf("%d ", arr[i]);
			printf("\nã�� ��: "); scanf("%d", &key);
			result = Iteration_BinarySearch(arr, 0, 29, key);

			if (result == -1)
				printf("\n�˻� ����\n");
			else
				printf("\n�˻� ����\n");
			printf("�� Ƚ��: %d\n\n", cnt);
			cnt = 0;
			break;
		case 3:
			printf("��� n�� �Է�: "); scanf("%d", &n);
			for (int i = 0; i < n; i++) {
				Recursion_BinarySearch(arr, 0, n - 1, arr[i]);
				printf("\n< arr[%d]�� �� Ƚ��: %d >\n", i, cnt);
				if (max < cnt)
					max = cnt;
				RecursionSum += cnt;
				cnt = 0;
			}
			printf("\n��� �� Ƚ��(���): %.2f\n", (double)RecursionSum / n);
			printf("�־��� ���(���): %d��\n\n", max);
			RecursionSum = 0, max = 0;
			break;
		case 4:
			printf("��� n�� �Է�: "); scanf("%d", &n);
			for (int i = 0; i < n; i++) {
				Iteration_BinarySearch(arr, 0, n - 1, arr[i]);
				printf("\n< arr[%d]�� �� Ƚ��: %d >\n", i, cnt);
				if (max < cnt)
					max = cnt;
				IterationSum += cnt;
				cnt = 0;
			}
			printf("\n��� �� Ƚ��(�ݺ�): %.2f\n", (double)IterationSum / n);
			printf("�־��� ���(�ݺ�): %d��\n\n", max);
			IterationSum = 0, max = 0;
			break;
		case 5:
			printf("�Ǻ���ġ �� �Է�: "); scanf("%d", &fiboNum);
			printf("���: %d\n", Fibonacci(fiboNum));
			printf("\n�Լ� ȣ�� %d��\n\n", cnt2);
			cnt2 = 0;
			break;
		default:
			return 0;
		}
	}
	return 0;
}