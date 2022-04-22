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


void FindAndReplace(std::string& subject, std::string const& search, std::string const& replace)
{
	size_t foundPosition = 0;

	while ((foundPosition = subject.find(search, foundPosition)) != std::string::npos)
	{
		subject.replace(
			subject.begin() + foundPosition, 
			subject.begin() + foundPosition + search.size(), 
			replace
		);
	}
}

std::string HtmlDecode(std::string const& html)
{
	std::string result = html;

	for (auto const& htmlEntity : HTML_TABLE)
	{
		FindAndReplace(result, htmlEntity.first, htmlEntity.second);
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