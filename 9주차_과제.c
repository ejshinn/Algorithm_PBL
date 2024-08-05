#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct treeNode {
	int data;
	struct treeNode *left;
	struct treeNode *right;
} treeNode;

treeNode* addNewNode(int data, treeNode* leftNode, treeNode* rightNode) {
	treeNode* root = (treeNode *)malloc(sizeof(treeNode));
	root->data = data;
	root->left = leftNode;
	root->right = rightNode;
	return root;
}

int node_count(treeNode * node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + node_count(node->left) + node_count(node->right);
	return count;
}

int get_height(treeNode *node)
{
	int height = 0;

	if (node != NULL)
		height = 1 + MAX(get_height(node->left), get_height(node->right));
	return height;
}

void inorder(treeNode * root) {
	if (root) {
		inorder(root->left);
		printf("[%d] ", root->data);
		inorder(root->right);
	}
}

bool identical(treeNode * root1, treeNode *root2)
{
	if (root1 == NULL && root2 == NULL)
		return true;

	if (root1 == NULL || root2 == NULL)
		return false;

	return (root1->data == root2->data   &&
		identical(root1->left, root2->left) &&
		identical(root1->right, root2->right));
}

treeNode *copy(treeNode *root) {
	if (root != NULL) {
		treeNode *temp;
		temp = (treeNode *)malloc(sizeof(treeNode));
		temp->data = root->data;
		temp->left = copy(root->left);
		temp->right = copy(root->right);

		return temp;
	}
	return NULL;
}

int min_val(treeNode* node)
{
	if (node != NULL) {
		int r = node->data;
		int lr = min_val(node->left);
		int rr = min_val(node->right);
		if (lr < rr)
			r = lr;
		if (rr < r)
			r = rr;
		return r;
	}
	return INT_MAX;
}

int max_val(treeNode* node)
{
	if (node != NULL) {
		int r = node->data;
		int lr = max_val(node->left);
		int rr = max_val(node->right);
		if (lr > r)
			r = lr;
		if (rr > r)
			r = rr;
		return r;
	}
	else
		return INT_MIN;
}

int BST_check(treeNode* node)
{
	if (node == NULL)
		return 1;

	if (node->left != NULL && max_val(node->left) > node->data)
		return 0;

	if (node->right != NULL && min_val(node->right) < node->data)
		return 0;

	if (!BST_check(node->left) || !BST_check(node->right))
		return 0;

	return 1;
}

