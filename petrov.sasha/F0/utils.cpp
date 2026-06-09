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

