#ifndef __LIST_NODE__H__
#define __LIST_NODE__H__

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

#endif // !__LIST_NODE__H__