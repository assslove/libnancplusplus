/*
 * =====================================================================================
 *
 *       Filename:  test_iter.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年01月23日 14时59分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <libnanc++/util.h>


int main(int argc, char *argv[])
{
	std::vector<int> vec;
	for (int i = 0; i < 10; ++i) {
		vec.push_back(i);
	}

	FOREACH (it, vec) {
		std::cout << *it << std::endl;
	}
	return 0;
}
