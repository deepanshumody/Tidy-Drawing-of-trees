/** This Program Implements Binary Search Tree in OpenGL using TR algorithm and bresenham's line and circle algorithms
*While printing the nodes it traverses the BST inorder 
*/

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <climits>
#include <algorithm>
#include <vector>

#include "bstfinal.h"									//header file that constructs a BST
#include "drawfinal.h"									//header file that draws the tree
using namespace std;
#include <chrono> 
using namespace std::chrono;

#define MINSEP 50									/*! \def Minimum seperation between roots of subtrees */

struct Node* setup(struct Node* root, int level, extreme &rightmost, extreme &leftmost) {
	struct Node* left;
	struct Node* right;						// Left and Right sons
	struct extreme LR, LL, RR, RL;			// LR = Rightmost node on lowest level of left subtree and so on
	int CURsep, ROOTsep, LOffsum, ROffsum;	// CURsep = Seperation on current level, ROOTsep = current seperation at node T
	if (root == NULL) {						// LOffsum, ROffsum = Offset from L and R to T
		leftmost.level = -1;
		rightmost.level = -1;
	}
	else {
		root->y = level;
		left = root->left;
		right = root->right;
		setup(left, level +1, LR, LL);       //Position left subtree recursively 
		setup(right, level +1, RR, RL);	  	 //Postion right subtree recursively
		if (left == NULL && right == NULL) {
			rightmost.addr = root;
			leftmost.addr = root;
			rightmost.level = level;
			leftmost.level = level;
			rightmost.offset = 0;
			leftmost.offset = 0;
			root->offset = 0;
		}
		else {

			//Set up for subtree pushing. Place roots of subtrees minimum distance apart
			CURsep = MINSEP;
			ROOTsep = MINSEP;
			LOffsum = 0;
			ROffsum = 0;
			/*Now consider each level  in turn until one subtree is exhausted
			pushing the subtrees apart when neccessary.*/
			while (left != NULL && right != NULL) {
				if (CURsep < MINSEP) {
					ROOTsep = ROOTsep + (MINSEP - CURsep);
					CURsep = MINSEP;
				}
				//Advance left 
				if (left->right != NULL) {
					LOffsum = LOffsum + left->offset;
					CURsep = CURsep - left->offset;
					left = left->right;
				}
				else {
					LOffsum = LOffsum - left->offset;
					CURsep = CURsep + left->offset;
					left = left->left;
				}
				//Advance right
				if (right->left != NULL) {
					ROffsum = ROffsum - right->offset;
					CURsep = CURsep - right->offset;
					right = right->left;
				}
				else {
					ROffsum = ROffsum + right->offset;
					CURsep = CURsep + right->offset;
					right = right->right;
				}
			}
			/*Set the offset in node root and include it in accumulated offsets in right and left*/
			root->offset = (ROOTsep + 1) / 2;
			LOffsum = LOffsum - root->offset;
			ROffsum = ROffsum + root->offset;
			/*Update extreme descendents information*/
			if (RL.level > LL.level || root->left == NULL) {
				leftmost = RL;
				leftmost.offset = leftmost.offset + root->offset;
			}
			else {
				leftmost = LL;
				leftmost.offset = leftmost.offset - root->offset;
			}
			if (LR.level > RR.level || root->right == NULL) {
				rightmost = LR;
				rightmost.offset = rightmost.offset - root->offset;
			}
			else {
				rightmost = RR;
				rightmost.offset = rightmost.offset + root->offset;
			}
			// IF SUBTREES OF T WERE OF UNEVEN HEIGHTS, CHECK 
            // R TO SEE IF THREADING IS NECESSARY. AT MOST ONE 
            // THREAD NEEDS TO BE INSERTED.

            if (left != NULL && left != root->left) {
				(RR.addr)->thread = 1;
				(RR.addr)->offset = abs((RR.offset + root->offset) - LOffsum);
				if ((LOffsum - root->offset) <= RR.offset) {
					(RR.addr)->left = left;
				}
				else {
					(RR.addr)->right = left;
				}
			} else if (right != NULL && right != root->right) {
				(LL.addr)->thread = 1;
				(LL.addr)->offset = abs((LL.offset - root->offset) - ROffsum);
				if ((ROffsum + root->offset) >= LL.offset) {
					(LL.addr)->right = right;
				}
				else {
					(LL.addr)->left = right;
				}
			}
        }
    }
    return root;
}
/*!This procedures forms the pre-order traversal of the tree
converting the relative coordinates to absolute coordinates*/
struct Node* petrify(struct Node* root, int pos) {
	if (root != NULL) {
		root->x = pos;
		if (root->thread==true) {
			root->thread = false;
			root->left = NULL;
			root->right = NULL;
		}
		petrify(root->left, pos - root->offset);
		petrify(root->right, pos + root->offset);
	}
	return root;
}


int main(int argc, char *argv[]){

	struct Node* p = bst_init();
	struct Node* root = p;								//that stores the root

	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	extreme rightmost, leftmost;		
	auto start = high_resolution_clock::now();
    root = setup(root, 0, rightmost, leftmost);		//assign coordinates
    root = petrify(root, 200);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		<< duration.count() << " microseconds" << endl;

    draw_main(root, argc, argv);
    				//draw tree, function in draw.h
    return 0;
}
