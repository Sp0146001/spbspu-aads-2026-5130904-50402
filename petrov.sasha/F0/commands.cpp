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

