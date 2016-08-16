#ifndef HTTP_RESOURCE_HPP
#define HTTP_RESOURCE_HPP

#include <string>
#include <map>
#include "../mime/MimeDB.cpp"
#include "../mime/MimeType.cpp"
#include "../core/CoreObject.cpp"

class HttpResource : public CoreObject
{
private:
	std::string mURL;
	std::string mContent;

	MimeDB& mMimeDB;
	MimeType mMimeType;

public:
	HttpResource(std::string url, MimeDB& mimeDB);
	std::string Content();
	uint32_t ContentLength();
	MimeType Mime();
	virtual uint32_t Load();
	void ReplaceTokens(std::map<std::string, std::string> tokenMap);
};

#endif

