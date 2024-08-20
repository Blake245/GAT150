#include "EString.h"

std::string ToLower(const std::string& str)
{
	std::string lowerStr;
	lowerStr.resize(str.size());

	// C/C++
	/*for (int i = 0; i < lowerStr.size(); i++)
	{
		lowerStr[i] = std::tolower(str[i]);
	}*/

	// modern c++
	std::transform(str.begin(), str.end(), lowerStr.begin(),
		[](char c)
		{
			return std::tolower(c);
		});

	return lowerStr;
}

std::string ToUpper(const std::string& str)
{
	std::string upperStr;
	upperStr.resize(str.size());

	std::transform(str.begin(), str.end(), upperStr.begin(),
		[](char c)
		{
			return std::toupper(c);
		});

	return upperStr;
}

bool IsEqualIgnoreCase(std::string& str1, std::string& str2)
{
	if (str1.length() != str2.length()) return false;

	return std::equal(str1.begin(), str1.end(), str2.begin(),
		[](char c1, char c2)
		{
			return std::tolower(c1) == std::tolower(c2);
		});
}
