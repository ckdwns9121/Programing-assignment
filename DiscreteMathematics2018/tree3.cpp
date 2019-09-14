#include <fstream>
#include <cstdlib>
#pragma warning(disable:4996)
using namespace std;
#define MAX_INDEX 10002
ifstream input_fp("tree3.inp");
ofstream output_fp("tree3.out");

int preorder[MAX_INDEX];
int inorder[MAX_INDEX];
int postorder[MAX_INDEX];

/* tree struct*/
typedef struct treeNode {
	int Root;
	struct treeNode* left;
	struct treeNode* right;
}treeNode;
/*insert key*/
treeNode* insertNode(treeNode* root, int data, bool check) {
	treeNode* newNode;
	if (root == NULL) {
		newNode = (treeNode*)malloc(sizeof(treeNode));
		newNode->Root = data;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else if (check == false) root->right = insertNode(root->right, data, check);
	else if (check == true) root->left = insertNode(root->left, data, check);
	return root;
}
/*array reversing*/
void reverseArrayInt(int* array, int size) {
	int temp = 0;
	int n = size;
	for (int i = 1; i <= size / 2; i++) {
		temp = array[i];
		array[i] = array[n];
		array[n] = temp;
		n--;
	}
}
/*root finding*/
int find_root(int type_Result, int n) {
	int root;
	if (type_Result < 0)  root = preorder[1];
	else if (type_Result > 0) root = postorder[n];
	return root;
}
/*preorder printing*/
void PreOrder_print(treeNode * node) {
	if (node == NULL)return;
	output_fp << node->Root << endl;
	PreOrder_print(node->left);
	PreOrder_print(node->right);
}
/*postorder printing*/
void PostOrder_print(treeNode * node) {
	if (node == NULL)return;
	PostOrder_print(node->left);
	PostOrder_print(node->right);
	output_fp << node->Root << endl;
}
/*make tree use preorder array*/
void preorder_check(treeNode * tree, int count, int root) {
	int Left, Right;
	int Left_count = -1, Right_count = -1;
	int preorder_Rindex = 0, inorder_Rindex = 0;
	/*finding root's index in preorder array*/
	for (int j = 1; j <= count; j++) {
		if (root == preorder[j]) {
			preorder_Rindex = j;
			break;
		}
	}
	/*finding root's index in inorder array*/
	for (int j = 1; j <= count; j++) {
		if (root == inorder[j]) {
			inorder_Rindex = j;
			break;
		}
	}
	/*left subtree right subtree count*/
	for (int j = inorder_Rindex; j <= count; j++) {
		if (inorder[j] == -1)break;
		else Right_count++;
	}
	for (int j = inorder_Rindex; j >= 0; j--) {
		if (inorder[j] == -1)break;
		else Left_count++;
	}
	/* leftsubtree && rightsubtree ==NULL --> return */
	if (Left_count == 0 && Right_count == 0) {
		preorder[preorder_Rindex] = -1;
		inorder[inorder_Rindex] = -1;
		return;
	}
	/* leftsubtree==NULL root= rightsubtree */
	else if (Left_count == 0 && Right_count != 0) {
		Right = preorder[preorder_Rindex + 1];
		insertNode(tree, Right, false);
		preorder[preorder_Rindex] = -1;
		inorder[inorder_Rindex] = -1;
		preorder_check(tree->right, count, Right);
	}
	/* 루트의 왼쪽값이 없으면 전위순회기준 루트오른쪽값이 오른쪽서브트리 */
	else if (Left_count != 0 && Right_count == 0) {
		Left = preorder[preorder_Rindex + 1];
		insertNode(tree, Left, true);
		preorder[preorder_Rindex] = -1;
		inorder[inorder_Rindex] = -1;
		preorder_check(tree->left, count, Left);
	}
	/* 둘다 값이 있으면 */
	else {
		Left = preorder[preorder_Rindex + 1];
		Right = preorder[preorder_Rindex + 1 + Left_count];
		insertNode(tree, Left, true);
		insertNode(tree, Right, false);
		preorder[preorder_Rindex] = -1;
		inorder[inorder_Rindex] = -1;
		preorder_check(tree->left, count, Left);
		preorder_check(tree->right, count, Right);
	}
}
void postorder_check(treeNode * tree, int count, int root) {
	int Left, Right;
	int Left_count = -1, Right_count = -1;
	int postorder_Rindex = 0, inorder_Rindex = 0;

	/*후위배열에서 root 인덱스 찾기*/
	for (int j = 1; j <= count; j++) {
		if (root == postorder[j]) {
			postorder_Rindex = j; //인덱스저장
			break;
		}
	}
	/*중위배열에서 root 인덱스찾기*/
	for (int j = 1; j <= count; j++) {
		if (root == inorder[j]) {
			inorder_Rindex = j; //인덱스저장
			break;
		}
	}
	/*left subtree right subtree count*/
	for (int j = inorder_Rindex; j <= count; j++) {
		if (inorder[j] == -1)break;
		else Right_count++;
	}
	for (int j = inorder_Rindex; j >= 0; j--) {
		if (inorder[j] == -1)break;
		else Left_count++;
	}
	/*root 기준 left right 값이 없으면 leaf node 라는뜻 return*/
	if (Left_count == 0 && Right_count == 0) {
		postorder[postorder_Rindex] = -1;
		inorder[inorder_Rindex] = -1;
		return;
	}
	/*root의 왼쪽값이 없으면 후위순회기준 root오른쪽값이 left subtree*/
	else if (Left_count == 0 && Right_count != 0) {
		Left = postorder[postorder_Rindex + 1];
		insertNode(tree, Left, true);
		postorder[postorder_Rindex] = -1;
		inorder[inorder_Rindex] = -1;
		postorder_check(tree->left, count, Left);
	}
	/* 루트의 왼쪽값이 없으면 후위순회기준 루트오른쪽값이 왼쪽서브트리 */
	else if (Left_count != 0 && Right_count == 0) {
		Right = postorder[postorder_Rindex + 1];
		insertNode(tree, Right, false);
		postorder[postorder_Rindex] = -1;
		inorder[inorder_Rindex] = -1;
		postorder_check(tree->right, count, Right);
	}
	/*값이 둘다 있을경우*/
	else {
		Right = postorder[postorder_Rindex + 1];
		Left = postorder[postorder_Rindex + 1 + Right_count];
		insertNode(tree, Right, false);
		insertNode(tree, Left, true);
		postorder[postorder_Rindex] = -1;
		inorder[inorder_Rindex] = -1;
		postorder_check(tree->left, count, Left);
		postorder_check(tree->right, count, Right);
	}
}
/*전위순회인지 후위순회인지 판단해서 점프*/
void JUMP(treeNode * tree, int type_Result, int count, int root) {
	if (type_Result < 0) preorder_check(tree, count, root);
	else postorder_check(tree, count, root);
}
int main() {
	int len, type, type_result = 0;
	int root;
	treeNode* tree = NULL;
	input_fp >> len;
	preorder[0] = -1;
	inorder[0] = -1;
	postorder[0] = -1;
	preorder[len + 1] = -1;
	inorder[len + 1] = -1;
	postorder[len + 1] = -1;
	for (int i = 0; i < 2; i++) {
		input_fp >> type;
		type_result += type;
		for (int j = 1; j <= len; j++) {
			if (type == -1) input_fp >> preorder[j];
			else if (type == 0) input_fp >> inorder[j];
			else input_fp >> postorder[j];
		}
	}
	root = find_root(type_result, len);
	if (type_result == 1) reverseArrayInt(postorder, len);
	tree = insertNode(tree, root, NULL);
	JUMP(tree, type_result, len, root);
	if (type_result < 0) PostOrder_print(tree);
	else PreOrder_print(tree);
	input_fp.close();
	output_fp.close();
	return 0;
}
