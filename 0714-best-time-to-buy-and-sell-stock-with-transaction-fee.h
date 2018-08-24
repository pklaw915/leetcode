#include <algorithm>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0714 {
public:
	int maxProfit(vector<int>& prices, int fee) {
		int profit = 0, cost = INT_MAX;
		for (auto iter = prices.begin(); iter != prices.end(); iter++)
		{
			cost = min(cost, fee + *iter - profit);
			profit = max(profit, *iter - cost);
		}
		return profit;
	}

	int maxProfit_wrong(vector<int>& prices, int fee) {
		if (prices.size() < 2)
			return 0;
		if (fee <= 0)
			return no_fee(prices);

		vector<int> st;
		st.reserve(prices.size());
		int profit = 0, sub = 0;
		int n = 1;
		while (n < prices.size())
		{
			int delta = 0;
			while (n < prices.size())
			{
				int d = prices[n] - prices[n - 1];
				if (d * delta < 0)
					break;
				delta += d;
				n++;
			}

			if (delta <= -fee)
			{
				sub = 0;
				profit += combine(st, fee);
				continue;
			}
			if (delta < 0)
			{
				if (st.empty())
					continue;
				if (st.size() > 1 && (*(st.rbegin() + 1) + st.back() + delta) <= -fee)
				{
					sub = 0;
					profit += combine(st, fee);
					continue;
				}
			}

			if (delta > 0 || sub + delta > 0)
			{
				sub += delta;
				st.push_back(delta);
			}
			else
			{
				sub = 0;
				profit += combine(st, fee);
			}
		}

		return profit + combine(st, fee);
	}

	int combine(vector<int>& st, int fee) {
		if (st.empty())
			return 0;
		if (st.back() < 0)
			st.pop_back();
		int sum = 0;
		while (st.size())
		{
			sum += st.back();
			if (sum <= 0)
			{
				sum -= st.back();
				return max(sum - fee, 0) + combine(st, fee);
			}
			st.pop_back();
		}

		return max(sum - fee, 0);
	}

	int no_fee(const vector<int>& prices) {
		int sum = 0;
		for (size_t i = 1; i < prices.size(); i++)
		{
			const int delta = prices[i] - prices[i - 1];
			if (delta > 0)
				sum += delta;
		}
		return sum;
	}
};


