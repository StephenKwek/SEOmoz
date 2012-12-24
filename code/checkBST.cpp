
#pragma once
#include <set>
#include <vector>
#include <assert.h>
#include <limits.h>

using namespace std;

template <typename T>
struct TreeNode
{
	T value; 
	TreeNode<int> *left; 
	TreeNode<int> *right; 
};


/* 
   IsBinarySearchTree checks that a given tree is a binary search tree by performing an inorder
   traversal and verifies that the values of the nodes visited are in increasing order.
   It also checks that there is no cycle by making sure that 
*/
const bool IsBinarySearchTree(const TreeNode<int> *cur, 
							  set<const TreeNode<int>*> &visited, 
							  int &largestValueSeenSoFar)
{
	if (!cur)
	{
		return true; 
	}

	if (visited.find(cur) != visited.end())
	{
		return false;
	}

	if (cur->left && !IsBinarySearchTree(cur->left, visited, largestValueSeenSoFar))
	{
		return false;
	}

	if (largestValueSeenSoFar > cur->value)
	{
		return false;
	}
	visited.insert(cur);
	largestValueSeenSoFar = cur->value;

	return (!cur->right || IsBinarySearchTree(cur->right, visited, largestValueSeenSoFar));
}


/*
   return true if this tree rooted at rootNode is a Binary Search Tree and false. 
   Throw an exception is the root is NULL. 
*/
inline const bool IsBinarySearchTree(const TreeNode<int> * rootNode)
{
	if (!rootNode)
	{
		throw "Root node is NULL!";
	}

	set<const TreeNode<int>*> visited;
	int max = INT_MIN;
	return IsBinarySearchTree(rootNode, visited, max);
}


void DeleteTree(TreeNode<int> *node)
{
	if (!node)
		return;

	if (node->left)
	{
		DeleteTree(node->left);
	}
	if (node->right)
	{
		DeleteTree(node->right);
	}
	delete node;
}


/*
  CreateTree takes a two dimensional array where each row is a 3-tuple
  represents a node <value, leftChildIndex, rightChildIndex> and construct 
  a binary tree.

  NOTE: it is meant for testing purposes and hence does not check that 
  the input array is valid. 
*/
TreeNode<int>* CreateTree(const int tree[][3], const int numNodes)
{
	// create a vector of 'empty' tree nodes.
	vector<TreeNode<int>*> nodes;
	for (int i = 0; i < numNodes; i++)
	{
		nodes.push_back(new (struct TreeNode<int>));
	}

	// Link up the nodes via left and right child pointer, and assign the value.
	for (int i = 0; i < numNodes; i++)
	{
		nodes[i]->value = tree[i][0];

		// assign left child pointer
		if (tree[i][1] != -1)
			nodes[i]->left = nodes[tree[i][1]];
		else
			nodes[i]->left = NULL;

		// assign right child pointer
		if (tree[i][2] != -1)
			nodes[i]->right = nodes[tree[i][2]];
		else
			nodes[i]->right = NULL;
	}

	// return the first node as the root. 
	return nodes[0];
}


int main()
{
	TreeNode<int>* root;

	// Case 1: Good tree with all possible number of chidlren 0, 1 (left or right) and 2 children
	int goodTree[9][3] = { 
		{50, 1, 2},
		{20, 3, 4},
		{80, 5, 6},
		{10, -1, -1},
		{30, -1, 7},
		{70, 8, -1},
		{90, -1, -1},
		{40, -1, -1},
		{60, -1, -1}
	};
		
	root = CreateTree(goodTree, 9);
	assert(IsBinarySearchTree(root));
	DeleteTree(root);

	// Case 2: Bad tree with left child (of root) being larger than parent
	int badTree1[3][3] = { {30, 1, 2}, {1000, -1, -1}, {40, -1, -1} }; 
	root = CreateTree(badTree1, 3);
	assert(!IsBinarySearchTree(root));
	DeleteTree(root);

	// Case 3: root is NULL, exception thrown.
	bool exceptionThrow = false; 
	try {
		IsBinarySearchTree(NULL);
	}
	catch (const char *e)
	{
		printf("Exception %s\n", e);
		exceptionThrow = true;
	}
	assert(exceptionThrow);

	// Case 4: Bad tree with right child (of root) being smaller than parent
	int badTree2[3][3] = { {30, 1, 2}, {20, -1, -1}, {4, -1, -1} }; 
	root = CreateTree(badTree2, 3);
	assert(!IsBinarySearchTree(root));
	DeleteTree(root);

	// Case 5: Bad tree with leftt child (of non-root node) being larger than parent
	int badTree3[5][3] = { {30, 1, 2}, {20, 3, -1}, {40, -1, 4}, {1000, -1, -1}, {50, -1, -1} }; 
	root = CreateTree(badTree3, 5);
	assert(!IsBinarySearchTree(root));
	DeleteTree(root);

	// Case 6: Bad tree with right child (of non-root node) being smaller than parent
	int badTree4[5][3] = { {30, 1, 2}, {20, 3, -1}, {40, -1, 4}, {1000, -1, -1}, {50, -1, -1} }; 
	root = CreateTree(badTree4, 5);
	assert(!IsBinarySearchTree(root));
	DeleteTree(root);

	// Case 7: Bad tree with left grandchild (of non-root node) being greater than its grandparent
	int badTree5[5][3] = { {30, 1, 2}, {20, -1, 3}, {40, -1, 4}, {10, -1, -1}, {5, -1, -1} }; 
	root = CreateTree(badTree4, 5);
	assert(!IsBinarySearchTree(root));
	DeleteTree(root);

	// Case 8: Bad tree with right grandchild (of non-root node) being smaller than its grandparent
	int badTree6[5][3] = { {30, 1, 2}, {20, 3, -1}, {40, 4, -1}, {10, -1, -1}, {5, -1, -1} }; 
	root = CreateTree(badTree4, 5);
	assert(!IsBinarySearchTree(root));
	DeleteTree(root);

	// Case 9: Bad tree with directed cycle, can result in infinite loop
	int badTree7[5][3] = { {30, 1, 2}, {20, -1, 3}, {40, -1, 4}, {10, -1, -1}, {50, 0, -1} }; 
	root = CreateTree(badTree4, 5);
	assert(!IsBinarySearchTree(root));
	DeleteTree(root);

	// Case 10: Bad tree with undirected cycle.
	int badTree8[5][3] = { {30, 1, 2}, {20, -1, 3}, {40, -1, 4}, {10, -1, -1}, {50, 1, -1} }; 
	root = CreateTree(badTree4, 5);
	assert(!IsBinarySearchTree(root));
	DeleteTree(root);

	printf("All tests passed\n");
}
