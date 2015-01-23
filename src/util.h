#ifndef _UTIL_H
#define _UTIL_H

/* @brief c++实用类 和 宏定义
 */

/* @brief 正向迭代器
 */
#define FOREACH(it, container) \
	for(typeof(container.begin()) it = container.begin(); it != container.end(); ++it)

#endif
