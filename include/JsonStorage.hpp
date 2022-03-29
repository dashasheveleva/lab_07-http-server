// Copyright 2022 Shevelyova Darya photodoshfy@gmail.com

#ifndef INCLUDE_JSONSTORAGE_HPP_
#define INCLUDE_JSONSTORAGE_HPP_

#include <iostream>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class JsonStorage{
 public:
  explicit JsonStorage(const std::string filename);
  [[nodiscard]] json get_storage() const;
  void load();

 private:
  json _storage; // Место хранения
  std::string _filename; // Имя файла
};

#endif  // INCLUDE_JSONSTORAGE_HPP_