int main()
{
	int sel, tSel, tSel1 = 0, tSel2 = 0;
	
	treeNode* n8 = addNewNode(42, NULL, NULL);
	treeNode* n7 = addNewNode(30, NULL, NULL);
	treeNode* n6 = addNewNode(55, n8, NULL);
	treeNode* n5 = addNewNode(15, n7, NULL);
	treeNode* n4 = addNewNode(2, NULL, NULL);
	treeNode* n3 = addNewNode(10, NULL, n6);
	treeNode* n2 = addNewNode(16, n4, n5);
	treeNode* n1 = addNewNode(22, n2, n3);
	treeNode* T1 = n1;

	treeNode* m8 = addNewNode(42, NULL, NULL);
	treeNode* m7 = addNewNode(18, NULL, NULL);
	treeNode* m6 = addNewNode(55, m8, NULL);
	treeNode* m5 = addNewNode(20, m7, NULL);
	treeNode* m4 = addNewNode(2, NULL, NULL);
	treeNode* m3 = addNewNode(36, NULL, m6);
	treeNode* m2 = addNewNode(16, m4, m5);
	treeNode* m1 = addNewNode(22, m2, m3);
	treeNode* T2 = m1;

	treeNode* p8 = addNewNode(42, NULL, NULL);
	treeNode* p7 = addNewNode(18, NULL, p8);
	treeNode* p6 = addNewNode(55, NULL, NULL);
	treeNode* p5 = addNewNode(20, p7, NULL);
	treeNode* p4 = addNewNode(2, NULL, NULL);
	treeNode* p3 = addNewNode(36, NULL, p6);
	treeNode* p2 = addNewNode(16, p4, p5);
	treeNode* p1 = addNewNode(22, p2, p3);
	treeNode* T3 = p1;

	treeNode *tree = NULL;

	while (1) {
		printf("1.��� ����  2.����  3.������ȸ  4.���� �Ǵ�  5.���� ����  6.�����˻�Ʈ�� �Ǻ�  7.����=> ");
		scanf("%d", &sel); printf("\n");
		switch (sel)
		{
		case 1:
			printf("Ʈ�� ����(1~3): ");
			scanf("%d", &tSel);
			if (tSel == 1)
				printf("��� ����: %d\n\n", node_count(T1));
			else if(tSel == 2)
				printf("��� ����: %d\n\n", node_count(T2));
			else
				printf("��� ����: %d\n\n", node_count(T3));
			break;
		case 2:
			printf("Ʈ�� ����(1~3): ");
			scanf("%d", &tSel);
			if (tSel == 1)
				printf("����: %d\n\n", get_height(T1));
			else if (tSel == 2)
				printf("����: %d\n\n", get_height(T2));
			else
				printf("����: %d\n\n", get_height(T3));
			break;
		case 3:
			printf("Ʈ�� ����(1~3): ");
			scanf("%d", &tSel);
			printf("\n���� ��ȸ: ");
			if (tSel == 1)
				inorder(T1);
			else if (tSel == 2)
				inorder(T2);
			else
				inorder(T3);
			printf("\n\n");
			break;
		case 4:
			printf("Ʈ�� ���� 2��(1~3): ");
			scanf("%d %d", &tSel1, &tSel2);

			if (tSel1 == 1 || tSel2 == 1) {
				if (tSel2 == 2 || tSel1 == 2) {
					if (identical(T1, T2))
						printf("����\n\n");
					else
						printf("�������� ����\n\n");
				}
				else
					if (tSel2 == 3 || tSel1 == 3) {
						if (identical(T1, T3))
							printf("����\n\n");
						else
							printf("�������� ����\n\n");
					}
			}
			else if (tSel1 == 2 || tSel2 == 2) {
				if (tSel2 == 3 || tSel1 == 3) {
					if (identical(T2, T3))
						printf("����\n\n");
					else
						printf("�������� ����\n\n");
				}
			}
			break;
		case 5:
			printf("Ʈ�� ����(1~3): ");
			scanf("%d", &tSel);
			if (tSel == 1) {
				tree = copy(T1);
				printf("\nT1�� ���� �˻�: ");
				if (identical(T1, tree))
					printf("����\n\n");
				else
					printf("�������� ����\n\n");
			}
			else if (tSel == 2) {
				tree = copy(T2);
				printf("\nT2�� ���� �˻�: ");
				if (identical(T2, tree))
					printf("����\n\n");
				else
					printf("�������� ����\n\n");
			}
			else {
				tree = copy(T3);
				printf("\nT3�� ���� �˻�: ");
				if (identical(T3, tree))
					printf("����\n\n");
				else
					printf("�������� ����\n\n");
			}
			break;
		case 6:
			printf("Ʈ�� ����(1~3): ");
			scanf("%d", &tSel);
			if (tSel == 1) {
				if (BST_check(T1) == 1)
					printf("T1�� �����˻�Ʈ���Դϴ�.\n\n");
				else
					printf("T1�� �����˻�Ʈ���� �ƴմϴ�.\n\n");
			}
			else if (tSel == 2) {
				if (BST_check(T2) == 1)
					printf("T2�� �����˻�Ʈ���Դϴ�.\n\n");
				else
					printf("T2�� �����˻�Ʈ���� �ƴմϴ�.\n\n");
			}
			else {
				if (BST_check(T3) == 1)
					printf("T3�� �����˻�Ʈ���Դϴ�.\n\n");
				else
					printf("T3�� �����˻�Ʈ���� �ƴմϴ�.\n\n");
			}
			break;
		default:
			return 0;
		}
	}
	return 0;
}