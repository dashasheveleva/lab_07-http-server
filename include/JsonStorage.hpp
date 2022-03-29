// Copyright 2022 Shevelyova Darya photodoshfy@gmail.com

#ifndef LAB_07_JSONSTORAGE_HPP
#define LAB_07_JSONSTORAGE_HPP

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

#endif  // LAB_07_JSONSTORAGE_HPP
