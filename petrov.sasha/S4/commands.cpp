#include "commands.hpp"
#include "dictionary.hpp"

#include <cstring>
#include <istream>
#include <ostream>

namespace
{
  const char INVALID_COMMAND[] = "<INVALID COMMAND>";
}

const petrov::Command COMMANDS[] =
{
  { "print", petrov::printCommand },
  { "complement", petrov::complementCommand },
  { "intersect", petrov::intersectCommand },
  { "union", petrov::unionCommand }
};

const std::size_t COMMAND_COUNT =
  sizeof(COMMANDS) / sizeof(COMMANDS[0]);

const petrov::Command *
petrov::findCommand(const char * name) noexcept
{
  for (std::size_t i = 0; i < COMMAND_COUNT; ++i)
  {
    if (std::strcmp(COMMANDS[i].name, name) == 0)
    {
      return &COMMANDS[i];
    }
  }
  return nullptr;
}

void petrov::printCommand(Storage & storage,
    std::istream & in,
    std::ostream & out)
{
  std::string dataset;

  if (!(in >> dataset))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  if (!storage.has(dataset))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  const Dictionary & dict = storage.get(dataset);

  if (dict.empty())
  {
    out << "<EMPTY>" << '\n';
    return;
  }

  out << dataset;

  for (Dictionary::const_iterator it = dict.begin();
      it != dict.end();
      ++it)
  {
    out << ' ' << it->first << ' ' << it->second;
  }

  out << '\n';
}

void petrov::complementCommand(Storage & storage,
    std::istream & in,
    std::ostream & out)
{
  std::string newName;
  std::string leftName;
  std::string rightName;

  if (!(in >> newName >> leftName >> rightName))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  if (!storage.has(leftName) || !storage.has(rightName))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  if (storage.has(newName))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  Dictionary result =
    storage.get(leftName).complement(storage.get(rightName));

  storage.insert(newName, result);
}

void petrov::intersectCommand(Storage & storage,
    std::istream & in,
    std::ostream & out)
{
  std::string newName;
  std::string leftName;
  std::string rightName;

  if (!(in >> newName >> leftName >> rightName))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  if (!storage.has(leftName) || !storage.has(rightName))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  if (storage.has(newName))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  Dictionary result = storage.get(leftName).intersect(storage.get(rightName));

  storage.insert(newName, result);
}

void petrov::unionCommand(Storage & storage,
    std::istream & in,
    std::ostream & out)
{
  std::string newName;
  std::string leftName;
  std::string rightName;

  if (!(in >> newName >> leftName >> rightName))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  if (!storage.has(leftName) || !storage.has(rightName))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  if (storage.has(newName))
  {
    out << INVALID_COMMAND << '\n';
    return;
  }

  Dictionary result = storage.get(leftName).unite(storage.get(rightName));

  storage.insert(newName, result);
}
