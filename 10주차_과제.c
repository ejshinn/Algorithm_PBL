#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

TreeNode * search(TreeNode * node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

void inorder(TreeNode * root)
{
	if (root) {
		inorder(root->left);
		printf("[%d] ", root->key);
		inorder(root->right);
	}
}

TreeNode* addNewNode(int key, TreeNode* leftNode, TreeNode* rightNode) {
	TreeNode* root = (TreeNode *)malloc(sizeof(TreeNode));
	root->key = key;
	root->left = leftNode;
	root->right = rightNode;
	return root;
}

TreeNode * new_node(int item)
{
	TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode * insert_node(TreeNode * node, int key)
{
	if (node == NULL) return new_node(key);

	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);

	return node;
}

TreeNode * min_value_node(TreeNode * node)
{
	TreeNode * current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

TreeNode * delete_node(TreeNode * root, int key)
{
	if (root == NULL) return root;

	if (key < root->key)
		root->left = delete_node(root->left, key);
	else if (key > root->key)
		root->right = delete_node(root->right, key);

	else {
		//ù ��°�� �� ��° ���
		if (root->left == NULL) {
			TreeNode * temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode * temp = root->left;
			free(root);
			return temp;
		}
		// �� ��° ���
		TreeNode * temp = min_value_node(root->right);
		root->key = temp->key;
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

int IPL(TreeNode * root, int value)
{
	if (root == NULL)
		return 0;
	printf("key: %d  value: %d\n", root->key, value);
	return (value + IPL(root->right, value + 1) + IPL(root->left, value + 1));
}

int node_count(TreeNode * root) {
	if (!root)
		return 0;
	else
		return (1 + node_count(root->left) + node_count(root->right));
}

double average_search_performance(TreeNode * root, int IPL)
{
	if (IPL == 0)
		return 0;
	else {
		printf("IPL: %d  node ����: %d\n", IPL, node_count(root));
		return (double)IPL / (double)(node_count(root));
	}
}

int hasPathSum(TreeNode * root, int sum)
{
	if (!root)
		return 0;
	if (!root->left && !root->right && root->key == sum)
		return 1;
	return hasPathSum(root->left, sum - root->key) || hasPathSum(root->right, sum - root->key);
}

int main(void)
{
	TreeNode* m8 = addNewNode(42, NULL, NULL);
	TreeNode* m7 = addNewNode(18, NULL, NULL);
	TreeNode* m6 = addNewNode(55, m8, NULL);
	TreeNode* m5 = addNewNode(20, m7, NULL);
	TreeNode* m4 = addNewNode(2, NULL, NULL);
	TreeNode* m3 = addNewNode(36, NULL, m6);
	TreeNode* m2 = addNewNode(16, m4, m5);
	TreeNode* m1 = addNewNode(22, m2, m3);
	TreeNode* T1 = m1;

	int sel, number, num, sumNum;

	while (1) {
		printf("1.�˻�  2.����  3.����  4.IPL  5.��� �˻� ����  6.���� ��� ��� ��  7.����=> ");
		scanf("%d", &sel); printf("\n");
		switch (sel) {
		case 1:
			printf("�˻��� Ű: "); scanf("%d", &num);
			if (search(T1, num) != NULL)
				printf("���� �˻� Ʈ������ %d��(��) �߰���\n\n", num);
			else
				printf("���� �˻� Ʈ������ %d��(��) �߰� ����\n\n", num);
			break;
		case 2:
			printf("�Է��� ���� ����: "); scanf("%d", &number);
			printf("���� �Է�: ");
			for (int i = 0; i < number; i++) {
				scanf("%d", &num);
				T1 = insert_node(T1, num);
			}
			printf("\n���� ��ȸ ���\n");
			inorder(T1); printf("\n\n");
			break;
		case 3:
			printf("���� �Է�: "); scanf("%d", &num);
			if (search(T1, num) == NULL)
				printf("���� �˻� Ʈ������ %d��(��) ����\n\n", num);
			else {
				T1 = delete_node(T1, num);
				printf("\n���� ��ȸ ���\n");
				inorder(T1); printf("\n\n");
			}
			break;
		case 4:
			printf("IPL: %d\n\n", IPL(T1, 1));
			break;
		case 5:
			printf("��� �˻� ����: %.2f\n\n", average_search_performance(T1, IPL(T1, 1)));
			break;
		case 6:
			printf("�� �Է�: "); scanf("%d", &sumNum);
			if (hasPathSum(T1, sumNum))
				printf("��ΰ� ������\n\n");
			else
				printf("��ΰ� �������� ����\n\n");
			break;
		default:
			return 0;
		}
	}
	return 0;
}