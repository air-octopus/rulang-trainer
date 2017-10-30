#pragma once

#include <string>

#include "utf8.h"

inline std::wstring utf8to16(const char *utf8_str, size_t sz)
{
    std::wstring utf16_str;
    utf16_str.reserve(sz);
    utf8::utf8to16(utf8_str, utf8_str + sz, std::back_inserter(utf16_str));
    return std::move(utf16_str);
}

inline std::wstring utf8to16(const std::string &utf8_str)
{
    return utf8to16(utf8_str.data(), utf8_str.size());
}

inline std::string make_utf8(const std::string & str) { return str; }
inline std::string make_utf8(const std::wstring & str)
{
    std::string utf8_str;
    utf8_str.reserve(str.size() * 3);
    utf8::utf16to8(str.begin(), str.end(), std::back_inserter(utf8_str));
    return std::move(utf8_str);
}
