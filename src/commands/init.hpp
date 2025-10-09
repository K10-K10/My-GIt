#pragma once
#include "checkout.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Init {
int init() {
  for (const auto &file : std::filesystem::directory_iterator("./")) {
    if (file.path().filename() == ".my-git") {
      std::cout << "Already Initialized." << std::endl;
      return 0;
    }
  }
  std::filesystem::path current_dir = std::filesystem::current_path();
  std::cout << "Initialized empty Git repository in " << current_dir
            << std::endl;
  std::filesystem::create_directories("./.my-git/");
  std::filesystem::create_directories("./.my-git/refs/heads");
  std::ofstream HEAD("./.my-git/HEAD"), config("./.my-git/config"),
      description("./.my-git/description");
  HEAD << "ref: refs/heads/main" << std::endl;
  HEAD.close();
  config.close();
  description.close();
  return 0;
}
} // namespace Init
