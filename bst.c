/* Binary Search Tree 並且用 inorder輸出*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}TreeNode;
//typedef struct node TreeNode;

// 用 StackNode 存子樹，pop 然後設成 inorder的下一個 curTree
typedef struct list
{
	struct node *treenode;
	struct list *next;
}StackNode;


void addTreeNode(TreeNode *, int);
void inorder(TreeNode *);
TreeNode* pop(StackNode *top);
void push(StackNode *top, TreeNode *treenode);
void printList(StackNode *cur);


int main(int argc, char *argv[])
{
/*
	TreeNode three = {3, NULL, NULL};
	TreeNode two = {2, NULL, &three};
	TreeNode one = {1, NULL, &two};
	TreeNode four = {4, &one, NULL};
	TreeNode five = {5, &four, NULL};
	TreeNode onethree = {13, NULL, NULL};
	TreeNode root = {10, &five, &onethree};
*/
	TreeNode root = {10, NULL, NULL};

	
	addTreeNode(&root, 5);
	addTreeNode(&root, 13);
	addTreeNode(&root, 4);

    int input[9]={1,2,3,44,8,66,23,77,50};
	for (int i = 0; i < 9; ++i)
	{
		//printf("輸入的子樹：%d\n", input[i]);
		addTreeNode(&root, input[i]);
	}

	inorder(&root);


	return 0;
}

void printList(StackNode *cur)
{
	printf("Stack 目前為：");
	for (; cur->next!=NULL ; cur=cur->next)
		printf("%d\t", cur->next->treenode->data);
	printf("\n");
}

void push(StackNode *top, TreeNode *treenode)
{
	StackNode *newnode = (StackNode*) malloc(sizeof(StackNode));
	//printf("在Push function\n");
	newnode->treenode = treenode;
	newnode->next = top->next;
	top->next = newnode;
	printList(top);
}

TreeNode* pop(StackNode *top)
{
	if (top->next == NULL)
	{
		printf("Stack Node 為空\n");
		return NULL;
	}

	//printf("開始pop\n");
	StackNode *pop_data = top->next;
	if (top->next->next == NULL)
	{
		top->next = NULL;
		free(pop_data);
	}
	else
	{
		StackNode *next_data = top->next->next;
		//printf("準備要設定 tree node: %d\n",next_data->treenode->data);
		top->next = next_data;
	}

	printf("準備 return的 treenode->data: %d\n", pop_data->treenode->data);
	printList(top);
	return pop_data->treenode;
}

void inorder(TreeNode *cur)
{
	StackNode top = {NULL, NULL};
	while(1)
	{

		if (cur->left == NULL)
		{
			printf("左子樹為空，可以印中序了 %d =======\n", cur->data );

			if (cur->right == NULL)
			{
				if (top.next != NULL)
				{
					cur = pop(&top);
					printf("cur->data pop出來的 TreeNode data:%d \n", cur->data);
				}
				else
					break;
			}
			else // 有右子樹
			{
				cur = cur->right;
				continue;
			}


			cur->left = NULL;
			free(cur->left);
			//printf("flag 2\n");
		}
		else
		{
			/*
			if (cur->right != NULL)
			{
				printf("準備要push 的右子樹 %d\n", cur->right->data);
				push(&top, cur->right);
			}*/
			printf("準備要push 的自己%d\n", cur->data);
			push(&top, cur);
			printf("準備要把 左子樹設為新的 cur \n");
			cur = cur->left;
			printf("現在的 子樹是%d，要離開else\n", cur->data);
		}
		//printf("while 的最後面\n");
	}
}

void addTreeNode(TreeNode *root, int input)
{
	TreeNode *cur = root;

	while(1)
	{
		//printf("=== Input == %d\n", input);
		if (input > cur->data) 
		{
			//printf("@if (input > cur->data) \n");

			if( cur->right == NULL)
			{
				
				TreeNode *newNode = (TreeNode*) malloc(sizeof(TreeNode));
				newNode->data = input;
				newNode->left = NULL;
				newNode->right = NULL;
				cur->right = newNode;
				break;

			}
			else
			{
				cur = cur->right;
				//printf("current: %d\n", cur->data );
				continue;
			}
		}
		else // input[i] < cur->data
		{
			//printf("@else // input < cur->data \n");
		
			if ( cur->left == NULL)
			{
				//printf("cur->left\n");
				TreeNode *newNode = (TreeNode*) malloc(sizeof(TreeNode));
				newNode->data = input;
				newNode->left = NULL;
				newNode->right = NULL;
				cur->left = newNode;
				break;
			}
			else
			{
				//printf("Cur 即將指向 %d\n", cur->left->data);
				cur = cur->left;
				continue;	
			}

		}
	}
	// End of While
}