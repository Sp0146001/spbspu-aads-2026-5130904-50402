#include "utils.hpp"

#include <cctype>
#include <string>
#include <vector>

std::string petrov::trim(const std::string& source)
{
  std::size_t begin = 0;
  std::size_t end = source.size();
  while (begin < end && std::isspace(static_cast< unsigned char >(source[begin]))) {
    ++begin;
  }
  while (end > begin && std::isspace(static_cast< unsigned char >(source[end - 1]))) {
    --end;
  }
  return source.substr(begin, end - begin);
}

std::string petrov::toLower(const std::string& source)
{
  std::string result;
  result.reserve(source.size());
  for (std::size_t i = 0; i < source.size(); ++i) {
    const char lowered = static_cast< char >(std::tolower(static_cast< unsigned char >(source[i])));
    result.push_back(lowered);
  }
  return result;
}

bool petrov::containsIgnoreCase(const std::string& haystack, const std::string& needle)
{
  if (needle.empty()) {
    return true;
  }
  return toLower(haystack).find(toLower(needle)) != std::string::npos;
}

