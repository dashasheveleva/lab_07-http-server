// Copyright 2022 Shevelyova Darya photodoshfy@gmail.com

#ifndef LAB_07_SUGGESTION_HPP
#define LAB_07_SUGGESTION_HPP

#include <iostream>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class CallSuggestions{
 public:
  CallSuggestions();
  void update(json storage);
  json suggest(const std::string& input);

 private:
  json _suggestions; // Предложения
};

#endif  // LAB_07_SUGGESTION_HPP
