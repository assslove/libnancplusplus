#ifndef _XML_PARSER_H
#define _XML_PARSER_H

#include <string>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>

/**
 *	@brief	XML解析器类定义
 */
class XmlParser
{
	public:

		XmlParser();		
		~XmlParser();		

		bool initFile(const std::string &fileName_);
		bool initFile(const char *fileName_);
		bool initStr(const std::string &xml_);
		bool initStr(const char *xml_);
		bool init();
		void final();

		std::string & dump(std::string &s_, bool format_ = false);
		std::string & dump(std::string &s_, const char *encoding_);
		std::string & dump(xmlNodePtr dumpNode_, std::string &s_, bool head_ = true);

		xmlNodePtr getRootNode(const char *rootName_);
		xmlNodePtr getChildNode(const xmlNodePtr parent_, const char *childName_);
		unsigned int getChildNodeNum(const xmlNodePtr parent_, const char *childName_);
		xmlNodePtr getNextNode(const xmlNodePtr node_, const char *nextName_);

		xmlNodePtr newRootNode(const char *rootName_);
		xmlNodePtr newChildNode(const xmlNodePtr parent_, const char *childName_, const char *content_);

		bool newNodeProp(const xmlNodePtr node_, const char *propName_, const char *prop_);

		bool getNodePropNum(const xmlNodePtr node_, const char *propName_, void *prop_, int propSize_);
		bool getNodePropStr(const xmlNodePtr node_, const char *propName_, void *prop_, int propSize_);
		bool getNodePropStr(const xmlNodePtr node_, const char *propName_, std::string &prop_);

		bool getNodeContentNum(const xmlNodePtr node_, void *content_, int contentSize_);
		bool getNodeContentStr(const xmlNodePtr node_, void *content_, int contentSize_);
		bool getNodeContentStr(const xmlNodePtr node_, std::string &content_);

		xmlDocPtr &getDoc() { return m_doc; }

		static unsigned char *charConv(unsigned char *in_, const char *fromEncoding_, const char *toEncoding_);

	private:

		xmlDocPtr m_doc;
};

#endif /* _X_XML_PARSER_H */
