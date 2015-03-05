/*
 * =====================================================================================
 *
 *       Filename:  dirty.cpp
 *
 *    Description:本敏感词过滤程序支持替换与检查操作，支持中文  
 *					利用字典树实现 字典树利用map, 在百微秒内进行替换
 *
 *        Version:  1.0
 *        Created:  2015年02月26日 17时16分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include "dirty.h"

void Dirty::insert(const wchar_t* str_) 
{
	if (!m_root) 
	{
		m_root = create();
	}
	std::wstring wstr = str_;
	TrieNode *nextNode = m_root;
	for (size_t i = 0; i < wstr.size(); ++i) 
	{
		TrieIter it = nextNode->childs.find(wstr[i]);
		if (it != nextNode->childs.end()) 
		{ //找到则进行下一次循环
			nextNode = it->second;	
		} 
		else 
		{ //找不到插入
			TrieNode *tmp = new TrieNode();
			nextNode->childs.insert(std::pair<wchar_t, TrieNode*>(wstr[i], tmp));
			nextNode = tmp;
		}
	}

	nextNode->isTerminal = true;
}

/* @brief 初始化脏词库
*/
void Dirty::initDirty(const char* name_)
{
	setlocale(LC_ALL, "zh_CN.UTF-8");//可以输出中文

	FILE *fp  = fopen(name_, "r");
	if (!fp) 
	{
		fprintf(stderr, "cannot read file %s", name_);
		return ;
	}

	size_t len = 256;
	char* line = NULL;
	wchar_t *wline = (wchar_t *)malloc(sizeof(wchar_t) * 100); //最长有10个词
	if (!wline) 
	{
		fprintf(stderr, "malloc wchar failed\n");
		return ;
	}

	ssize_t read;
	while ((read = getline(&line, &len, fp)) != -1) 
	{
		line[read - 1] = '\0';
		mbstowcs(wline, line, read);	
		insert(wline);
	}
	free(line);
	free(wline);
}

/* @brief 打印字典树 用于调试
*/
void Dirty::displayNode(TrieNode *node_) 
{
	if (node_->isTerminal) 
	{
		std::wcout << node_->childs.begin()->first;
		std::wcout << std::endl;
	}
	else 
	{
		TrieIter it = node_->childs.begin();
		for (; it != node_->childs.end(); ++it) 
		{
			std::wcout << it->first;
			displayNode(it->second);
		}
	}
}

/* @brief 检查是否包含脏词
 * @return 0-无 其它有
 */
int Dirty::checkDirty(const char* content_) 
{
	int tmplen = strlen(content_) + 1;
	wchar_t *wstr = (wchar_t *)malloc(sizeof(wchar_t) * tmplen);
	if (!wstr) 
	{
		return 0;
	}
	//char* to wchar_t*
	mbstowcs(wstr, content_, tmplen);

	int len = wcslen(wstr);
	TrieNode *node = m_root;
	TrieIter it;
	for (int i = 0; i < len; ++i) 
	{
		for (int j = i; j < len; ++j) 
		{
			if (!node) {
				break;
			}
			it = node->childs.find(wstr[j]);
			if (it != node->childs.end()) 
			{ //找到相应, 继续找下一个
				node = it->second;
				if (node->isTerminal) 
				{ //如果是最后一个说明找到
					free(wstr);
					return 1;
				}
				else 
				{
					continue;
				}

			}  
			else 
			{
				node = m_root;
				break;
			}
		}
	}

	free(wstr);
	return 0;
}

/* @brief 对脏词进行替换成***
*/
void Dirty::replaceDirty(char* content_) 
{
	int tmplen = strlen(content_) + 1;
	wchar_t *wstr = (wchar_t *)malloc(sizeof(wchar_t) * tmplen);
	if (!wstr) 
	{
		return ;
	}
	mbstowcs(wstr, content_, tmplen);
	int len = wcslen(wstr);

	TrieNode *node = m_root;
	TrieIter it;
	for (int i = 0; i < len; ++i)
	{
		for (int j = i; j < len; ++j) 
		{
			if (!node) {
				break;
			}
			it = node->childs.find(wstr[j]);
			if (it != node->childs.end()) 
			{
				node = it->second;
				if (node->isTerminal) 
				{ //如果匹配到,则替换
					wmemset(wstr + i, L'*', j-i+1);
					i = j;
					node = m_root;
					break;
				} 
				else 
				{ //否则继续匹配
					continue;
				}
			}
			else 
			{ //没有匹配成功进入下一次循环
				node = m_root;
				break;
			}
		}
	}

	//wchar* 转化为char*
	wcstombs(content_, wstr, tmplen);
	free(wstr);
}


