#include "question.hpp"

#include <cctype>
#include <ostream>
#include <string>

std::string petrov::typeName(const Question& question)
{
  if (question.type == QuestionType::single) {
    return "single";
  }
  if (question.type == QuestionType::multiple) {
    return "multiple";
  }
  return "matching";
}

