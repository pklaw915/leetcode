#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

#include "utils/listnode.h"

class Solution0002 {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		bool bAdd = false;
		ListNode* p1 = l1, *p2 = l2;
		ListNode* t1 = nullptr;
		ListNode* t2 = nullptr;
		while (p1 && p2)
		{
			p1->val += p2->val + (bAdd ? 1 : 0);
			if (bAdd = (p1->val > 9))
				p1->val -= 10;
			t1 = p1; p1 = p1->next;
			t2 = p2; p2 = p2->next;
		}
		t1->next = nullptr;
		t2->next = nullptr;
		if (p1 || p2)
		{
			t1->next = p1 ? p1 : p2;
			p1 = t1->next;
			while (bAdd && p1)
			{
				p1->val += 1;
				if (bAdd = (p1->val > 9))
					p1->val -= 10;
				t1 = p1; p1 = p1->next;
			}
		}

		if (bAdd)
		{
			p1 = l2;
			l2 = l2->next;
			t1->next = p1;
			p1->next = nullptr;
			p1->val = 1;
		}

		return l1;
	}
};

ListNode* get_num_list(vector<ListNode*>& arr, unsigned int n)
{
	size_t index = 0;
	auto fnGetNode = [&arr, &index]()->ListNode*
	{
		if (index >= arr.size())
		{
			arr.resize(index + 5);
		}
		if (arr[index] == nullptr)
			arr[index] = new ListNode(0);

		return arr[index++];
	};
	ListNode* head = nullptr;
	ListNode* tail = nullptr;
	do
	{
		ListNode* p = fnGetNode();
		p->val = n % 10;

		if (head == nullptr)
		{
			head = tail = p;
		}
		else
		{
			tail->next = p;
			tail = p;
		}
		tail->next = nullptr;

		n /= 10;
	} while (n);

	return head;
}

unsigned int get_list_num(ListNode* p)
{
	unsigned int m = 1;
	unsigned int n = 0;
	while (p)
	{
		n += p->val * m;
		m *= 10;
		p = p->next;
	}
	return n;
}

void test0002_addTwoNumbers()
{
	Solution0002 sol;
	unsigned int n1, n2;
	vector<ListNode*> arr1, arr2;

	n1 = 12365;
	n2 = 53459;
	auto l1 = get_num_list(arr1, n1);
	auto l2 = get_num_list(arr2, n2);
	auto ss = sol.addTwoNumbers(l1, l2);
	assert(get_list_num(ss) == n1 + n2);

	for (size_t i = 0; i < arr1.size(); i++)
	{
		delete arr1[i];
	}
	for (size_t i = 0; i < arr2.size(); i++)
	{
		delete arr2[i];
	}
}