void test0714_maxProfit()
{
	int fee, nn;
	vector<int> prices;
	Solution0714 sol;

	fee = 2;
	prices.assign({1, 3, 2, 8, 4, 9});
	nn = sol.maxProfit(prices, fee);
	assert(nn == 8);

	fee = 655;
	prices.assign({ 1036, 2413, 2776, 825, 2640, 31, 1560, 2917, 4282, 783, 3146, 2600, 1939, 694, 4284, 3881, 554, 167, 372, 4620, 3037, 1175, 1075, 3845, 4981, 4495, 3406, 4228, 2807, 4774, 4526, 3914, 2633, 3762, 1570, 2334, 616, 1648, 1914, 2900, 349, 2428, 4013, 1964, 4020, 1882, 629, 240, 2595, 2902, 3419, 292, 224, 4437, 4918, 632, 3701, 3840, 3996, 2129, 3345, 3979, 1954, 781, 1576, 1084, 3250, 4517, 3106, 2133, 309, 4520, 2225, 4366, 4628, 1303, 4373, 1266, 3181, 558, 3855, 3447, 4335, 2115, 4603, 661, 1715, 3972, 2846, 342, 686, 787, 273, 2575, 100, 2860, 3587, 4236, 3862, 2238, 3471, 3123, 431, 4489, 1551, 596, 4037, 4986, 594, 2386, 326, 628, 1363, 2377, 4986, 3780, 3853, 2670, 2852, 3519, 2998, 4083, 3392, 2394, 1083, 3958, 4082, 1506, 2322, 2715, 4901, 2555, 4097, 3748, 4717, 3901, 3329, 4616, 3334, 2603, 3705, 631, 3541, 555, 508, 464, 4495, 4463, 3616, 31, 2177, 3307, 1011, 2759, 751, 1537, 1000, 292, 3921, 1442, 2726, 4677, 792, 82, 2580, 609, 4758, 3190, 1958, 913, 955, 1259, 1634, 4729, 2672, 1761, 1467, 2347, 4295, 2049, 4708, 1452, 3411, 1428, 4078, 2627, 3785, 2432, 2916, 492, 1108, 1691, 972, 3823, 4086, 2115, 1925, 1454, 291, 3266, 300, 2539, 2681, 2084, 4633, 1084, 1061, 1043, 1304, 2205, 410, 4332, 2567, 703, 529, 4273, 3684, 308, 3164, 4876, 3108, 4993, 4555, 1237, 4753, 549, 2795, 3426, 819, 2897, 825, 2514, 3419, 1854, 3209, 3766, 2794, 4117, 4668, 2162, 1571, 2446, 1480, 974, 1090, 3903, 4655, 4452, 1451, 2953, 1241, 842, 1750, 3847, 3053, 4395, 4338, 1493, 1660, 1569, 3418, 3029, 4416, 2056, 2283, 3392, 2032, 4354, 803, 4959, 3630, 2080, 1553, 873, 4050, 1986, 2328, 55, 4602, 1430, 4238, 4326, 3382, 4845, 4968, 1903, 423, 4717, 2427, 4618, 2644, 4541, 380, 3404, 4880, 2577, 1640, 189, 2692, 3788, 818, 4091, 4730, 611, 1776, 3594, 4746, 580, 2083, 4183, 3355, 3063, 658, 4532, 3318, 3902, 556, 2249, 4653, 2118, 1529, 4793, 4935, 4259, 3542, 1705, 2839, 1436, 3918, 564, 3277, 2988, 2460, 3213, 4445, 4238, 1954, 2213, 1748, 939, 1149, 1408, 2408, 1781, 1618, 1457, 2123, 3366, 826, 2094, 16, 1161, 3337, 1864, 433, 1303, 4800, 4667, 4769, 1026, 3440, 1072, 4725, 6, 1263, 4184, 2728, 1315, 2091, 3032, 2071, 2672, 4557, 1916, 638, 2133, 2687, 2408, 1677, 344, 697, 1699, 8, 480, 655, 2656, 4983, 455, 1611, 1726, 692, 392, 1921, 2555, 3549, 3740, 3840, 3062, 3420, 2428, 1169, 4570, 389, 3509, 2169, 3290, 1680, 1733, 1765, 2518, 3260, 3644, 765, 4521, 269, 2501, 4014, 1743, 239, 4908, 1656, 4433, 3647, 2612, 4872, 387, 3091, 4011, 564, 4421, 810, 3623, 3451, 4108, 1428, 475, 3755, 4484, 3527, 3062, 4706, 3424, 2678, 2411, 4446, 2556, 4305, 1305, 646, 1458, 4471, 1689, 4556, 3851, 1245, 1197, 3785, 1175, 2904, 302, 2422, 4302, 2148, 2338, 4288, 375, 2824, 1623, 3717, 1142, 4254, 192, 783, 1963, 2225, 1209, 1746, 3072, 2737, 4640, 4919, 3614, 804, 4029, 1751, 2360, 3789, 4445, 2283, 2769, 2833, 4452, 2978, 2809, 4532, 4365, 2124, 3541, 2658, 2902, 4688, 3980, 1543, 4041, 1420, 1452, 1284, 66, 19, 947, 932, 3244, 3374, 1910, 2561, 3466, 4104, 1667, 589, 3048, 730, 1770, 1241, 2270, 4016, 2835, 604, 4771, 514, 3854, 3427, 1875, 2038, 3067, 3216, 4732, 3735, 4440, 2855, 4958, 4569, 1685, 3539, 4589, 3512, 3143, 898, 3004, 3072, 2573, 3163, 2522, 3927, 330, 3874, 363, 1900, 1629, 1156, 4259, 2747, 3445, 4513, 2867, 52, 3870, 1761, 619, 3308, 4380, 1101, 2592, 4852, 4140, 174, 3997, 4617, 3500, 3028, 907, 2355, 759, 374, 2429, 412, 2132, 3973, 3583, 3028, 2070, 2235, 2659, 1053, 2558, 753, 1221, 1185, 2225, 1593, 3554, 3703, 332, 2843, 3349, 3871, 4389, 6, 2768, 4382, 902, 417, 191, 2107, 2838, 4958, 3905, 4966, 3937, 1105, 4150, 2682, 3396, 818, 2297, 2077, 2032, 3340, 2478, 127, 4379, 954, 2593, 3454, 1230, 2308, 3694, 2179, 4134, 653, 3808, 4043, 2069, 660, 4515, 4189, 4876, 1784, 4166, 342, 1766, 3305, 1980, 1909, 4115, 4115, 1461, 2061, 838, 3112, 122, 656, 4856, 4822, 3468, 2111, 2700, 4124, 4663, 2948, 3029, 4182, 3847, 4760, 1323, 1505, 308, 128, 874, 583, 2671, 1315, 747, 2682, 2841, 67, 2712, 2703, 4471, 2952, 3081, 464, 655, 57, 1460, 1395, 682, 2447, 2590, 4624, 1578, 64, 4060, 2975, 1236, 831, 3313, 1432, 2589, 3777, 1868, 1720, 45, 3311, 4532, 2672, 454, 752, 4839, 4717, 748, 4323, 2999, 3491, 631, 1407, 1453, 4611, 4263, 3366, 584, 2014, 2396, 1902, 4569, 3002, 1938, 3998, 4093, 1899, 3071, 2815, 1974, 302, 1641, 2836, 565, 264, 1332, 3319, 3689, 2181, 3873, 4883, 3849, 1991, 4633, 4556, 3866, 142, 2903, 3181, 740, 3311, 2071, 280, 714, 2440, 3950, 290, 3580, 738, 1604, 3631, 1989, 1299, 836, 1913, 224, 1066, 1741, 1551, 1735, 4601, 2024, 4570, 4192, 1723, 3949, 3696, 1419, 1760, 697, 4764, 3405, 4443, 199, 717, 4568, 3252, 2016, 2151, 1741, 2613, 2736, 4053, 814, 4282, 3392, 615, 1998, 3294, 3663, 559, 4278, 4626, 55, 1418, 2056, 3191, 3181, 1732, 1887, 2517, 3180, 2154, 2166, 3096, 3930, 2721, 4332, 427, 4332, 4237, 3928, 2262, 4657, 2202, 922, 3711, 1921, 4728, 2236, 2441, 622, 233, 293, 1466, 1891, 1222, 3693, 3261, 2605, 3486, 102, 3612, 1897, 2698, 3524, 3567, 613, 3834, 1583, 1482, 4734, 2339, 752, 1428, 4121, 3267, 3518, 4652, 3119, 1818, 4596, 3181, 3159, 4069, 3375, 3762, 1386, 3054, 3052, 67, 2246, 1493, 2738, 2835, 4906, 303, 1107, 3111, 1525, 1739, 437, 2941, 545, 1458, 993, 1871, 640, 4047, 2017, 4971, 4917, 701, 4811, 4335, 3221, 4187, 4414, 756, 3069, 3052, 812, 3135, 928, 1264, 3356, 4518, 2136, 2691, 2638, 3156, 4909, 2944, 3920, 4609, 1856, 654, 4643, 2932, 309, 3613, 4479, 4173, 1848, 165, 1171, 592, 3233, 3151, 4009, 3952, 2624, 38, 2616, 2056, 841, 1764, 4667, 1526, 125, 3963, 933, 3951, 2151, 2110, 4666, 1000, 1985, 3868, 2735, 635, 277, 1129, 572, 2136, 980, 2731, 556, 3012, 2900, 2180, 1912, 2799, 1771, 4441, 2666, 3958, 4381, 3677, 4218, 1276, 3512, 4868, 4579, 2307, 3952, 3544, 651, 1300, 218, 489, 2837, 3737, 509, 3421, 879, 4353, 4695 });
	nn = sol.maxProfit(prices, fee);
	assert(nn == 595352);

	fee = 4;
	prices.assign({ 100, 107, 104, 105, 102, 109 });
	nn = sol.maxProfit(prices, fee);
	assert(nn == 6);

	fee = 4490;
	prices.assign({ 1619, 1810, 2047, 1362, 2387, 648, 2858, 3008, 1212, 2489, 639, 2589, 3107, 1927, 499, 411, 3830, 3077, 4165, 4133, 2359, 2749, 713, 1156, 4856, 3484, 2602, 231, 4315, 3633, 2829, 4704, 24, 2659, 4247, 495, 1532, 1943, 4664, 1194, 1446, 4232, 864, 4545, 1111, 3875, 3250, 2322, 3899, 2301, 1736, 1308, 479, 1574, 1475, 3335, 4975, 1344, 2870, 3354, 107, 4488, 327, 3685, 181, 4406, 2220, 2369, 2624, 2522, 2718, 453, 3672, 2931, 20, 1247, 2533, 1139, 1998, 2256, 273, 4176, 124, 709, 1855, 2611, 1631, 2196, 3929, 1385, 4143, 2739, 3597, 509, 1243, 3559, 3705, 3955, 1946, 3592, 713, 2363, 3869, 3253, 271, 2928, 1621, 3231, 2007, 1450, 2791, 3373, 1594, 1521, 3850, 1842, 2496, 2037, 1627, 3694, 1605, 2517, 1729, 2543, 4071, 4032, 80, 769, 455, 3525, 3921, 2584, 397, 4103, 590, 1711, 1457, 1801, 1803, 3716, 4885, 4936, 4658, 3189, 2722, 3724, 3702, 266, 2637, 1331, 2285, 2721, 2201, 2587, 2038, 4986, 3109, 4284, 785, 2538, 3463, 20, 3643, 1735, 3431, 4956, 4513, 1409, 2080, 2456, 4231, 2354, 639, 4288, 1109, 524, 3668, 3867, 3658, 2868, 711, 772, 3660, 2121, 4847, 3894, 3792, 2309, 976, 2408, 3699, 2963, 1597, 2703, 4594, 1360, 4624, 289, 3389, 89, 2089, 4964, 934, 322, 4459, 3917, 2770, 2314, 2671, 3067, 3027, 2023, 2878, 4104, 4213, 2694, 2922, 3389, 4808, 3320, 2835, 1813, 493, 854, 1511, 3467, 3836, 3096, 634, 1280, 2027, 3997, 1742, 1030, 1304, 2445, 960, 343, 331, 282, 2104, 3241, 529, 2381, 1642, 1991, 3710, 1179, 554, 2880, 3532, 2284, 3617, 4407, 3998, 1100, 2400, 3804, 4922, 1328, 3718, 1478, 4709, 3739, 751, 3512, 131, 3701, 1636, 4958, 815, 2406, 2737, 743, 951, 4177, 4101, 1441, 1525, 3168, 4950, 3737, 758, 4975, 546, 3857, 4173, 2355, 2543, 490, 4360, 364, 4012, 3406, 2272, 3538, 3617, 261, 3456, 2652, 834, 4250, 1896, 2433, 3769, 4690, 3568, 4779, 4674, 669, 4589, 4186, 2655, 2726, 2264, 1005, 4096, 1295, 2029, 1704, 2606, 3178, 980, 3718, 791, 4201, 761, 177, 3264, 279, 1601, 4062, 4543, 1683, 1666, 635, 4560, 2057, 263, 4866, 2902, 1331, 2396, 3550, 2037, 555, 4971, 2146, 3169, 3370, 1148, 2144, 1792, 1938, 4085, 2585, 3947, 2479, 4345, 2375, 3232, 1538, 3031, 1101, 3842, 2507, 392, 188, 4971, 912, 3799, 2841, 777, 4485, 4889, 995, 263, 4554, 3326, 1829, 2829, 4081, 3976, 1885, 3697, 4479, 2667, 1764, 1330, 3113, 1388, 3085, 4915, 2451, 3356, 53, 4808, 175, 4455, 1379, 4621, 1495, 3966, 4966, 1495, 1998, 3005, 2893, 1250, 3946, 1650, 2707, 3474, 4286, 1810, 1866, 946, 1400, 4089, 459, 328, 4248, 2828, 3781, 4646, 3754, 3488, 4149, 275, 2484, 4815, 3826, 3076, 4956, 1626, 2570, 3337, 1721, 4352, 2148, 4852, 2146, 1844, 3995, 2523, 2556, 3474, 4648, 2020, 4473, 3068, 4256, 4086, 2876, 1996, 4146, 2171, 180, 4186, 3256, 1315, 4592, 351, 4095, 457, 4514, 4175, 1830, 4724, 3271, 3777, 3985, 3458, 2943, 1583, 3210, 2258, 989, 3303, 2730, 4898, 4437, 1295, 3447, 2718, 32, 2356, 134, 205, 1878, 776, 174, 1333, 576, 4299, 2043, 429, 612, 3471, 2546, 1067, 4107, 3331, 1508, 3851, 3834, 1396, 1874, 4968, 435, 1947, 4131, 4923, 3354, 460, 689, 2767, 1184, 3625, 2622, 3567, 3928, 2664, 2835, 4363, 4733, 2556, 1372, 4371, 2049, 1820, 4722, 2496, 3854, 3582, 3338, 2001, 2639, 1828, 1934, 2609, 363, 4187, 485, 2798, 44, 145, 4871, 3529, 1683, 341, 3607, 2098, 4844, 4518, 4431, 889, 1910, 4440, 2297, 2963, 1084, 3204, 4372, 3959, 3516, 2242, 3540, 2430, 125, 3096, 4928, 1807, 4331, 37, 2867, 2952, 284, 2658, 2817, 2248, 1616, 2492, 4954, 3330, 1153, 2273, 190, 2900, 4129, 1906, 4933, 4008, 4093, 4373, 15, 789, 4670, 3388, 782, 2243, 611, 1115, 3798, 2281, 1721, 173, 298, 3789, 1496, 872, 698, 1355, 1980, 2538, 3366, 1685, 76, 3190, 133, 2853, 2426, 3077, 1993, 4138, 4915, 845, 2192, 612, 2234, 4751, 1023, 4255, 1513, 2753, 1002, 3796, 415, 2374, 1340, 1595, 1294, 2122, 1416, 4147, 2247, 2557, 4063, 975, 2318, 1743, 3298, 4753, 910, 2059, 948, 2249, 842, 4927, 3963, 1894, 2010, 789, 2499, 3368, 1143, 241, 2118, 2938, 662, 839, 2206, 4683, 1190, 588, 3072, 1284, 2790, 4041, 1194, 884, 1364, 2635, 3285, 313, 2143, 3366, 1230, 4801, 900, 4828, 3274, 2912, 4541, 1606, 3924, 3238, 1262, 491, 2797, 4883, 53, 3110, 4985, 4104, 4228, 3697, 1730, 2191, 3819, 1786, 2351, 4080, 589, 2504, 4889, 2311, 828, 3367, 649, 2519, 3243, 3721, 1954, 4975, 3294, 4780, 4086, 1290, 338, 1552, 586, 4546, 76, 3932, 1314, 2106, 2344, 1266, 4283, 1598, 2090, 4697, 2465, 3200, 2503, 62, 2297, 57, 3794, 1671, 3113, 1670, 4157, 1189, 2117, 3074, 3669, 2603, 3001, 3289, 3895, 4523, 4684, 3162, 3151, 2127, 1004, 2784, 168, 3925, 2261, 912, 1450, 3889, 4345, 1817, 2428, 2918, 3755, 1892, 2083, 4540, 2461, 4837, 2807, 2747, 3970, 180, 1687, 2737, 4131, 2372, 1502, 3753, 160, 3271, 4444, 4239, 4433, 3673, 670, 2781, 1941, 1347, 1928, 1544, 2040, 1619, 393, 2567, 3461, 4298, 2575, 4417, 4247, 2143, 431, 3302, 982, 2478, 3284, 3431, 4114, 2377, 806, 2925, 3026, 1269, 4991, 3399, 2823, 2148, 1887, 2084, 2967, 523, 1835, 3237, 1282, 2152, 386, 1039, 2363, 2692, 973, 251, 2970, 2503, 1227, 3739, 1803, 2839, 482, 722, 2623, 1210, 820, 3310, 3789, 1235, 2653, 28, 3556, 2739, 4171, 1943, 96, 4325, 3050, 4072, 2653, 1862, 4194, 4042, 4147, 4655, 491, 2527, 440, 3142, 1509, 770, 270, 1069, 4251, 3720, 3396, 3558, 4513, 131, 1050, 1010, 2516, 2776, 4222, 1935, 4114, 2675, 986, 2710, 320, 4222, 588, 3124, 2856, 1074, 4791, 3275, 1836, 2443, 3167, 2408, 2628, 2661, 641, 4018, 2374, 4538, 1870, 3316, 3610, 876, 3271, 1972, 1184, 1112, 3347, 4383, 568, 2945, 1051, 4175, 2989, 2084, 390, 2536, 603, 61, 996, 340, 1541, 2811, 91, 4350, 4802, 4019, 1146, 538, 691, 1964, 4854, 2146, 2368, 4669, 2482, 3849, 1356, 2233, 3580, 4541, 2602, 570, 680, 4174, 2272, 3573, 2643, 3361, 2417, 3399, 3910, 1745, 4132, 102, 4027, 9, 2166, 929, 3373, 1250, 2881, 4661, 1286, 163, 2303, 950, 1846, 3361, 3774, 2073, 1983, 2660, 4506, 3935, 2771, 3489, 408, 3537, 4606 });
	nn = sol.maxProfit(prices, fee);
	assert(nn == 8703);

	fee = 1231;
	prices.assign({ 4680, 4209, 710, 364, 1213, 4092, 931, 436, 4408, 3929, 978, 2355, 3867, 1060, 109, 904, 1675, 1762, 1331, 3883, 2179, 3326, 1083, 4292, 295, 905, 806, 25, 3060, 3701, 2282, 1849, 4671, 3260, 1461, 3755, 1382, 696, 326, 21, 2355, 3412, 860, 451, 4317, 3351, 231, 3458, 603, 2390, 167, 405, 4152, 1640, 2974, 41, 2305, 1682, 1090, 2158, 4583, 318, 1583, 918, 3346, 4420, 1334, 1966, 4727, 4783, 1694, 3746, 804, 3230, 1831, 2261, 2436, 1436, 3216, 2112, 1170, 3671, 179, 823, 2221, 1622, 4976, 2343, 4098, 1418, 4220, 4135, 2799, 4064, 4064, 2325, 384, 1306, 4305, 4977, 4461, 962, 3075, 4277, 3295, 440, 4645, 1573, 377, 2430, 3095, 2688, 1933, 2948, 989, 3453, 1751, 4132, 4256, 3326, 3952, 4163, 4947, 852, 4415, 4147, 24, 4337, 2973, 2802, 4255, 3095, 1066, 2080, 4948, 1866, 2268, 2680, 4876, 4937, 627, 561, 4412, 869, 1070, 349, 1458, 4511, 1727, 453, 3319, 1566, 98, 2731, 263, 4999, 677, 571, 1698, 3027, 2811, 3364, 2899, 1265, 2070, 2281, 589, 3245, 1099, 53, 2947, 1064, 256, 517, 1919, 2683, 3598, 518, 2510, 2843, 4859, 4569, 85, 2281, 4977, 3098, 4781, 966, 4313, 1555, 3833, 3863, 267, 3149, 2985, 3611, 3849, 1566, 4002, 2202, 3114, 4804, 2739, 1459, 3776, 1293, 3784, 2197, 4175, 3368, 3467, 1131, 3382, 2305, 480, 3804, 2769, 1816, 2301, 3322, 1738, 3682, 3438, 3441, 3704, 4637, 2830, 4536, 3066, 2827, 2986, 4677, 4759, 1238, 4609, 983, 4321, 3778, 909, 3671, 55, 2679, 3928, 4336, 2295, 4498, 2326, 2791, 864, 3775, 1809, 365, 3701, 1080, 4215, 3902, 985, 894, 313, 940, 2754, 1667, 4507, 487, 3372, 2424, 3564, 3992, 1670, 235, 1246, 4037, 4653, 345, 4128, 377, 1933, 4758, 683, 1727, 3250, 4679, 1188, 4096, 764, 1309, 977, 1139, 841, 4482, 2100, 2501, 796, 4380, 4093, 1071, 2935, 2909, 1398, 3746, 3211, 1297, 3576, 3605, 3957, 3772, 1765, 3707, 446, 1531, 2937, 2910, 2099, 3532, 3053, 3693, 4035, 4095, 4987, 581, 3940, 4570, 661, 2904, 462, 2973, 2145, 3975, 4961, 1486, 4117, 1696, 2767, 4209, 373, 691, 3073, 4786, 3798, 4797, 391, 1032, 1393, 2601, 2402, 1489, 1128, 3359, 2620, 477, 3921, 2406, 4960, 1052, 3207, 4155, 2855, 100, 1920, 596, 3157, 4063, 2780, 2831, 4802, 4628, 1330, 557, 2461, 3265, 3623, 4372, 3743, 1693, 1533, 3193, 55, 4085, 2873, 1570, 1272, 90, 2251, 2542, 1911, 1263, 2554, 1608, 4295, 3034, 3639, 26, 726, 830, 1927, 1676, 2525, 3302, 1034, 4616, 4539, 1882, 2330, 705, 2632, 4354, 2260, 4092, 828, 2213, 4302, 611, 2527, 2979, 1081, 4979, 3468, 1324, 4148, 864, 3944, 1679, 4415, 1913, 4915, 4694, 4049, 514, 1401, 3144, 1754, 4012, 1050, 2469, 959, 1986, 776, 889, 3349, 1820, 3712, 4678, 1330, 1112, 2589, 3303, 1715, 3247, 784, 4517, 4925, 1916, 2296, 1205, 2242, 881, 3575, 3406, 2772, 2223, 3521, 3855, 4779, 953, 1526, 701, 3939, 945, 571, 3842, 3311, 4584, 2065, 3423, 1656, 3766, 1948, 835, 573, 4438, 568, 1184, 4983, 3725, 4280, 3659, 2356, 2275, 3896, 3191, 1517, 2092, 4670, 4408, 4892, 4795, 1993, 1825, 2619, 4927, 643, 2547, 1419, 2590, 4137, 2188, 4930, 919, 64, 2436, 551, 3004, 4350, 1018, 4805, 1957, 4859, 243, 2144, 2160, 1962, 4838, 1048, 151, 2456, 4154, 1949, 3148, 3444, 2736, 174, 1163, 3202, 1330, 3591, 1021, 2896, 1872, 932, 3063, 999, 4546, 4571, 1635, 3046, 2905, 67, 4188, 1035, 968, 3817, 1905, 314, 2662, 3087, 3544, 1607, 2800, 677, 4858, 4925, 4322, 113, 4272, 1910, 4885, 2672, 2158, 24, 3464, 3507, 2512, 94, 2674, 4287, 287, 341, 638, 3434, 987, 329, 2128, 2141, 1260, 4905, 2325, 3009, 2852, 2048, 3825, 2685, 1353, 2505, 3743, 3061, 2131, 4045, 4415, 4348, 1540, 3998, 1240, 2619, 3132, 3620, 1007, 2873, 2781, 1192, 2296, 1048, 3084, 4316, 4358, 3155, 4739, 344, 1484, 1953, 1181, 3699, 2571, 3082, 2223, 4929, 1890, 87, 642, 3248, 3427, 164, 1657, 3298, 3540, 4062, 2571, 1434, 3124, 1682, 222, 2569, 915, 3048, 1585, 4080, 3092, 452, 1232, 874, 3070, 2479, 3900, 611, 1044, 3721, 2158, 80, 1365, 4001, 3683, 4375, 3493, 4373, 1304, 62, 2555, 199, 2682, 850, 745, 3366, 1289, 2134, 3948, 603, 1711, 4076, 4042, 501, 3990, 4698, 1752, 1617, 3919, 2691, 212, 2774, 316, 3581, 1795, 3909, 912, 4423, 2672, 724, 1843, 1967, 3451, 1293, 130, 1015, 4818, 3395, 853, 4135, 1806, 2144, 1507, 3158, 4639, 3511, 755, 1458, 1364, 4276, 415, 761, 1083, 3963, 552, 3422, 3293, 3610, 3733, 3440, 1939, 17, 1220, 216, 550, 549, 3417, 3179, 2242, 2549, 1283, 2319, 4012, 2806, 1335, 2327, 22, 798, 2470, 4174, 1075, 4242, 3025, 1570, 4101, 218, 2104, 2404, 3381, 4025, 3326, 3499, 2852, 4942, 2988, 2890, 4544, 2562, 2160, 1282, 4907, 2583, 1111, 1193, 3610, 3336, 3491, 2536, 3258, 1468, 2380, 2589, 4494, 1763, 4817, 2594, 2662, 3521, 4759, 1132, 1221, 343, 4467, 2976, 4756, 3684, 2007, 2616, 2102, 4941, 238, 2709, 199, 284, 3969, 3488, 1269, 3550, 3505, 4105, 303, 1729, 2591, 2847, 1954, 3247, 548, 3245, 3945, 1867, 4976, 4520, 3692, 4790, 3027, 2356, 2633, 3143, 4671, 1922, 4002, 2934, 2564, 3380, 954, 1078, 2147, 393, 4793, 1260, 4548, 2871, 3502, 4842, 1283, 4345, 1498, 3297, 4340, 1644, 2848, 2208, 2249, 4461, 4338, 581, 1712, 4588, 4965, 4841, 3408, 3299, 3530, 4645, 2407, 1851, 3857, 755, 3892, 962, 710, 4712, 4800, 4780, 4008, 1460, 2257, 3898, 368, 1435, 2016, 2189, 4483, 2798, 2561, 2106, 1678, 3516, 3580, 1108, 3576, 2363, 2881, 4927, 3669, 2878, 3126, 3554, 1176, 377, 389, 597, 2719, 334, 4697, 2973, 3555, 2730, 3857, 2530, 4595, 4890, 4133, 3381, 4852, 3270, 4189, 1031, 982, 3487, 2814, 2534, 2259, 3275, 4422, 209, 3485, 4464, 1026, 3341, 3078, 4880, 4834, 3819, 4419, 2708, 708, 3576, 3894, 2125, 107, 1319, 1077, 4968, 2911, 2393, 3505, 3390, 1842, 1036, 4609, 3350, 3101, 956, 1207, 417, 581, 1258, 3610, 129, 2853, 3814, 4155, 4499, 2138, 3085, 2141, 2320, 4949, 1775, 4578, 217, 315, 1236, 1784, 781, 3113, 1701, 4177, 4239, 264, 202, 501, 967, 869, 3942, 330, 368, 4294, 4535, 1917, 1973, 2197, 3659, 3099, 4220, 2402, 4941, 3440, 1694, 1934, 1564, 3063, 3331, 3662 });
	nn = sol.maxProfit(prices, fee);
	assert(nn == 458445);
}