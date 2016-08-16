#ifndef MIME_DB_HPP
#define MIME_DB_HPP

#include "../core/CoreObject.cpp"
#include "../utility/FileUtil.cpp"
#include "../utility/StringUtil.cpp"
#include "../utility/KvpDB.cpp"
#include "MimeType.cpp"

class MimeDB : public KvpDB
{
public:
    MimeDB();
    MimeType GetMime(const std::string& filePath);
};

#endif
