#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class MedianFinder {
	struct heap
	{
		heap(bool bLess)
			: _bLess(bLess)
		{

		}

		void push(int num)
		{
			vals.push_back(num);
			push_heap(vals.begin(), vals.end(), [this](int n1, int n2) {
				return _bLess ? (n1 < n2) : (n1 > n2);
			});
		}

		int swap(int num)
		{
			if (vals.empty())
				return num;
			if (_bLess ? num < vals.front() : num > vals.front())
			{
				int nn = vals.front();
				pop_heap(vals.begin(), vals.end(), [this](int n1, int n2) {
					return _bLess ? (n1 < n2) : (n1 > n2);
				});
				vals.back() = num;
				push_heap(vals.begin(), vals.end(), [this](int n1, int n2) {
					return _bLess ? (n1 < n2) : (n1 > n2);
				});
				return nn;
			}

			return num;
		}

		bool		_bLess;
		vector<int>	vals;
	};
	heap			minHeap, maxHeap;
public:
	/** initialize your data structure here. */
	MedianFinder()
		: minHeap(true), maxHeap(false)
	{

	}

	void addNum(int num) {
		if (minHeap.vals.size() < maxHeap.vals.size())
		{
			num = maxHeap.swap(num);
			minHeap.push(num);
		}
		else
		{
			num = minHeap.swap(num);
			maxHeap.push(num);
		}
	}

	double findMedian() {
		if (minHeap.vals.size() > maxHeap.vals.size())
			return minHeap.vals.front();
		if (minHeap.vals.size() < maxHeap.vals.size())
			return maxHeap.vals.front();
		if (minHeap.vals.size() == 0)
			return 0;
		return (minHeap.vals.front() + maxHeap.vals.front()) * 0.5;
	}
};

/**
* Your MedianFinder object will be instantiated and called as such:
* MedianFinder obj = new MedianFinder();
* obj.addNum(num);
* double param_2 = obj.findMedian();
*/


void test0295_findMedian()
{
	MedianFinder mf;

	const int vals[] = { 1 ,2 ,3 ,5 ,6, 1, 2, 5, 10, 20, 30, 40 };
	for (size_t i = 0; i < _countof(vals); i++)
	{
		mf.addNum(vals[i]);
		double md = mf.findMedian();
		printf("%f\n", md);
	}
}