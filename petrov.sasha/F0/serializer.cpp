#include "serializer.hpp"

#include <fstream>
#include <istream>
#include <ostream>
#include <set>
#include <stdexcept>
#include <string>

#include "question.hpp"
#include "tag.hpp"

static void writeQuestionTags(std::ostream& out, const petrov::Question& question)
{
  out << question.tags.size() << '\n';
  for (std::set< std::string >::const_iterator it = question.tags.begin(); it != question.tags.end(); ++it) {
    out << *it << '\n';
  }
}

static bool readLine(std::istream& in, std::string& out)
{
  return static_cast< bool >(std::getline(in, out));
}

static bool readCount(std::istream& in, std::size_t& out)
{
  std::string line;
  if (!std::getline(in, line)) {
    return false;
  }
  try {
    out = static_cast< std::size_t >(std::stoul(line));
  } catch (const std::exception&) {
    return false;
  }
  return true;
}

