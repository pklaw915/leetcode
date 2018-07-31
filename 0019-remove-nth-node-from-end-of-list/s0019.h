#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

#include "../listnode.h"

class Solution0019 {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		if (head == nullptr || n < 1)
			return head;

		ListNode* p = head;
		while (n>0)
		{
			--n;
			if (p == nullptr)
				return head;
			p = p->next;
		}

		if (p == nullptr)
		{
			p = head->next;
			//	delete head;
			return p;
		}

		ListNode* r = head;
		p = p->next;		// to remove r->next if p is nullptr
		while (p)
		{
			p = p->next;
			r = r->next;
		}

		// remove r->next
		p = r->next;
		r->next = p->next;
		//	delete p;

		return head;
	}
};



ListNode* setupList0019(vector<ListNode*>& vNodes, int n)
{
	if (n == 0)
		return nullptr;

	for (int ii = 0; ii < n - 1; ++ii)
		vNodes[ii]->next = vNodes[ii + 1];
	vNodes[n - 1]->next = nullptr;

	return vNodes[0];
}

void verifyList(const vector<ListNode*>& vNodes, const ListNode* head, int n, int remove)
{
	assert(n >= 0 && n <= (int)vNodes.size());
	if (n == 0)
	{
		assert(head == nullptr);
		return;
	}

	if (n == 1)
	{
		if (remove == 1)
			assert(head == nullptr);
		else
			assert(head == vNodes[0] && vNodes[0]->next == nullptr);
		return;
	}

	if (remove > 0 && remove <= n)
	{
		remove = n - remove;		// actual index in vector
		if (remove == 0)			// 1st is removed
		{
			assert(head == vNodes[1]);
			vNodes[0]->next = vNodes[1];
		}
		else
		{
			assert(head == vNodes[0]);
			if (remove == n - 1)	// last is removed
			{
				assert(vNodes[remove - 1]->next == nullptr);
				vNodes[remove - 1]->next = vNodes[remove];
				vNodes[remove]->next = nullptr;
			}
			else
			{
				assert(vNodes[remove - 1]->next == vNodes[remove + 1]);
				vNodes[remove - 1]->next = vNodes[remove];
				vNodes[remove]->next = vNodes[remove + 1];
			}
		}
	}
	for (int i = 0; i < n - 1; i++)
	{
		assert(vNodes[i]->next == vNodes[i + 1]);
	}
	assert(vNodes[n - 1]->next == nullptr);
}

void test_removeNthFromEnd()
{
	vector<ListNode*> vNodes;
	vNodes.resize(100);
	for (size_t i = 0; i < vNodes.size(); i++)
		vNodes[i] = new ListNode((int)i + 1);

	int size;
	ListNode* head;
	Solution0019 sol;

	size = 0;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 1);
	verifyList(vNodes, head, size, 1);

	size = 3;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 2);
	verifyList(vNodes, head, size, 2);

	size = 2;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 1);
	verifyList(vNodes, head, size, 1);

	size = 2;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 2);
	verifyList(vNodes, head, size, 2);

	size = 1;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 1);
	verifyList(vNodes, head, size, 1);

	size = 1;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 0);
	verifyList(vNodes, head, size, 0);

	size = 1;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), -1);
	verifyList(vNodes, head, size, -1);

	size = 1;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 100);
	verifyList(vNodes, head, size, 100);

	size = 2;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 1);
	verifyList(vNodes, head, size, 1);

	size = 2;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 2);
	verifyList(vNodes, head, size, 2);

	size = 2;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 0);
	verifyList(vNodes, head, size, 0);

	size = 2;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), -1);
	verifyList(vNodes, head, size, -1);

	size = 2;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 100);
	verifyList(vNodes, head, size, 100);

	size = 100;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 1);
	verifyList(vNodes, head, size, 1);

	size = 100;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 50);
	verifyList(vNodes, head, size, 50);

	size = 100;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 100);
	verifyList(vNodes, head, size, 100);

	size = 100;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 0);
	verifyList(vNodes, head, size, 0);

	size = 100;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), -1);
	verifyList(vNodes, head, size, -1);

	size = 100;
	head = sol.removeNthFromEnd(setupList0019(vNodes, size), 101);
	verifyList(vNodes, head, size, 101);

	for (size_t i = 0; i < vNodes.size(); i++)
		delete vNodes[i];
}