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

bool petrov::exportDatabase(const std::string& path, const Database& database)
{
  std::ofstream file(path);
  if (!file) {
    return false;
  }
  file << "TAGS " << database.tags.size() << '\n';
  for (TagTree::const_iterator it = database.tags.begin(); it != database.tags.end(); ++it) {
    file << it->first << '\n';
  }
  file << "QUESTIONS " << database.questions.size() << '\n';
  for (QuestionTree::const_iterator it = database.questions.begin(); it != database.questions.end(); ++it) {
    const Question& question = it->second;
    file << typeName(question) << '\n';
    file << question.id << '\n';
    file << question.text << '\n';
    file << question.options.size() << '\n';
    for (std::size_t i = 0; i < question.options.size(); ++i) {
      file << question.options[i] << '\n';
    }
    if (question.type == QuestionType::matching) {
      for (std::size_t i = 0; i < question.rights.size(); ++i) {
        file << question.rights[i] << '\n';
      }
    } else {
      file << question.correct.size() << '\n';
      for (std::size_t i = 0; i < question.correct.size(); ++i) {
        file << question.correct[i] << '\n';
      }
    }
    writeQuestionTags(file, question);
    file << "END\n";
  }
  return static_cast< bool >(file);
}

