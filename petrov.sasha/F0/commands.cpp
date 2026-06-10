#include "commands.hpp"

#include <cstddef>
#include <istream>
#include <ostream>
#include <set>
#include <string>
#include <vector>

namespace petrov
{
  const Command COMMANDS[] = {
    { "addq", addQuestion },
    { "delq", delQuestion },
    { "editq", editQuestion },
    { "listq", listQuestions },
    { "findq", findQuestions },
    { "addtag", addTag },
    { "deltag", delTag },
    { "listtag", listTags },
    { "tagq", tagQuestion },
    { "untagq", untagQuestion },
    { "tagsq", questionTags },
    { "gen", generate },
    { "template", printTemplate },
    { "exportdb", exportDb },
    { "importdb", importDb },
    { "statsq", statsQuestions },
    { "statstag", statsTags }
  };
  const std::size_t COMMAND_COUNT = sizeof(COMMANDS) / sizeof(COMMANDS[0]);
}

const petrov::Command* petrov::findCommand(const std::string& name)
{
  for (std::size_t i = 0; i < COMMAND_COUNT; ++i) {
    if (name == COMMANDS[i].name) {
      return std::addressof(COMMANDS[i]);
    }
  }
  return nullptr;
}

static void reportInvalid(std::ostream& out, const std::string& reason)
{
  out << "<INVALID COMMAND> " << reason << '\n';
}

static std::size_t findMarker(const petrov::Tokens& tokens, const std::string& marker, std::size_t from)
{
  for (std::size_t i = from; i < tokens.size(); ++i) {
    if (tokens[i] == marker) {
      return i;
    }
  }
  return tokens.size();
}

void petrov::addQuestion(Database& database, const Tokens& tokens, std::istream&, std::ostream& out)
{
  if (tokens.size() < 3) {
    reportInvalid(out, "not enough arguments");
    return;
  }
  const std::string& id = tokens[1];
  const std::string& type = tokens[2];
  if (database.questions.has(id)) {
    reportInvalid(out, "question id=" + id + " already exists");
    return;
  }
  if (type == "single") {
    if (tokens.size() < 4) {
      reportInvalid(out, "not enough arguments");
      return;
    }
    const std::size_t correctPos = findMarker(tokens, "correct", 4);
    if (correctPos == tokens.size()) {
      reportInvalid(out, "missing correct marker");
      return;
    }
    if (correctPos == 4) {
      reportInvalid(out, "no answer options");
      return;
    }
    if (correctPos + 2 != tokens.size()) {
      reportInvalid(out, "single requires exactly one correct answer");
      return;
    }
    Question question;
    question.id = id;
    question.text = tokens[3];
    question.type = QuestionType::single;
    for (std::size_t i = 4; i < correctPos; ++i) {
      question.options.push_back(tokens[i]);
    }
    std::size_t index = 0;
    if (!letterToIndex(tokens[correctPos + 1], index) || index >= question.options.size()) {
      reportInvalid(out, "invalid correct answer");
      return;
    }
    question.correct.push_back(index);
    database.questions.push(id, question);
    out << "<Добавлен вопрос id=" << id << ", тип single>\n";
    return;
  }
  if (type == "multiple") {
    if (tokens.size() < 4) {
      reportInvalid(out, "not enough arguments");
      return;
    }
    const std::size_t correctPos = findMarker(tokens, "correct", 4);
    if (correctPos == tokens.size()) {
      reportInvalid(out, "missing correct marker");
      return;
    }
    if (correctPos == 4) {
      reportInvalid(out, "no answer options");
      return;
    }
    if (correctPos + 1 >= tokens.size()) {
      reportInvalid(out, "no correct answers");
      return;
    }
    Question question;
    question.id = id;
    question.text = tokens[3];
    question.type = QuestionType::multiple;
    for (std::size_t i = 4; i < correctPos; ++i) {
      question.options.push_back(tokens[i]);
    }
    std::set< std::size_t > unique;
    for (std::size_t i = correctPos + 1; i < tokens.size(); ++i) {
      std::size_t index = 0;
      if (!letterToIndex(tokens[i], index) || index >= question.options.size()) {
        reportInvalid(out, "invalid correct answer");
        return;
      }
      unique.insert(index);
    }
    for (std::set< std::size_t >::const_iterator it = unique.begin(); it != unique.end(); ++it) {
      question.correct.push_back(*it);
    }
    database.questions.push(id, question);
    out << "<Добавлен вопрос id=" << id << ", тип multiple>\n";
    return;
  }
  if (type == "matching") {
    if (tokens.size() < 6) {
      reportInvalid(out, "not enough arguments");
      return;
    }
    const std::size_t count = tokens.size() - 4;
    if (count % 2 != 0) {
      reportInvalid(out, "odd number of pair elements");
      return;
    }
    Question question;
    question.id = id;
    question.text = tokens[3];
    question.type = QuestionType::matching;
    for (std::size_t i = 4; i < tokens.size(); i += 2) {
      question.options.push_back(tokens[i]);
      question.rights.push_back(tokens[i + 1]);
    }
    database.questions.push(id, question);
    out << "<Добавлен вопрос id=" << id << ", тип matching>\n";
    return;
  }
  reportInvalid(out, "unknown type " + type);
}

