#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#endif // __TREE_NODE_H__