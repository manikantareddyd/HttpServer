#ifndef HTTP_RESPONSE_DB_HPP
#define HTTP_RESPONSE_DB_HPP

#include "../core/CoreObject.cpp"
#include "../utility/FileUtil.cpp"
#include "../utility/StringUtil.cpp"
#include "../utility/KvpDB.cpp"

class HttpResponseDB : public KvpDB
{
public:
	HttpResponseDB();
	std::string ResponseString(int statusCode);
};

#endif
