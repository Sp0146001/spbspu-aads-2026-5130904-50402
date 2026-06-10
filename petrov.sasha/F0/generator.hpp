#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <set>
#include <string>
#include <vector>

#include "database.hpp"

namespace petrov
{
  struct GenParams
  {
    std::string title;
    int variants;
    int questionsPerVariant;
    std::vector< std::string > tags;
    std::set< std::string > excludeIds;

    GenParams():
      title("Самостоятельная работа"),
      variants(0),
      questionsPerVariant(0),
      tags(),
      excludeIds()
    {}
  };
}

#endif
