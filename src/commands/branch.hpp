#pragma once
#include "checkout.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Branch {

const std::string BRANCH_FILE_PATH = "/refs/heads";

std::vector<std::string> branch(int argc, char *argv[],
                                const std::string &GIT_DIRPATH) {
  std::vector<std::string> return_value;

  if (argc == 2) {
    for (const auto &file :
         std::filesystem::directory_iterator(GIT_DIRPATH + BRANCH_FILE_PATH)) {
      std::string branch_name = file.path().stem().string();
      std::cout << branch_name << std::endl;
      return_value.push_back(branch_name);
    }
  } else {
    std::cout << argc << std::endl;
    for (int i = 2; i < argc; i++) {
      std::cout << argv[i] << std::endl;
    }
    for (int i = 2; i < argc; i++) {
      return_value.push_back(argv[i]);
    }
  }

  return return_value;
}

} // namespace Branch
