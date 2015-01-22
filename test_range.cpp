/*
 * =====================================================================================
 *
 *       Filename:  test_range.cpp
 *
 *    Description:  测试范围内查找数据
 *
 *        Version:  1.0
 *        Created:  2015年01月22日 09时44分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <iostream>
#include <libnanc++/range.h>

int main(int argc, char* argv[])
{
	RangeManager<range_t> range_mgr;

	for (int i = 0; i < 200;) {
		range_t r = {i, i+5};
		i = i + 6;
		range_mgr.push_back(r);
	}

	range_mgr.random_shuffle();
	for (int i = 0; i < range_mgr.size(); ++i) {
		std::cout << range_mgr[i].start << "\t" <<range_mgr[i].end << std::endl;
	}

	range_mgr.sort_less();
	for (int i = 0; i < range_mgr.size(); ++i) {
		std::cout << range_mgr[i].start << "\t" <<range_mgr[i].end << std::endl;
	}


	const range_t *tmp = range_mgr.find(11);
	if (tmp) {
		std::cout << tmp->start << "\t" << tmp->end << std::endl;
	}
	return 0;
}
