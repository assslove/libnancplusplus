//=====================================================================

// **   Copyright(c) 2014 纵游网络. 
// **   All rights reserved.

// **   @File     main.cpp
// **   @Author   bin.hou at 2015年02月26日 14时21分03秒
// **   @Brief    定义
// **   @Version  1.0

//=====================================================================

#include <libnanc++/dirty.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "zh_CN.UTF-8"); //可以输出中文

	//const wchar_t* data [] =  {L"fuck", L"food", L"beast", L"aboard", L"boot", L"cat", L"ddd", L"你妈比", L"你妈", L"比较"};
	Dirty trie;
	trie.initDirty("dirty.dat");

//	trie.display();
	timeval prev, last;
	gettimeofday(&prev, NULL);
	bool isDirty = trie.checkDirty("做原子aafuck");	
	gettimeofday(&last, NULL);

	std::wcout << isDirty << " " << last.tv_usec - prev.tv_usec << std::endl;

	gettimeofday(&prev, NULL);
	char str[] = "做原子弹aafuckbbbootaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa被指抄袭aaaaaaa磅解码器aaaaaaa办怔aaaa";
	trie.replaceDirty(str);
	gettimeofday(&last, NULL);
	//std::cout << str << std::endl;
	std::string wstr(strlen(str), L' ');
	std::copy(str, str + strlen(str), wstr.begin());
	std::wcout << wstr.c_str() << " " << last.tv_usec - prev.tv_usec << std::endl;

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
