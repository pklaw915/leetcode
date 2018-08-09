#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

#include "utils/listnode.h"

class Solution0025 {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (k <= 1)
			return head;
		std::pair<ListNode*, ListNode*> rev(nullptr, nullptr);	// reversed head and tail
		while (head)
		{
			int n;
			auto grp = reverseKMost(head, k, n);
			if (n < k)
			{
				head = grp.first;
				grp = reverseKMost(head, k, n);
			}
			if (rev.second == nullptr)
			{
				rev = grp;
			}
			else
			{
				rev.second->next = grp.first;
				rev.second = grp.second;
			}
		}
		return rev.first;
	}

	std::pair<ListNode*, ListNode*> reverseKMost(ListNode* &head, int k, int& n)
	{
		n = 0;
		std::pair<ListNode*, ListNode*> rev(nullptr, head);
		while (head && n < k)
		{
			++n;
			auto p = head;
			head = head->next;
			p->next = rev.first;
			rev.first = p;
		}

		return rev;
	}
};

void test0025_reverseKGroup()
{

}