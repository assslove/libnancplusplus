/*
 * =====================================================================================
 *
 *       Filename:  test_singleton.cpp
 *
 *    Description:  用来测试单例
 *
 *        Version:  1.0
 *        Created:  2015年01月20日 19时15分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <iostream>
#include <libnanc++/singleton.h>

class Service : public Singleton<Service>
{
	friend class Singleton<Service>;

	private:
		Service() : count(2) {}
		~Service() {}

	public:
		void set_count(int count) {
			this->count = count;	
		}
		void print() {
			std::cout << count << "\n";
		}
	private:
		int count;
};

int main(int argc, char *argv[])
{
	Service::getInstance().print();
//	Service *s = new Service();
//	s->print();
	Service::delInstance();

	return 0;
}
