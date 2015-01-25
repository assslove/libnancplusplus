#include <string.h>
#include <strings.h>
#include <stdint.h>

#include <iostream>

#include "xml_parser.h"

static void finalLibXml2() __attribute__ ((destructor));
void finalLibXml2()
{
	xmlCleanupParser();
}

XmlParser::XmlParser()
	:	m_doc(NULL)
{
}

XmlParser::~XmlParser()
{
	final();
}

bool XmlParser::initFile(const std::string &fileName_)
{
	return initFile(fileName_.c_str());
}

bool XmlParser::initFile(const char * fileName_)
{
	final();
	if(!fileName_) return false;
	m_doc = xmlParseFile(fileName_);
	return (m_doc != NULL);
}

bool XmlParser::initStr(const std::string &xml_)
{
	return initStr(xml_.c_str());
}

bool XmlParser::initStr(const char *xml_)
{
	final();
	if(!xml_) return false;
	m_doc = xmlParseDoc((xmlChar *)xml_);
	return (m_doc != NULL);
}

bool XmlParser::init()
{
	final();
	m_doc = xmlNewDoc((const xmlChar *)"1.0");
	return (m_doc != NULL);
}

void XmlParser::final()
{
	if(m_doc)
	{
		xmlFreeDoc(m_doc);
		m_doc = NULL;
	}
}

std::string & XmlParser::dump(std::string &s_, bool format_)
{
	if(m_doc)
	{
		int size = 0;
		xmlChar *out = NULL;
		xmlDocDumpFormatMemory(m_doc, &out, &size, format_?1:0);
		if(out)
		{
			s_ = (char *)out;
			xmlFree(out);
		}
	}

	return s_;
}

std::string & XmlParser::dump(std::string &s_, const char *encoding_)
{
	if(m_doc)
	{
		xmlChar *out = NULL;

		int size = 0;
		xmlDocDumpMemoryEnc(m_doc, &out, &size, encoding_);
		if(out)
		{
			s_ = (char *)out;
			xmlFree(out);
		}
	}

	return s_;
}


xmlNodePtr XmlParser::getRootNode(const char *rootName_)
{
	if(!m_doc) return NULL;

	xmlNodePtr cur = xmlDocGetRootElement(m_doc);

	if(rootName_)
		while(cur && xmlStrcmp(cur->name, (const xmlChar *)rootName_))
			cur = cur->next;

	return cur;
}

xmlNodePtr XmlParser::getChildNode(const xmlNodePtr parent_, const char *childName_)
{
	if(!m_doc) return NULL;

	xmlNodePtr retval = parent_->children;

	if(childName_)
		while(retval)
		{
			if(!xmlStrcmp(retval->name, (const xmlChar *)childName_))
				break;
			retval = retval->next;
		}
	else
		while(retval)
		{
			if(!xmlNodeIsText(retval))
				break;
			retval = retval->next;
		}
		
	return retval;
}

unsigned int XmlParser::getChildNodeNum(const xmlNodePtr parent_, const char *childName_)
{
	int retval = 0;
	if(!parent_) return retval;

	xmlNodePtr child = parent_->children;

	if(childName_)
		while(child)
		{
			if(!xmlStrcmp(child->name, (const xmlChar *)childName_))
				retval++;
			child = child->next;
		}
	else
		while(child)
		{
			if(!xmlNodeIsText(child))
				retval++;
			child = child->next;
		}
		
	return retval;
}

xmlNodePtr XmlParser::getNextNode(const xmlNodePtr node_, const char *nextName_)
{
	if(!node_) return NULL;

	xmlNodePtr retval = node_->next;

	if(nextName_)
		while(retval)
		{
			if(!xmlStrcmp(retval->name, (const xmlChar *)nextName_))
				break;
			retval = retval->next;
		}
	else
		while(retval)
		{
			if(!xmlNodeIsText(retval))
				break;
			retval = retval->next;
		}
		
	return retval;
}

xmlNodePtr XmlParser::newRootNode(const char *rootName_)
{
	if(NULL == m_doc) return NULL;

	xmlNodePtr rootNode = xmlNewNode(NULL, (const xmlChar *)rootName_);
	xmlDocSetRootElement(m_doc, rootNode);

	return rootNode;
}

xmlNodePtr XmlParser::newChildNode(const xmlNodePtr parent_, const char *childName_, const char *content_)
{
	if(!parent_) return NULL;

	return xmlNewChild(parent_, NULL, (const xmlChar *)childName_, (const xmlChar *)content_);
}

bool XmlParser::newNodeProp(const xmlNodePtr node_, const char *propName_, const char *prop_)
{
	if(!node_) return false;

	return (NULL != xmlNewProp(node_, (const xmlChar *)propName_, (const xmlChar *)prop_));
}

bool XmlParser::getNodePropNum(const xmlNodePtr node_, const char *propName_, void *prop_, int propSize_)
{
	char *tmp = NULL;
	bool ret = true;

	if(!node_ || !prop_ || !propName_) return false;

	tmp = (char *)xmlGetProp(node_, (const xmlChar *)propName_);
	if(!tmp) return false;

	switch(propSize_)
	{
		case sizeof(uint8_t):
			*(uint8_t *)prop_ = (uint8_t)atoi(tmp);
			break;

		case sizeof(int16_t):
			*(int16_t *)prop_ = (int16_t)atoi(tmp);
			break;

		case sizeof(int32_t):
			*(int32_t *)prop_ = atoi(tmp);
			break;

		case sizeof(uint64_t):
			*(uint64_t *)prop_ = atoll(tmp);
			break;

		default:
			ret = false;
	}

	if(tmp) xmlFree(tmp);
	return ret;
}

bool XmlParser::getNodePropStr(const xmlNodePtr node_, const char *propName_, void *prop_, int propSize_)
{
	bool ret = true;

	if(!node_ || !prop_ || !propName_) return false;

	prop_= (char *)xmlGetProp(node_, (const xmlChar *)propName_);
	if(!prop_) return false;

	return ret;
}

bool XmlParser::getNodePropStr(const xmlNodePtr node_, const char *propName_, std::string &prop_)
{
	bool ret = true;

	if(!node_ || !propName_) return false;
	prop_ = (char *)xmlGetProp(node_, (const xmlChar *)propName_);
	if(!prop_.size()) return false;

	return ret;
}

bool XmlParser::getNodeContentNum(const xmlNodePtr node_, void *content_, int contentSize_)
{
	char *tmp = NULL;
	bool ret = true;

	if(!node_ || !content_) return false;
	
	xmlNodePtr text = node_->children;

	while(text)
	{
		if(!xmlStrcmp(text->name, (const xmlChar *)"text"))
		{
			tmp = (char *)text->content;
			break;
		}

		text = text->next;
	}

	if(!tmp) return false;

	switch(contentSize_)
	{
		case sizeof(uint8_t):
			*(uint8_t *)content_ = (uint8_t)atoi(tmp);
			break;

		case sizeof(int16_t):
			*(int16_t *)content_ = (int16_t)atoi(tmp);
			break;

		case sizeof(int32_t):
			*(int32_t *)content_ = atoi(tmp);
			break;

		case sizeof(uint64_t):
			*(uint32_t *)content_ = atoll(tmp);
			break;

		default:
			ret = false;
	}

	return ret;
}


