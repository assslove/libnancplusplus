#ifndef _RANGE_H
#define _RANGE_H

#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>

/* @brief 区间集合类
 */
typedef struct range {

	int start;
	int end;

	bool operator < (const struct range &r) const {
		return start < r.start;
	}

	bool operator > (const struct range &r) const {
		return start > r.start;
	}

} range_t;

/* @brief 集合管理
 * @note 用于在一个区间查找某个值
*/
template<typename T>
class RangeManager {

	private:
		typedef std::vector<T> RangeVec;
		typedef typename std::vector<T>::iterator RangeIter;
	public:

		const T& operator[] (int idx) {
			assert(idx < range_vec.size());
			return range_vec[idx];
		}

		/* @brief 往集合增加元素
		*/
		void push_back(const T& range_) {
			range_vec.push_back(range_);
		}

		/* @brief 返回集合中元素数量
		 */
		int size() {
			return range_vec.size();
		}

		/* @brief 根据第一个字段排序
		*/
		void sort_less() {
			std::sort(range_vec.begin(), range_vec.end(), std::less<T>());
		}

		void sort_greater() {
			std::sort(range_vec.begin(), range_vec.end(), std::greater<T>());
		}

		void random_shuffle() {
			std::random_shuffle(range_vec.begin(), range_vec.end());
		}

		/* @brief 查找区间
		*/
		const T* find(int value) {
			int start = 0, end = range_vec.size(), mid;

			while (start <= end) {
				mid = (start + end) / 2;
				if (value >= range_vec[mid].start && value <= range_vec[mid].end) {
					return &range_vec[mid];
				} else if (value >= range_vec[mid].start) {
					start = mid + 1;
				} else {
					end = mid - 1;
				}
			}

			return NULL;
		}

		/* @brief 获得range_vec
		 */
		RangeVec& get_range_vec() {
			return range_vec;
		}
	private:
		RangeVec range_vec;

};

#endif
