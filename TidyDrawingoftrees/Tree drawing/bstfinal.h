/*
	*	.h file that just creates a basic BST to be used for our programs
	*	Returns a pair containing the root and the height of the tree
*/

#include <stdio.h>


 struct Node {
	int data;					//information
	struct Node *left;		//pointer to left subtree
	struct Node *right;		//pointer to right subtree
	struct Node *parent;
	int level;
	int x;						//x coordinate of node
	int y;						//y coordinate of node
	int offset;					//distance to each son
	bool thread;				//Threading active or not
};

struct extreme {
	struct Node *addr;	//address
	int offset;		//offset from root of subtree
	int level;		//tree level
};

//Creates a new node and returns it
struct Node* getNode(int val, int height){
	struct Node *root = (struct Node*)malloc(sizeof(struct Node));
	root->data = val;
	root->x = 0;
	root->y = height;
	root->left = root->right = NULL;
	root->parent = NULL;
	return root;
}

//!Insert node into BST
struct Node* Insert(struct Node* root, int data, int height){
    if(root == NULL)
        root = getNode(data, height);
    else if(data <= root->data){
        struct Node *lchild = Insert(root->left, data, height+1);
        root->left = lchild;
        lchild->parent = root; 
    }
    else{
        struct Node *rchild = Insert(root->right, data, height+1);
        root->right = rchild;
        rchild->parent = root;
    }
    return root;
}


//!Creates a binary tree and returns its root and height
struct Node* bst_init(){
	struct Node *root = NULL;
	//int arr[] = {1, 2, 3, 4, 5};
	int arr[] = {20, 23, 45, 1, 24, 4, 34, 20, 23, 45, 1, 24, 4, 34 };
	int n = sizeof(arr)/sizeof(arr[0]);

	//insert all elements in BST
	for(int i=0; i<n; i++)
		root = Insert(root, arr[i], 0);

	return root;
}
