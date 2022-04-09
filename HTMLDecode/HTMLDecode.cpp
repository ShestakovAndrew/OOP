#include "HTMLDecode.h"

namespace
{
	static std::map<std::string, std::string> HTML_TABLE = {
			{"&quot;", "\""},
			{"&apos;", "'"},
			{"&lt;", "<"},
			{"&gt;", ">"},
			{"&amp;", "&"},
	};
}

std::string FindAndReplace(std::string const& subject, std::string const& search, std::string  const& replace)
{
	std::string result;

	if (search.empty()) result = subject;

	size_t position = 0;
	while (position < subject.size())
	{
		size_t foundPosition = subject.find(search, position);
		result.append(subject, position, (foundPosition - position));
		if (foundPosition != std::string::npos)
		{
			result.append(replace);
			position = foundPosition + search.size();
		}
		else break;
	}
	return result;
}

std::string HtmlDecode(std::string const& html)
{
	std::string result = html;
	for (auto const& htmlEntity : HTML_TABLE)
	{
		result = FindAndReplace(result, htmlEntity.first, htmlEntity.second);
	}
	return result;
}

std::string HtmlDecodeOld(std::string const& html)
{
	std::string text = html;

	for (size_t i = 0; i < text.size(); i++)
	{
		if (text[i] == '&')
		{
			for (size_t j = 4; j <= 6; j++)
			{
				std::string substr = text.substr(i, j);
				if (i+j <= text.length() and HTML_TABLE.find(substr) != HTML_TABLE.end())
				{
					text = text.replace(i, j, HTML_TABLE[substr]);
					break;
				}
			}
		}
	}
	
 	return text;
}