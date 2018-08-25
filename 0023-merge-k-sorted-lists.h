#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

#include "utils/structs.h"

class Solution0023 {
public:
	bool less(ListNode* l, ListNode* r) const
	{
		if (l == nullptr)
			return false;
		if (r == nullptr)
			return true;
		return l->val < r->val;
	}

	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.empty())
			return nullptr;

		auto fnCmp = [this, &lists](int i1, int i2)
		{
			ListNode* n1 = lists[i1];
			ListNode* n2 = lists[i2];
			return less(n1, n2);
		};

		vector<int> order;
		order.resize(lists.size());
		for (int ii = 0; ii < (int)order.size(); ++ii)
			order[ii] = ii;
		sort(order.begin(), order.end(), fnCmp);

		int& minimum = order[0];
		ListNode* head = lists[minimum];

		ListNode* p = head;
		while (p)
		{
			lists[minimum] = p->next;

			auto beg = order.begin() + 1;
			auto end = lower_bound(beg, order.end(), minimum, fnCmp);
			if (beg != end)
			{
				int backup = order[0];
				auto prv = order.begin();
				while (beg != end)
					*prv++ = *beg++;
				*prv = backup;
			}

			p->next = lists[minimum];
			p = lists[minimum];
		}

		return head;
	}
};


void test0023_mergeKLists()
{
	vector<ListNode*> vNodes;
	vNodes.resize(100);
	for (size_t i = 0; i < vNodes.size(); i++)
		vNodes[i] = new ListNode((int)i + 1);

	Solution0023 sol;
	ListNode* head;
	vector<ListNode*> lists;

	lists.resize(3, nullptr);
	lists[0] = nullptr;
	lists[1] = nullptr;
	lists[2] = nullptr;
	head = sol.mergeKLists(lists);
	assert(head == nullptr);

	lists.resize(3, nullptr);
	lists[0] = vNodes[0];	vNodes[0]->next = nullptr;
	lists[1] = nullptr;
	lists[2] = vNodes[1];	vNodes[1]->next = nullptr;
	head = sol.mergeKLists(lists);
	assert(head == vNodes[0] && head->next == vNodes[1] && head->next->next == nullptr);

	lists.resize(3, nullptr);
	lists[0] = nullptr;
	lists[1] = vNodes[0];	vNodes[0]->next = vNodes[1];	vNodes[1]->next = nullptr;
	lists[2] = nullptr;
	head = sol.mergeKLists(lists);
	assert(head == vNodes[0] && head->next == vNodes[1] && head->next->next == nullptr);

	lists.resize(3, nullptr);
	lists[0] = vNodes[0];	vNodes[0]->next = vNodes[1];	vNodes[1]->next = vNodes[2];	vNodes[2]->next = nullptr;
	lists[1] = vNodes[3];	vNodes[3]->next = vNodes[4];	vNodes[4]->next = vNodes[5];	vNodes[5]->next = nullptr;
	lists[2] = vNodes[6];	vNodes[6]->next = vNodes[7];	vNodes[7]->next = nullptr;
	vNodes[0]->val = 1;
	vNodes[1]->val = 4;
	vNodes[2]->val = 5;
	vNodes[3]->val = 1;
	vNodes[4]->val = 3;
	vNodes[5]->val = 4;
	vNodes[6]->val = 2;
	vNodes[7]->val = 6;
	head = sol.mergeKLists(lists);

	for (size_t i = 0; i < vNodes.size(); i++)
		delete vNodes[i];
}