#pragma once
#include "branch.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Checkout {

const std::string HEAD_PATH = "/HEAD";
const std::string HEAD_CONTENT = "ref: refs/heads/";

auto checkout(int argc, char *argv[], const std::string &GIT_DIRPATH) -> int {
  std::ifstream head_read(HEAD_PATH);
  std::string current;
  std::cout << GIT_DIRPATH << std::endl;
  // std::vector<std::string> branchList = Branch::branch(0, argv, GIT_DIRPATH);
  if (head_read.is_open()) {
    std::getline(head_read, current);
    head_read.close();
  }

  if (argc <= 2) {
    std::cerr << "Usage: checkout <branch>" << std::endl;
    return 1;
  }

  std::string target_branch = argv[2];
  // std::cout << target_branch << std::endl;
  if (HEAD_CONTENT + target_branch == current) {
    std::cout << "Already on '" << target_branch << "'" << std::endl;
  } else {
    std::ofstream head_write(HEAD_PATH, std::ios::trunc);
    if (!head_write.is_open()) {
      std::cerr << "Failed to open HEAD file for writing." << std::endl;
      return 1;
    }
    head_write << HEAD_CONTENT + target_branch << std::endl;
    head_write.close();
    std::cout << "Switched to branch '" << target_branch << "'" << std::endl;
  }

  return 0;
}

} // namespace Checkout
