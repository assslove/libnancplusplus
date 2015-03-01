#ifndef DIRTY_H_
#define DIRTY_H_

#include <iostream>
#include <set>
#include <wchar.h>
#include <string>
#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* @brief 脏词节点
 */
struct TrieNode 
{
	std::map<wchar_t, TrieNode*> childs; //子树
	bool isTerminal;	//结束节点

	TrieNode() : isTerminal(false)
	{
		childs.clear();
	}
};

/* @brief 字典树类
 */
class Dirty 
{
	typedef std::map<wchar_t, TrieNode*>::iterator TrieIter;

	public:
		Dirty () : m_root(NULL) 
		{
			
		}

		~Dirty () 
		{
			delete m_root;
		}

		TrieNode* create() 
		{
			TrieNode *node = new TrieNode();
			return node;
		}

		/* @brief 插入节点
		 */
		void insert(const wchar_t* str_);

		/* @brief 初始化脏词库
		*/
		void initDirty(const char* name_);

		/* @brief 打印每个节点 用于调试
		 */
		void displayNode(TrieNode *node_);

		/* @brief 打印字典树
		*/
		void display() 
		{
			if (!m_root) 
			{
				return ;
			}

			displayNode(m_root);
		}

		/* @brief 检查是否包含脏词
		 * @return 0-无 其它有
		 */
		int checkDirty(const char* content_);

		/* @brief 对脏词进行替换成***
		*/
		void replaceDirty(char* content_); 

	private:
		TrieNode* m_root; //根结点
};

#endif
