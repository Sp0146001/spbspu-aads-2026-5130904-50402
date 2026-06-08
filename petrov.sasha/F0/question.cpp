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

bool petrov::letterToIndex(const std::string& letter, std::size_t& index)
{
  if (letter.size() != 1) {
    return false;
  }
  const char symbol = letter[0];
  if (symbol >= 'A' && symbol <= 'Z') {
    index = static_cast< std::size_t >(symbol - 'A');
    return true;
  }
  if (symbol >= 'a' && symbol <= 'z') {
    index = static_cast< std::size_t >(symbol - 'a');
    return true;
  }
  return false;
}

char petrov::indexToLetter(std::size_t index)
{
  return static_cast< char >('A' + index);
}


