#include "UrlParsingError.h"

CUrlParsingError::CUrlParsingError(std::string const& message)
	: std::invalid_argument(message)
{
}
