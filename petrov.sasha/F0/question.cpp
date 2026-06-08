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

void petrov::renderBody(std::ostream& out, const Question& question)
{
  if (question.type == QuestionType::matching) {
    for (std::size_t i = 0; i < question.options.size(); ++i) {
      out << (i + 1) << ". " << question.options[i] << "\n";
    }
    out << "\n";
    for (std::size_t i = 0; i < question.rights.size(); ++i) {
      out << indexToLetter(i) << ") " << question.rights[i] << "\n";
    }
    return;
  }
  for (std::size_t i = 0; i < question.options.size(); ++i) {
    out << indexToLetter(i) << ") " << question.options[i] << "\n";
  }
}



