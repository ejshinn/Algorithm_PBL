#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int mat(int m[][6], int n) {
	int c[6][6] = { 0, };
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			
			if (i == 1 && j == 1)
				c[i][j] = m[i][j];
			else if (i == 1)
				c[i][j] = m[i][j] + c[i][j - 1];
			else if (j == 1)
				c[i][j] = m[i][j] + c[i - 1][j];
			else {
				int submax = MAX(c[i - 1][j], c[i][j - 1]);
				c[i][j] = m[i][j] + MAX(submax, c[i - 1][j - 1]);
			}
		}
	}

	printf("\n[ 메모된 배열 ]\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%2d ", c[i][j]);
		}
		printf("\n");
	}

	return c[n][n];
}

int stepCase(int n)
{
	int answer = 0;
	int tmp[1000] = { 0, };

	tmp[0] = 1;
	tmp[1] = 2;
	for (int i = 2; i < n; i++)
		tmp[i] = tmp[i - 2] + tmp[i - 1];

	answer = tmp[n - 1];
	return answer;
}

int coin1(int n) {
	int *c = (int*)malloc(sizeof(int)*(n + 1));
	int coin[3] = { 80, 50, 10 };

	for (int i = 1; i <= n; i++)
		c[i] = INT_MAX;

	c[0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			if (coin[j] <= i && c[i - coin[j]] + 1 < c[i])
				c[i] = c[i - coin[j]] + 1;
		}
	}
	return c[n];
}

int coin2(int n) {
	int coin[3] = { 80, 50, 10 };
	int one = 0, two = 0, three = 0;

	if (n >= coin[0]) {
		one = n / coin[0];
		n = n % coin[0];
	}
	if (n >= coin[1]) {
		two = n / coin[1];
		n = n % coin[1];
	}
	if (n >= coin[2]) {
		three = n / coin[2];
		n = n % coin[2];
	}
	printf("80원: %d개, 50원: %d개 10원: %d개\n", one, two, three);
	return (one+two+three);
}

int main(void) {
	int m[6][6] = {
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 5, 4, 3, 2, 1 },
	{ 0, 3, 2, 1, 5, 4 },
	{ 0, 1, 5, 4, 3, 2 },
	{ 0, 4, 3, 2, 1, 5 },
	{ 0, 2, 1, 5, 4, 3 },
	};

	int sel, num1;

	while (1) {
		printf("1.행렬 경로  2.계단  3.동전  4.종료  => ");
		scanf("%d", &sel); printf("\n");
		switch (sel) {
		case 1:
			printf("입력: "); scanf("%d", &num1);
			printf("\n결과: %d\n\n", mat(m, num1));
			break;
		case 2:
			printf("입력: "); scanf("%d", &num1);
			printf("방법의 수: %d\n\n", stepCase(num1));
			break;
		case 3:
			printf("입력: "); scanf("%d", &num1); printf("\n");
			printf("dp: %d개\n", coin1(num1));
			printf("==================================\n");
			printf("\ngreedy: %d개\n\n", coin2(num1));
			break;
		default:
			return 0;
		}
	}
	return 0;
}