#pragma once
#include <string>
#include <algorithm>

std::string ToLower(const std::string& str);
std::string ToUpper(const std::string& str);
bool IsEqualIgnoreCase(std::string& str1, std::string& str2);
