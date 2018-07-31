// main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../0004-median-of-two-sorted-arrays/s0004.h"
#include "../0008-string-to-integer-atoi/s0008.h"
#include "../0010-regular-expression-matching/s0010.h"
#include "../0019-remove-nth-node-from-end-of-list/s0019.h"
#include "../0023-merge-k-sorted-lists/s0023.h"
#include "../0041-first-missing-positive/s0041.h"
#include "../0136-single-number/s0136.h"
#include "../0871-minimum-number-of-refueling-stops/s0871.h"


int main()
{
	test_findMedianSortedArrays();
	test_atoi();
	test_isMatch();
	test_removeNthFromEnd();
	test_mergeKLists();
	test_firstMissingPositive();
	test_singleNumber();
	test_minRefuelStops();
    return 0;
}

