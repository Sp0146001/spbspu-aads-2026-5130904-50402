#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <cstddef>
#include <string>

#include "avltree.hpp"
#include "question.hpp"
#include "tag.hpp"

namespace petrov
{
  using QuestionTree = AvlTree< std::string, Question >;
  using TagTree = AvlTree< std::string, Tag >;

  struct Database
  {
    QuestionTree questions;
    TagTree tags;
    std::size_t deletedQuestions;
    std::size_t deletedTags;

    Database():
      questions(),
      tags(),
      deletedQuestions(0),
      deletedTags(0)
    {}
  };
}

#endif

