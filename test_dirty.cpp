//=====================================================================

// **   Copyright(c) 2014 纵游网络. 
// **   All rights reserved.

// **   @File     main.cpp
// **   @Author   bin.hou at 2015年02月26日 14时21分03秒
// **   @Brief    定义
// **   @Version  1.0

//=====================================================================

#include <libnanc++/dirty.h>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "zh_CN.UTF-8"); //可以输出中文

	//const wchar_t* data [] =  {L"fuck", L"food", L"beast", L"aboard", L"boot", L"cat", L"ddd", L"你妈比", L"你妈", L"比较"};
	Dirty trie;
	trie.initDirty("dirty.dat");

	trie.display();

	std::wcout << trie.checkDirty("做原子aafuck") << std::endl;

	char str[] = "做原子弹aafuckbbboot";
	trie.replaceDirty(str);
	//std::cout << str << std::endl;
	std::string wstr(strlen(str), L' ');
	std::copy(str, str + strlen(str), wstr.begin());
	std::wcout << wstr.c_str() << std::endl;

	//std::wcout << wstr.c_str() << std::endl;
	//setlocale(LC_ALL, "zh_CN.UTF-8"); //可以输出中文
	//xDirty trie;
	//const char *src = "你吗";
	//wchar_t *wstr = (wchar_t*)malloc(sizeof(wchar_t) * strlen(src));
	//mbstowcs(wstr, src, strlen(src));
	//std::wcout << wcslen(wstr) << std::endl;
	//std::wcout << wstr << std::endl;
	return 0;
}
