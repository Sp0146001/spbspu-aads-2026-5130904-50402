#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>

namespace petrov
{
  class Storage;

  struct Command
  {
    const char * name;
    void (*execute)(Storage & storage,
        std::istream & in,
        std::ostream & out);
  };

  const Command * findCommand(const char * name) noexcept;

  void printCommand(Storage & storage,
      std::istream & in,
      std::ostream & out);

  void complementCommand(Storage & storage,
      std::istream & in,
      std::ostream & out);

  void intersectCommand(Storage & storage,
      std::istream & in,
      std::ostream & out);

  void unionCommand(Storage & storage,
      std::istream & in,
      std::ostream & out);
}

#endif

