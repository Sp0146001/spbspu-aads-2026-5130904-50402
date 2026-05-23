#include "commands.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid parameters\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file) {
    std::cerr << "Cannot open file\n";
    return 1;
  }
  petrov::Storage storage;
  std::string dataset;
  while (file >> dataset) {
    petrov::InnerTree tree;
    int key = 0;
    std::string value;
    while (file >> key >> value) {
      tree.push(key, value);
      if (file.peek() == '\n') {
        break;
      }
    }
    storage.push(dataset, tree);
  }
  std::string commandName;
  while (std::cin >> commandName) {
    const petrov::Command * command =
      petrov::findCommand(commandName);
    if (command == nullptr) {
      std::cout << "<INVALID COMMAND>\n";
      continue;
    }
    command->execute(storage, std::cin, std::cout);
  }
  return 0;
}

