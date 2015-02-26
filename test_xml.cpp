/*
 * =====================================================================================
 *
 *       Filename:  test_xml.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年01月26日 08时03分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <libnanc++/xml_parser.h>

int main(int argc, char* argv[]) 
{
	XmlParser xmlParser;
	xmlParser.initFile("a.xml");
	return 0;
}
