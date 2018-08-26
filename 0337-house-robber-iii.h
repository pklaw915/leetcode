#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

#include "utils/structs.h"

class Solution0337 {
public:
	int rob(TreeNode* root) {
		auto sum = _rot(root);
		return max(sum.first, sum.second);
	}

	pair<int, int> _rot(TreeNode* root)
	{
		// first: skip root, second: take root
		pair<int, int> sum(0, 0);
		if (root)
		{
			auto s1 = _rot(root->left);
			auto s2 = _rot(root->right);
			sum.first = max(s1.first, s1.second) + max(s2.first, s2.second);
			sum.second = root->val + s1.first + s2.first;
	}
		return sum;
	}
};

void test0337_rob()
{
	int nn;
	Solution0337 sol;

	TreeNode* root = new TreeNode(3);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->right = new TreeNode(3);
	root->right->right = new TreeNode(1);
	nn = sol.rob(root);
	assert(nn == 7);

	root->val = 3;
	root->left->val = 4;
	root->right->val = 5;
	root->left->left = new TreeNode(1);
	root->left->right->val = 3;
	root->right->right->val = 1;
	nn = sol.rob(root);
	assert(nn == 9);
}