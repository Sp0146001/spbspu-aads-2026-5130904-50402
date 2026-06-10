#include "generator.hpp"
#include "utils.hpp"

#include <fstream>
#include <random>
#include <stdexcept>
#include <string>

bool petrov::parseGenFile(const std::string& path, GenParams& params, std::string& error)
{
  std::ifstream file(path);
  if (!file) {
    error = "cannot open input file " + path;
    return false;
  }
  std::string line;
  while (std::getline(file, line)) {
    const std::string trimmed = trim(line);
    if (trimmed.empty() || trimmed[0] == '#') {
      continue;
    }
    const std::size_t eq = trimmed.find('=');
    if (eq == std::string::npos) {
      continue;
    }
    const std::string key = trim(trimmed.substr(0, eq));
    const std::string value = trim(trimmed.substr(eq + 1));
    if (key == "title") {
      if (!value.empty()) {
        params.title = value;
      }
    } else if (key == "variants") {
      try {
        params.variants = std::stoi(value);
      } catch (const std::exception&) {
        error = "invalid variants value";
        return false;
      }
    } else if (key == "questions_per_variant") {
      try {
        params.questionsPerVariant = std::stoi(value);
      } catch (const std::exception&) {
        error = "invalid questions_per_variant value";
        return false;
      }
    } else if (key == "tags") {
      params.tags = splitList(value, ',');
    } else if (key == "exclude_ids") {
      const std::vector< std::string > ids = splitList(value, ',');
      for (std::size_t i = 0; i < ids.size(); ++i) {
        params.excludeIds.insert(ids[i]);
      }
    }
  }
  if (params.variants <= 0) {
    error = "variants must be positive";
    return false;
  }
  if (params.questionsPerVariant <= 0) {
    error = "questions_per_variant must be positive";
    return false;
  }
  return true;
}

